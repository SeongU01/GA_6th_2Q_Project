#pragma once
#include "State.h"
#include "RangeEnemyInformation.h"

namespace Engine
{
	class Animation;
	class SpriteRenderer;
	class	TextRenderer;
}
class GridEffect;
class HP;
class GridMovement;
class AStar;
class Pannel;
class RangeEnemyScript;
class RangeEnemyState :public Engine::State
{
protected:
	explicit RangeEnemyState() = default;
	virtual ~RangeEnemyState() = default;
	void Initialize(RangeEnemyScript* pScript);
public:
	virtual void ShowInfo() {};
	virtual void CloseInfo() {};
protected:
	Engine::TextRenderer* _pTextRenderer = nullptr;
	Vector3* _pTargetPosition = nullptr;
	Vector3* _pGridPosition = nullptr;
	RangeEnemyScript* _pOwner = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	GridMovement* _pMovement = nullptr;
	AStar* _pAstar = nullptr;
	Pannel* _pPannel = nullptr;
	GridEffect* _pGridEffect = nullptr;
	std::wstring _infoText;
	bool _isBack = false;

};

