#pragma once
#include "Base.h"

namespace Engine
{
	class GameManager;
}

class DataManager;
class MainGame : public Engine::Base
{
private:
	explicit MainGame();
	virtual ~MainGame() = default;

public:
	void Run();

private:
	// Base을(를) 통해 상속됨
	bool Initialize(HINSTANCE hInstance);	
	void Free() override;

public:
	static MainGame* Create(HINSTANCE hInstance);

private:
	Engine::GameManager*	_pGameManager = nullptr;
	DataManager*			_pDataManager = nullptr;
};

