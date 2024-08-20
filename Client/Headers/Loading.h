#pragma once
#include "Scene.h"

class Loading : public Engine::Scene
{
private:
	explicit Loading() = default;
	virtual ~Loading() = default;

public:
	// Scene��(��) ���� ��ӵ�
	void Free() override;
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	bool Initialize() override;

private:
	void LoadResource();

public:
	static Loading* Create();

private:
	bool _isLoading = false;
};

