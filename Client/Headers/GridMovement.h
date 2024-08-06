#pragma once
#include "MonoBehavior.h"

class Grid;
class GridMovement:public Engine::MonoBehavior 
{
public:
	explicit GridMovement(const wchar_t* name, const float speed);
private:
	virtual ~GridMovement() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void MoveToCell(Vector3& pos, float timeToMove);
public:
	Grid* _grid=nullptr;
	bool _isMoving=false;
private:
	Vector3 _originPos;
	Vector3 _targetPos;
	float _timeToMove=0.f;
	float _moveSpeed = 0.f;
};

