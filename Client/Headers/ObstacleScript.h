#pragma once
#include "MonoBehavior.h"

class GridInfo;

class ObstacleScript :public Engine::MonoBehavior
{
public:
	explicit ObstacleScript(const wchar_t* name,const std::pair<Vector3, Vector3>&gridRange);
private:
	virtual ~ObstacleScript() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	GridInfo* _pGridInfo=nullptr;
	//<startpos,endpos>
	std::pair<Vector3, Vector3>_gridRange;
};

