#include "EffectTarget.h"

// Component
#include "Player.h"
#include "GridEffect.h"

#include "Client_Define.h"

void EffectTarget::ShowRange()
{
	const Vector3& gridPosition = _pPlayer->GetGridPosition();

	for (auto& grid : _ranges)
		_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), 6);
}

bool EffectTarget::Initialize(Player* pPlayer, CardEffectType type, const std::vector<std::pair<int, int>>& range)
{
	_pPlayer = pPlayer;
	_effectType = type;
	_ranges = range;

	_pGridEffect = Engine::FindObject((int)LayerGroup::UI, L"UI", L"GridEffect")->GetComponent<GridEffect>();

	return true;
}

void EffectTarget::Free()
{
}

EffectTarget* EffectTarget::Create(Player* pPlayer, CardEffectType type, const std::vector<std::pair<int, int>>& range)
{
	EffectTarget* pInstance = new EffectTarget;

	if (pInstance->Initialize(pPlayer, type, range))
		return pInstance;

	return pInstance;
}
