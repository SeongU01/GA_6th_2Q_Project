#pragma once
#include "MonoBehavior.h"

class GridEffect : public Engine::MonoBehavior
{
public:
	explicit GridEffect(int width, int height);
private:
	virtual ~GridEffect() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void OnEffect(int x, int y, int type);

private:
	std::vector<std::vector<Engine::GameObject*>> _gridEffects;
};