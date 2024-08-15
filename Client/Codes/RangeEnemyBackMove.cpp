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

    // BFS를 위한 큐: 각 요소는 (x, y) 좌표와 현재 스텝 수를 가진다.
    std::queue<std::tuple<int, int, int>> bfsQueue;

    // 시작 지점
    int startX = (int)_pGridPosition->x;
    int startY = (int)_pGridPosition->y;

    // 이미 방문한 노드를 추적하기 위한 배열
    std::vector<std::vector<bool>> visited(gridHeight, std::vector<bool>(gridWidth, false));

    // 초기 지점 추가 및 방문 표시
    bfsQueue.push({ startX, startY, 0 });
    visited[startY][startX] = true;

    Vector3 farthestPosition = *_pTargetPosition;
    float maxDistance = 0;

    while (!bfsQueue.empty())
    {
        auto [x, y, currentStep] = bfsQueue.front();
        bfsQueue.pop();

        // 지정된 step에서 멈추고, 가장 먼 지점을 계산
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

        // 상하좌우로 이동 가능한 지점 확인
        for (auto& dir : directions)
        {
            int nextX = x + dir.first;
            int nextY = y + dir.second;

            // 좌표 유효성 및 방문 여부 확인
            if (nextX >= 0 && nextX < gridWidth && nextY >= 0 && nextY < gridHeight && !visited[nextY][nextX])
            {
                // 이동 가능한지 여부 확인
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
