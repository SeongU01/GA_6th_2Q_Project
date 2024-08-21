#pragma once
#include "State.h"
#include "ToolTip.h"
#include "Pannel.h"
#include "RangeEnemyInformation.h"

namespace Engine
{
	class Animation;
	class SpriteRenderer;
	class	TextRenderer;
}
class Attribute;
class Player;
class GridEffect;
class HP;
class GridMovement;
class AStar;
class RangeEnemyScript;
class RangeEnemyState :public Engine::State
{
protected:
	explicit RangeEnemyState() = default;
	virtual ~RangeEnemyState() = default;
	void Initialize(RangeEnemyScript* pScript);
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
protected:
	Attribute* _pAttribute = nullptr;
	HP* _pHP = nullptr;
	Player* _pPlayer = nullptr;
	Engine::TextRenderer* _pTextRenderer = nullptr;
	Engine::SpriteRenderer* _pSpriteRenderer = nullptr;
	const Vector3* _pTargetPosition = nullptr;
	Vector3* _pGridPosition = nullptr;
	RangeEnemyScript* _pOwner = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	GridMovement* _pMovement = nullptr;
	AStar* _pAstar = nullptr;
	Pannel* _pPannel = nullptr;
	ToolTip* _pToolTip = nullptr;
	GridEffect* _pGridEffect = nullptr;

	std::wstring _infoText;
	Vector3 _currDirection = { 1.f,0.f,0.f };

};

