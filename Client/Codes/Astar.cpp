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

	//// 목표 지점이 갱신되었거나 경로가 비어있거나 인덱스 초과 시 새 경로 계산
	//if (!((int)temporaryGoal.x == (int)_goalPosition.x && (int)temporaryGoal.y == (int)_goalPosition.y) ||
	//	_path.empty() || _pathIndex >= _path.size())
	//{
	//	_goalPosition = temporaryGoal;
	//	_path = AStarMove(_gridPosition, _goalPosition, _movement->_grid->GetTiles());
	//	_goalPosition = _path[_path.size() - 2];
	//	_path.pop_back();
	//	_pathIndex = 1;
	//	_currentMoveSteps = 0; // 이동 단계 초기화

	//}
	if (_path.empty() || _pathIndex >= _path.size())
	{
		_path = AStarMove(_gridPosition, _goalPosition, _movement->_grid->GetTiles());
		if(!_path.empty())
		{
			_goalPosition = _path[_path.size() - 2];
			_path.pop_back();
			_pathIndex = 1;
			_currentMoveSteps = 0; // 이동 단계 초기화
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
			_currentMoveSteps++; // 이동 단계 증가

			// 이동 가능 여부 확인 후 이동
			if (_movement->_grid->IsTileWalkable((int)_gridPosition.x, (int)_gridPosition.y))
			{
				_movement->MoveToCell(_gridPosition, 0.5f);
			}
			else
			{
				_path.clear(); // 비워진 경로
				_isMoving = false; // AStar의 움직임 비활성화
			}
		}
		// 최대 이동 단계에 도달했는지 확인
		if (_currentMoveSteps >= _maxMoveSteps)
		{
			_isMoving = false; // AStar의 움직임 비활성화
			std::cout << "Max move steps reached: " << _currentMoveSteps << std::endl;
		}

	}
}

void AStar::LateUpdate(const float& deltaTime)
{
}

void AStar::SetMaxMoveSteps(int steps)
{
	_maxMoveSteps = steps; // 이동할 칸 수 설정
	_currentMoveSteps = 0; // 현재 이동 단계 초기화
	_isMoving = true; // AStar의 움직임 활성화
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
	return std::abs(a.x - b.x) + std::abs(a.y - b.y); // 맨해튼 거리
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
	std::reverse(path.begin(), path.end()); // 경로를 역순으로
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

		// 목표 노드에 도달했는지 확인
		if (*currentNode == Node(goal))
		{
			return reconstructPath(currentNode); // 경로 재구성
		}

		// 이웃 노드 탐색
		for (const auto& neighborPos : getNeighbors(currentNode->position, grid, goal))
		{
			float tentativeGCost = currentNode->gCost + 1; // 이동 비용
			std::shared_ptr<Node> neighborNode;

			// 이웃 노드가 처음 발견된 경우
			if (allNodes.find(neighborPos) == allNodes.end())
			{
				neighborNode = std::make_shared<Node>(neighborPos);
				neighborNode->pParent = currentNode;
				allNodes[neighborPos] = neighborNode;
			}
			else
			{
				neighborNode = allNodes[neighborPos];
				if (tentativeGCost >= neighborNode->gCost) continue; // 더 나은 경로가 아닐 경우
			}

			// gCost, hCost 업데이트
			neighborNode->gCost = tentativeGCost;
			neighborNode->hCost = heuristic(neighborPos, goal);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost; // fCost 계산
			neighborNode->pParent = currentNode; // 부모 노드 설정

			openSet.push(neighborNode); // 열린 집합에 추가
		}
	}
	return std::vector<Vector3>(); // 경로를 찾지 못한 경우 빈 벡터 반환
}
