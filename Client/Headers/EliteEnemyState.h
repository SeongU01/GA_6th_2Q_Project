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
class Player;
class DefenseScript;
class HP;
class Attribute;
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
	bool CheckRange(int x, int y);
protected:
	Attribute* _pAttribute = nullptr;
	HP* _pHP = nullptr;
	DefenseScript* _pDefense=nullptr;
	Player* _pPlayer = nullptr;
	Engine::TextRenderer* _pTextRenderer = nullptr;
	const Vector3* _pTargetPosition = nullptr;
	Vector3* _pGridPosition = nullptr;
	EliteEnemyScript* _pOwner = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	GridMovement* _pMovement = nullptr;
	AStar* _pAstar = nullptr;
	Pannel* _pPannel = nullptr;
	GridEffect* _pGridEffect = nullptr;
	std::wstring _infoText;
	Vector3 _currDirection = {1.f,0.f,0.f};
};


