#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
}

enum class CardEffectType;
class Player;
class GridEffect;
class EffectTarget : public Engine::Base
{
private:
	explicit EffectTarget() = default;
	virtual ~EffectTarget() = default;

public:
	void ShowRange();

private:
	// Base을(를) 통해 상속됨
	bool Initialize(Player* pPlayer, CardEffectType type, const std::vector<std::pair<int, int>>& range);
	void Free() override;

public:
	static EffectTarget* Create(Player* pPlayer, CardEffectType type, const std::vector<std::pair<int, int>>& range);

private:
	std::vector<std::pair<int, int>> _ranges;
	Player* _pPlayer = nullptr;
	CardEffectType _effectType;
	GridEffect* _pGridEffect = nullptr;
};

