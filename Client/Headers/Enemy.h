#pragma once 
#include "MonoBehavior.h"
#include "Player.h"
namespace Engine
{
	class Animation;
	class FiniteStateMachine;
}
class GridMovement;
class Enemy : public Engine::MonoBehavior
{
public:
	explicit Enemy(const wchar_t* name);
private:
	virtual ~Enemy() = default;

public:
	void SetGridPosition(const Vector3& position) { _gridPosition = position; }
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	GridMovement* _movement = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
	Player* _player = nullptr;
	float _moveTime = 0.8f;
	float _curTime = 0.f;
	
private:
	Vector3 _gridPosition = { 0.f,0.f,0.f };
	Vector3 goalPosition;
	std::vector<Vector3> _path;
	size_t _pathIndex = 0;

};