#include "Astar.h"
#include "Client_Define.h"
#include "Tile.h"
#include "Grid.h"
#include "GridMovement.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

AStar::AStar(const wchar_t* name, const std::wstring& targetName)
	: MonoBehavior(name), _targetObjectName(targetName)
{
}

void AStar::Awake()
{
}

void AStar::Start()
{
	_pTargetObject = Engine::FindObject((int)LayerGroup::Object, L"Defense", _targetObjectName.c_str());
	if (_targetObjectName == L"player") _pTargetObject = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);
}

void AStar::Update(const float& deltaTime)
{
	if (!_isMoving) return;
	if (_gridPosition == _goalPosition)
	{
		return;
	}

	//Vector3 temporaryGoal = _goalPosition;

	//// ��ǥ ������ ���ŵǾ��ų� ��ΰ� ����ְų� �ε��� �ʰ� �� �� ��� ���
	//if (!((int)temporaryGoal.x == (int)_goalPosition.x && (int)temporaryGoal.y == (int)_goalPosition.y) ||
	//	_path.empty() || _pathIndex >= _path.size())
	//{
	//	_goalPosition = temporaryGoal;
	//	_path = AStarMove(_gridPosition, _goalPosition, _movement->_grid->GetTiles());
	//	_goalPosition = _path[_path.size() - 2];
	//	_path.pop_back();
	//	_pathIndex = 1;
	//	_currentMoveSteps = 0; // �̵� �ܰ� �ʱ�ȭ

	//}
	if (_path.empty() || _pathIndex >= _path.size())
	{
		_path = AStarMove(_gridPosition, _goalPosition, _movement->_grid->GetTiles());
		if(!_path.empty())
		{
			_goalPosition = _path[_path.size() - 2];
			_path.pop_back();
			_pathIndex = 1;
			_currentMoveSteps = 0; // �̵� �ܰ� �ʱ�ȭ
		}

	}
	_curTime += deltaTime;

	if (!_path.empty() && _pathIndex < _path.size())
	{
		if (_curTime >= _moveTime)
		{
			Vector3 nextPosition = _path[_pathIndex];
			_gridPosition = nextPosition;
			_curTime = 0.0f;
			_pathIndex++;
			_currentMoveSteps++; // �̵� �ܰ� ����

			// �̵� ���� ���� Ȯ�� �� �̵�
			if (_movement->_grid->IsTileWalkable((int)_gridPosition.x, (int)_gridPosition.y))
			{
				_movement->MoveToCell(_gridPosition, 0.5f);
			}
			else
			{
				_path.clear(); // ����� ���
				_isMoving = false; // AStar�� ������ ��Ȱ��ȭ
			}
		}
		// �ִ� �̵� �ܰ迡 �����ߴ��� Ȯ��
		if (_currentMoveSteps >= _maxMoveSteps)
		{
			_isMoving = false; // AStar�� ������ ��Ȱ��ȭ
			std::cout << "Max move steps reached: " << _currentMoveSteps << std::endl;
		}

	}
}

void AStar::LateUpdate(const float& deltaTime)
{
}

void AStar::SetMaxMoveSteps(int steps)
{
	_maxMoveSteps = steps; // �̵��� ĭ �� ����
	_currentMoveSteps = 0; // ���� �̵� �ܰ� �ʱ�ȭ
	_isMoving = true; // AStar�� ������ Ȱ��ȭ
	_curTime = _moveTime;
}

void AStar::ChangeTarget(std::wstring targetName)
{
	_targetObjectName = targetName;
	if (L"player" == targetName)
	{
		_pTargetObject = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);
		return;
	}
	_pTargetObject = Engine::FindObject((int)LayerGroup::Object, L"Defense", _targetObjectName.c_str());
}

float AStar::heuristic(const Vector3& a, const Vector3& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y); // ����ư �Ÿ�
}

std::vector<Vector3> AStar::getNeighbors(const Vector3& pos, const std::vector<std::vector<Tile*>>& grid, Vector3 goal)
{
	std::vector<Vector3> neighbors;
	std::vector<Vector3> directions = { {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0} };

	for (const auto& dir : directions)
	{
		Vector3 neighborPos = { pos.x + dir.x, pos.y + dir.y, pos.z };
		if (neighborPos.x >= 0 && (int)neighborPos.x < (int)grid[0].size() &&
			neighborPos.y >= 0 && (int)neighborPos.y < (int)grid.size() &&
			(grid[(int)neighborPos.y][(int)neighborPos.x]->canMove ||
				((int)goal.x == (int)neighborPos.x && (int)goal.y == (int)neighborPos.y)))
		{
			neighbors.push_back(neighborPos);
		}
	}
	return neighbors;
}

std::vector<Vector3> AStar::reconstructPath(const std::shared_ptr<Node>& currentNode)
{
	std::vector<Vector3> path;
	std::shared_ptr<Node> node = currentNode;
	while (node != nullptr)
	{
		path.push_back(node->position);
		node = node->pParent;
	}
	std::reverse(path.begin(), path.end()); // ��θ� ��������
	return path;
}

std::vector<Vector3> AStar::AStarMove(const Vector3& start, const Vector3& goal, const std::vector<std::vector<Tile*>>& grid)
{
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare> openSet;
	std::unordered_map<Vector3, std::shared_ptr<Node>, Vector3Hash> allNodes;

	auto startNode = std::make_shared<Node>(start);
	openSet.push(startNode);
	allNodes[start] = startNode;

	while (!openSet.empty())
	{
		auto currentNode = openSet.top();
		openSet.pop();

		// ��ǥ ��忡 �����ߴ��� Ȯ��
		if (*currentNode == Node(goal))
		{
			return reconstructPath(currentNode); // ��� �籸��
		}

		// �̿� ��� Ž��
		for (const auto& neighborPos : getNeighbors(currentNode->position, grid, goal))
		{
			float tentativeGCost = currentNode->gCost + 1; // �̵� ���
			std::shared_ptr<Node> neighborNode;

			// �̿� ��尡 ó�� �߰ߵ� ���
			if (allNodes.find(neighborPos) == allNodes.end())
			{
				neighborNode = std::make_shared<Node>(neighborPos);
				neighborNode->pParent = currentNode;
				allNodes[neighborPos] = neighborNode;
			}
			else
			{
				neighborNode = allNodes[neighborPos];
				if (tentativeGCost >= neighborNode->gCost) continue; // �� ���� ��ΰ� �ƴ� ���
			}

			// gCost, hCost ������Ʈ
			neighborNode->gCost = tentativeGCost;
			neighborNode->hCost = heuristic(neighborPos, goal);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost; // fCost ���
			neighborNode->pParent = currentNode; // �θ� ��� ����

			openSet.push(neighborNode); // ���� ���տ� �߰�
		}
	}
	return std::vector<Vector3>(); // ��θ� ã�� ���� ��� �� ���� ��ȯ
}
