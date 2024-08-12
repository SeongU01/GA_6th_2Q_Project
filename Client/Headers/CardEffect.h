#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
}

enum class CardEffectType;
class Player;
class GridEffect;
class CardEffect : public Engine::Base
{
public:
	struct CardEffectInfo
	{
		std::vector<std::pair<int, int>> ranges;
		unsigned long long additiveFlag;
		CardEffectType effectType;
		int value;
		int additiveStack;
	};
private:
	explicit CardEffect() = default;
	virtual ~CardEffect() = default;

public:
	void ShowRange();
	std::vector<std::pair<int, int>> GetAttackRange();

private:
	// Base을(를) 통해 상속됨
	bool Initialize(Player* pPlayer, const CardEffectInfo& info);
	void Free() override;

private:
	std::pair<int, int> ComputeRotationTarget(int x, int y);

public:
	static CardEffect* Create(Player* pPlayer, const CardEffectInfo& info);

private:
	CardEffectInfo _info;
	Player* _pPlayer = nullptr;	
	GridEffect* _pGridEffect = nullptr;
};

