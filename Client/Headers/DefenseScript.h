#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class SpriteRenderer;
	class GameObject;
}
class GridInfo;
class HP;
class ToolTip;
class DefenseScript : public Engine::MonoBehavior
{
public:
	explicit DefenseScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange, const wchar_t* type);
private:
	virtual ~DefenseScript() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Explosion();
	bool IsDestroy() { return _isDestroy; }
public:
	virtual void OnCollisionEnter(Engine::CollisionInfo& info) override;
	virtual void OnCollision(Engine::CollisionInfo& info) override;
	virtual void OnCollisionExit(Engine::CollisionInfo& info) override;
public:
	const Vector3& GetGridPosition() { return _gridPosition; }
private:
	std::wstring _name;
	HP* _pHP = nullptr;
	GridInfo* _pGridInfo = nullptr;
	Vector3 _gridPosition;
	Engine::SpriteRenderer* _pSpriteRenderer=nullptr;
	ToolTip* _pToolTip = nullptr;
	std::pair<Vector3, Vector3>_gridRange;
	
	bool _isDestroy = false;
	bool _doDestoryEffect = false;
};

