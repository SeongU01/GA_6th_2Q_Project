#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class GameOverHUD : public Engine::MonoBehavior
{
public:
	explicit GameOverHUD();
private:
	virtual ~GameOverHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

