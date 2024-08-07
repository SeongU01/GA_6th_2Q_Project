#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"
class UI;
class MainHUD : public Engine::MonoBehavior
{
public:
	explicit MainHUD();
private:
	virtual ~MainHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

