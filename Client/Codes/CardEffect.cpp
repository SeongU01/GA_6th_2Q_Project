#include "CardEffect.h"

// Component
#include "Player.h"
#include "GridEffect.h"
#include "GridMovement.h"
#include "Grid.h"

#include "Client_Define.h"

void CardEffect::ShowRange()
{
	const Vector3& gridPosition = _pPlayer->GetNextGridPosition();
	bool isShow = true;
	int index = 6;

	switch (_info.effectType)
	{
	case CardEffectType::RangeAttack:
		break;
	case CardEffectType::RangeCast:
		break;
	case CardEffectType::SelfCast:
		isShow = false;
		break;
	case CardEffectType::PathMove:
		index = 2;
		break;
	}

	if (isShow)
	{
		for (auto& grid : _info.ranges)
		{
			std::pair<int, int> target = ComputeRotationTarget(grid.first, grid.second);
			_pGridEffect->OnEffect(int(gridPosition.x + target.first), int(gridPosition.y + target.second), index);
		}
	}
	else
	{
		_pGridEffect->OnEffect((int)gridPosition.x, (int)gridPosition.y, 3);
	}
}

std::vector<std::pair<int, int>> CardEffect::GetAttackRange()
{	
	std::vector<std::pair<int, int>> attackRange;

	for (auto& grid : _info.ranges)
	{
		std::pair<int, int> position = ComputeRotationTarget(grid.first, grid.second);
		attackRange.push_back(std::make_pair(position.first, position.second));
	}

	return attackRange;
}

bool CardEffect::Initialize(Player* pPlayer, const CardEffectInfo& info)
{
	_pPlayer = pPlayer;
	_info = info;

	_pGridEffect = Engine::FindObject((int)LayerGroup::UI, L"UI", L"GridEffect")->GetComponent<GridEffect>();

	return true;
}

void CardEffect::Free()
{
}

std::pair<int, int> CardEffect::ComputeRotationTarget(int x, int y)
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(Engine::GetWindow(), &mousePoint);

	Vector3 mousePosition = { float(mousePoint.x), float(mousePoint.y), 0.f };

	Vector3 gridPosition = _pPlayer->GetNextGridPosition();
	Vector3 playerPosition = _pPlayer->GetComponent<GridMovement>()->_grid->GetTileCenter((int)gridPosition.x, (int)gridPosition.y);
	 
	Vector3 direction = mousePosition - playerPosition;
	float radian = XMVectorATan2({ direction.y }, { direction.x }).m128_f32[0];
	
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
	Vector3 rotatePosition = XMVector3TransformCoord(Vector3((float)x, (float)y, 0.f), xmRotationZ);
	_degree = XMConvertToDegrees(radian);

	return std::pair<int, int>((int)ceil(rotatePosition.x - 0.5f), (int)ceil(rotatePosition.y - 0.5f));
}

CardEffect* CardEffect::Create(Player* pPlayer, const CardEffectInfo& info)
{
	CardEffect* pInstance = new CardEffect;

	if (pInstance->Initialize(pPlayer, info))
		return pInstance;

	return pInstance;
}
