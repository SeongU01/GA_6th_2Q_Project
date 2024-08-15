#pragma once
#include "RangeEnemyBackMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridMovement.h"
#include "Grid.h"
#include "Tile.h"

#include "Client_Define.h"

int RangeEnemyBackMove::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Move");
            _pAstar->SetGoalPosition(FindBFS(3));
			_pAstar->SetMaxMoveSteps(2);
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemyBackMove::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Move") && _pAnimation->IsLastFrame())
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyBackMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(1, 3);
}

void RangeEnemyBackMove::OnExit()
{
}

Vector3 RangeEnemyBackMove::FindBFS(int step)
{
    std::vector<std::vector<Tile*>> _grid = _pMovement->_grid->GetTiles();
    int gridHeight = (int)_grid.size();
    int gridWidth = (int)_grid[0].size();

    std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    // BFS�� ���� ť: �� ��Ҵ� (x, y) ��ǥ�� ���� ���� ���� ������.
    std::queue<std::tuple<int, int, int>> bfsQueue;

    // ���� ����
    int startX = (int)_pGridPosition->x;
    int startY = (int)_pGridPosition->y;

    // �̹� �湮�� ��带 �����ϱ� ���� �迭
    std::vector<std::vector<bool>> visited(gridHeight, std::vector<bool>(gridWidth, false));

    // �ʱ� ���� �߰� �� �湮 ǥ��
    bfsQueue.push({ startX, startY, 0 });
    visited[startY][startX] = true;

    Vector3 farthestPosition = *_pTargetPosition;
    float maxDistance = 0;

    while (!bfsQueue.empty())
    {
        auto [x, y, currentStep] = bfsQueue.front();
        bfsQueue.pop();

        // ������ step���� ���߰�, ���� �� ������ ���
        if (currentStep == step)
        {
            float distance = (float)sqrt(pow(x - _pTargetPosition->x, 2) + pow(y - _pTargetPosition->y, 2));
            if (distance > maxDistance)
            {
                maxDistance = distance;
                farthestPosition = Vector3((float)x, (float)y, 0.f);
            }
            continue;
        }

        // �����¿�� �̵� ������ ���� Ȯ��
        for (auto& dir : directions)
        {
            int nextX = x + dir.first;
            int nextY = y + dir.second;

            // ��ǥ ��ȿ�� �� �湮 ���� Ȯ��
            if (nextX >= 0 && nextX < gridWidth && nextY >= 0 && nextY < gridHeight && !visited[nextY][nextX])
            {
                // �̵� �������� ���� Ȯ��
                if (_grid[nextY][nextX]->canMove)
                {
                    bfsQueue.push({ nextX, nextY, currentStep + 1 });
                    visited[nextY][nextX] = true;
                }
            }
        }
    }

    return farthestPosition;
}

void RangeEnemyBackMove::ShowInfo()
{
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Back] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyBackMove::CloseInfo()
{
	_pPannel->SetActive(false);
}

RangeEnemyBackMove* RangeEnemyBackMove::Create(RangeEnemyScript* pScript)
{
	RangeEnemyBackMove* pInstance = new RangeEnemyBackMove;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
