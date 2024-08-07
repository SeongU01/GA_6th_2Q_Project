#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class CreditHUD : public Engine::MonoBehavior
{
public:
	explicit CreditHUD();
private:
	virtual ~CreditHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

