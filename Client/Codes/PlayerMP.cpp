#include "PlayerMP.h"
#include "Client_Define.h"
PlayerMP::PlayerMP(const wchar_t* name)
	:MonoBehavior(name)
{
}

void PlayerMP::Awake()
{
}

void PlayerMP::Start()
{
}

void PlayerMP::Update(const float& deltaTime)
{
	MPUpdate(deltaTime);
}

void PlayerMP::LateUpdate(const float& deltaTime)
{
}

void PlayerMP::MPUpdate(const float& deltaTime)
{
	if (_mp < 5)
		NaturalRecovery(deltaTime);

	//마나 테스트용...
	if (Input::IsKeyDown(DIK_M))
	{
		_mp--;
	}

	_mp = std::clamp(_mp, 0, 5);
}

void PlayerMP::NaturalRecovery(const float& deltaTime)
{
	_mpRecoveryTime += deltaTime;

	if (_mpRecoveryTime >= 5.f)
	{
		_mpRecoveryTime = 0.f;
		_mp++;
	}
}
