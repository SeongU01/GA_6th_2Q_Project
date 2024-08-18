#pragma once
#include "MonoBehavior.h"

class GridInfo;
class ToolTip;
class ObstacleScript :public Engine::MonoBehavior
{
public:
	explicit ObstacleScript(const wchar_t* name,const std::pair<Vector3, Vector3>&gridRange, const wchar_t* texture);
private:
	virtual ~ObstacleScript() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
public:
	virtual void OnCollisionEnter(Engine::CollisionInfo& info);
	virtual void OnCollision(Engine::CollisionInfo& info);
	virtual void OnCollisionExit(Engine::CollisionInfo& info);
private:
	GridInfo* _pGridInfo=nullptr;
	//<startpos,endpos>
	std::wstring _type;
	ToolTip* _pToolTip = nullptr;
	std::pair<Vector3, Vector3>_gridRange;
};

