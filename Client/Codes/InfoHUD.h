#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class InfoHUD : public Engine::MonoBehavior
{
public:
	explicit InfoHUD();
private:
	virtual ~InfoHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

