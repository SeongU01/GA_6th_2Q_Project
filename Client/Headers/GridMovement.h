#pragma once
#include "MonoBehavior.h"

class Grid;
class GridMovement:public Engine::MonoBehavior 
{
public:
	explicit GridMovement(const wchar_t* name);
private:
	virtual ~GridMovement() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void MoveToCell(int x, int y, float timeToMove);
public:
	Grid* _grid=nullptr;
private:
	Vector3 _originPos;
	Vector3 _targetPos;
	bool _isMoving=false;
	float _timeToMove=0.f;
};

