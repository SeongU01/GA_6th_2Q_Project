#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class MainStageHUD : public Engine::MonoBehavior
{
public:
	explicit MainStageHUD();
private:
	virtual ~MainStageHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

