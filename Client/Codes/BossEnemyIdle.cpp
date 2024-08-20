#include "BossEnemyIdle.h"
#include "BossEnemyScript.h"
//component
#include "HP.h"
#include "Astar.h"
#include "Animation.h"

#include "TextRenderer.h"
#include "Client_Define.h"

int BossEnemyIdle::Update(const float& deltaTime)
{
	if (!_isFandIn)
	{
		_alpha += deltaTime;
		_pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, _alpha);
		_pHP->SetInvinsibleTime(1.f);
		_pHP->SetInvinsible(true);
		if (_alpha >= 1.f)
		{
			_alpha = 1.f;
			_pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, _alpha);
			_pHP->SetInvinsibleTime(0.1f);
			_pHP->SetInvinsible(false);
			_isFandIn = true;
		}
		return 0;
	}

	const Vector3& gridPosition = *_pGridPosition;
	Vector3 Direction = *_pTargetPosition - gridPosition;

	if (_currDirection.x * Direction.x < 0)
	{
		_currDirection.x *= -1;
		_pOwner->transform.scale *= Vector3(-1.f, 1.f, 1.f);
		_pPannel->transform.scale *= Vector3(-1.f, 1.f, 1.f);
	}
	_nextState = SelectNextBehave();
	return 0;
}

int BossEnemyIdle::LateUpdate(const float& deltaTime)
{
	ShowInfo();
	return (int)_nextState;
}

void BossEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");

}

void BossEnemyIdle::OnExit()
{
	CloseInfo();
}

void BossEnemyIdle::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-30.f, -15.f, 0.f));

	_infoText = L"[None]";
	_pTextRenderer->SetText(_infoText.c_str());
}

void BossEnemyIdle::CloseInfo()
{
	__super::CloseInfo();
}

BossEnemy::FSM BossEnemyIdle::SelectNextBehave()
{
	if (!(_pAstar->GetGoalPosition() == *_pGridPosition))
	{
		return BossEnemy::FSM::Move;
	}
	return BossEnemy::FSM::None;
}

BossEnemyIdle* BossEnemyIdle::Create(BossEnemyScript* pScript)
{
	BossEnemyIdle* pInstance = new BossEnemyIdle;
	pInstance->BossEnemyState::Initialize(pScript);
	return pInstance;
}
