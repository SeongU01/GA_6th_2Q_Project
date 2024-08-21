#pragma once
#include "State.h"
#include "ToolTip.h"
#include "Pannel.h"
#include "BossEnemyInformation.h"

namespace Engine
{
	class Animation;
	class SpriteRenderer;
	class	TextRenderer;
}

class GridEffect;
class BossEnemyScript;
class Player;
class AStar;
class HP;
class GridMovement;
class Attribute;

class BossEnemyState :public Engine::State
{
protected:
	explicit BossEnemyState() = default;
	virtual ~BossEnemyState() = default;
	void Initialize(BossEnemyScript* pScript);
public:
	virtual void ShowInfo()
	{
		_pPannel->SetActive(true);
	};
	virtual void CloseInfo()
	{
		_pPannel->SetActive(false);
	};
	virtual void ShowToolTip()
	{
		_pToolTip->ActiveToolTip(true);
	};
	virtual void CloseToolTip()
	{
		_pToolTip->ActiveToolTip(false);
	};
	bool CheckRange(int x, int y);
protected:
	Attribute* _pAttribute = nullptr;
	HP* _pHP = nullptr;
	Player* _pPlayer = nullptr;
	Engine::TextRenderer* _pTextRenderer = nullptr;
	Engine::SpriteRenderer* _pSpriteRenderer = nullptr;
	const Vector3* _pTargetPosition = nullptr;
	Vector3* _pGridPosition = nullptr;
	BossEnemyScript* _pOwner = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	GridMovement* _pMovement = nullptr;
	AStar* _pAstar = nullptr;
	Pannel* _pPannel = nullptr;
	ToolTip* _pToolTip = nullptr;
	GridEffect* _pGridEffect = nullptr;

	std::wstring _infoText;
	Vector3 _currDirection = { 1.f,0.f,0.f };

};

