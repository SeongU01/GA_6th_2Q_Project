#pragma once
#include "MonoBehavior.h"

class Grid;

class GridInfo:public Engine::MonoBehavior
{
public:
	explicit GridInfo(const wchar_t* name);
private:
	virtual ~GridInfo() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	Grid* GetGrid() { return _pGrid;}
private:
	Grid* _pGrid = nullptr;
};

