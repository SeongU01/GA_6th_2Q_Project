#pragma once
#include "MonoBehavior.h"
#include "Client_Define.h"

class GameClearHUD : public Engine::MonoBehavior
{
public:
	explicit GameClearHUD();
private:
	virtual ~GameClearHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

