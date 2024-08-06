#pragma once
#include "MonoBehavior.h"

class Grid;
class GridMovement:public Engine::MonoBehavior 
{
public:
	explicit GridMovement(const wchar_t* name);
private:
	virtual ~GridMovement() = default;
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	bool CanMove(Vector3& postion);
private:
	Grid* _grid=nullptr;
};

