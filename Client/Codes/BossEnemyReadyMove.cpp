#include "BossEnemyReadyMove.h"
#include "BossEnemyScript.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "TextRenderer.h"
#include "GridMovement.h"
#include "Attribute.h"
#include "Effect.h"
#include "Grid.h"
#include "Tile.h"

#include "Client_Define.h"
int BossEnemyReadyMove::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"ReadyMove");
			if(_pMovement->_grid->GetTiles()[3][7]->canMove)
			{
				_pMovement->MoveToCell(Vector3(7.f, 3.f, 0.f), 0.5f);
				_pAstar->SetGridPosition(Vector3(7.f, 3.f, 0.f));
				_pAstar->ReCalculatePath();
			}
			else
			{
				_pMovement->MoveToCell(Vector3(8.f, 3.f, 0.f), 0.5f);
				_pAstar->SetGridPosition(Vector3(8.f, 3.f, 0.f));
				_pAstar->ReCalculatePath();
			}
			Boost();
			_isStateOn = true;
		}
	}
	return 0;
}

int BossEnemyReadyMove::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"ReadyMove"))
	{
		GetShield();
		return (int)BossEnemy::FSM::LaserBurst;
	}
	return 0;
}

void BossEnemyReadyMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(2, 3);
}

void BossEnemyReadyMove::OnExit()
{
	CloseInfo();
}

void BossEnemyReadyMove::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void BossEnemyReadyMove::CloseInfo()
{
	__super::CloseInfo();
}

void BossEnemyReadyMove::GetShield()
{
	_pAttribute->AddState(AttributeFlag::Shield, 1);

	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.05f;
	info.textureTag = L"AIEffect_Buff";
	info.scale = _pOwner->transform.scale * 1.5f;
	info.position = _pOwner->transform.position + Vector3(0.f, -50.f, 0.f);
	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

void BossEnemyReadyMove::Boost()
{
	Sound::PlaySound("Battle_Sound_Enemy_Boss_Wander", (int)SoundGroup::Battle);
	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.05f;
	info.textureTag = L"AIEffect_Booster";
	info.pTarget = &_pOwner->transform;
	info.drawOffset = Vector3(-100.f, -50.f, 0.f);
	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

BossEnemyReadyMove* BossEnemyReadyMove::Create(BossEnemyScript* pScript)
{
	BossEnemyReadyMove* pInstance = new BossEnemyReadyMove;
	pInstance->BossEnemyState::Initialize(pScript);
	return pInstance;
}
