#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class EventInvoker;
}

enum Stage;
class RestartGame : public Engine::MonoBehavior
{
public:
	explicit RestartGame();
private:
	virtual ~RestartGame() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void SetStage(Stage stage) { _stage = stage; }
	void GameOver();

private:
	Engine::GameObject*		_pRestartGame = nullptr;
	Engine::EventInvoker*	_pEventInvoker = nullptr;
	Stage					_stage;
	float					_alpha = 0.f;
	float					_elapsed = 0.f;
	bool					_isRestart = false;
};

