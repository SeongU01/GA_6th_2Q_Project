#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class StageSelectHUD : public Engine::MonoBehavior
{
public:
	explicit StageSelectHUD();
private:
	virtual ~StageSelectHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

