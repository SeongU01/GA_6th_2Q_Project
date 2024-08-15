#pragma once
#include "State.h"
#include "EliteEnemyInfomation.h"
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
class EliteEnemyScript;
class EliteEnemyState :public Engine::State
{
protected:
	explicit EliteEnemyState() = default;
	virtual ~EliteEnemyState() = default;
	void Initialize(EliteEnemyScript* pScript);
public:
	virtual void ShowInfo() {};
	virtual void CloseInfo() {};
protected:
	Engine::TextRenderer* _pTextRenderer = nullptr;
	Vector3* _pTargetPosition = nullptr;
	Vector3* _pGridPosition = nullptr;
	EliteEnemyScript* _pOwner = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	GridMovement* _pMovement = nullptr;
	AStar* _pAstar = nullptr;
	Pannel* _pPannel = nullptr;
	GridEffect* _pGridEffect = nullptr;
	std::wstring _infoText;

};


