#include "RangeEnemyAttack.h"
//component
#include "Animation.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridEffect.h"

#include "DataManager.h"
#include "Client_Define.h"
int RangeEnemyAttack::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{

		_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Attack");
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemyAttack::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Attack") && _pAnimation->IsLastFrame())
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyAttack::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(1, 3);
	_newTargetPosition = *_pTargetPosition;
}

void RangeEnemyAttack::OnExit()
{
}

void RangeEnemyAttack::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(13);
	int index = 1;
	for (auto& grid : ranges)
	{
		std::pair<int, int> _computePosition= ComputeRotationTarget((int)(gridPosition.x + grid.first), int(gridPosition.y + grid.second));
		_pGridEffect->OnEffect(_computePosition.first,_computePosition.second, index);
	}
}

std::pair<int, int> RangeEnemyAttack::ComputeRotationTarget(int x, int y)
{
	Vector3 direction = _newTargetPosition - *_pGridPosition;
	float radian = XMVectorATan2({ direction.y }, { direction.x }).m128_f32[0];

	int originX = _pGridPosition->x;
	int originY = _pGridPosition->y;

	float relativeX = x - originX;
	float relativeY = y - originY;

	if (radian >= XM_PIDIV4 && radian < 3 * XM_PIDIV4)
	{
		radian = XM_PIDIV2; 
	}
	else if (radian >= 3 * -XM_PIDIV4 && radian < -XM_PIDIV4)
	{
		radian = -XM_PIDIV2; 
	}
	else if (radian >= -XM_PIDIV4 && radian < XM_PIDIV4)
	{
		radian = 0.f; 
	}
	else
	{
		radian = XM_PI; 
	}
	XMMATRIX xmRotationZ = XMMatrixRotationZ(radian);
	Vector3 rotatePosition = XMVector3TransformCoord(Vector3(relativeX, relativeY, 0.f), xmRotationZ);
	float rotatedX = rotatePosition.x + originX;
	float rotatedY = rotatePosition.y + originY;

	return std::pair<int, int>((int)ceil(rotatedX - 0.5f), (int)ceil(rotatedY - 0.5f));
}


void RangeEnemyAttack::ShowInfo()
{
	//if (_pAnimation->IsCurrAnimation(L"Charge"))
	{
		ShowAttackRange();
	}

	_pTextRenderer->SetOffset(Vector3(-60.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Attack] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyAttack::CloseInfo()
{
	_pPannel->SetActive(false);
}

RangeEnemyAttack* RangeEnemyAttack::Create(RangeEnemyScript* pScript)
{
	RangeEnemyAttack* pInstance = new RangeEnemyAttack;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
