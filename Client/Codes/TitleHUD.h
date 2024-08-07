#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class TitleHUD : public Engine::MonoBehavior
{
public:
	explicit TitleHUD();
private:
	virtual ~TitleHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

