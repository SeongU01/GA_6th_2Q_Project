#include "BossEnemyRealLaserWave.h"
#include "BossEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "AttackCollider.h"
#include "Effect.h"
#include "GridEffect.h"
#include "Attribute.h"
#include "Player.h"
#include "GridMovement.h"
#include "Grid.h"

#include "Client_Define.h"
int BossEnemyRealLaserWave::Update(const float& deltaTime)
{
	if (_directionCheck == false)
	{
		const Vector3& gridPosition = *_pGridPosition;
		Vector3 Direction = *_pTargetPosition - gridPosition;

		if (_currDirection.x * Direction.x < 0)
		{
			_currDirection.x *= -1;
		}
		_directionCheck = true;
	}

	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
		{
			_currTime += deltaTime;
		}
		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"RealLaserWave");
			//TODO : 공격하기. 피해 1, 허점부여
			_isStateOn = true;
		}

	}
	return 0;
}

int BossEnemyRealLaserWave::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"RealLaserWave"))
	{
		return (int)BossEnemy::FSM::Idle;
	}
	return 0;
}

void BossEnemyRealLaserWave::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = Engine::RandomGeneratorFloat(1.5f, 2.5f);
	RandX = Engine::RandomGeneratorInt(0, 15);
	RandY = Engine::RandomGeneratorInt(0, 6);
	playerX = (int)_pPlayer->GetGridPosition().x;
	if (RandX == playerX)
	{
		if (RandX == 15)
		{
			RandX--;
		}
		else
		{
			RandX++;
		}
	}
}

void BossEnemyRealLaserWave::OnExit()
{
	CloseInfo();
}

void BossEnemyRealLaserWave::ShowInfo()
{
	__super::ShowInfo();
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}
	_pTextRenderer->SetOffset(Vector3(-60.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Attack] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void BossEnemyRealLaserWave::CloseInfo()
{
	__super::CloseInfo();
}

void BossEnemyRealLaserWave::Attack()
{
	auto pEffect = Engine::GameObject::Create();
	auto pEffect2 = Engine::GameObject::Create();
	auto pEffect3 = Engine::GameObject::Create();

	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.03f;
	info.textureTag = L"AIEffect_Attack_Anim_VFX_Beam_E";
	info.scale = _pOwner->transform.scale * Vector3(3.f, 2.f, 0.f);
	float info1X = _pMovement->_grid->GetTileCenter(playerX, 0).x;
	info.position = Vector3(info1X, 0.f, 0.f);

	Effect::EffectInfo info2;
	info2.renderGroup = RenderGroup::FrontEffect;
	info2.aniSpeed = 0.03f;
	info2.textureTag = L"AIEffect_Attack_Anim_VFX_Beam_E";
	info2.scale = _pOwner->transform.scale * Vector3(3.f, 2.f, 0.f);
	float info2X = _pMovement->_grid->GetTileCenter(RandX, 0).x;
	info2.position = Vector3(info2X, 0.f, 0.f);

	Effect::EffectInfo info3;
	info3.renderGroup = RenderGroup::FrontEffect;
	info3.aniSpeed = 0.03f;
	info3.textureTag = L"AIEffect_Attack_Anim_VFX_Beam_E";
	info3.scale = _pOwner->transform.scale * Vector3(3.f, 2.f, 0.f);
	float info3Y = _pMovement->_grid->GetTileCenter(0, RandY).y;
	info3.position = Vector3(2000.f, info3Y, 0.f);

	AttackCollider* pAttackCollider = _pOwner->GetComponent<AttackCollider>();
	AttackCollider::AttackInfo attackInfo;
	attackInfo.Attribute = AttributeFlag::WeakPoint;
	attackInfo.AttributeStack = 1;
	if (_pAttribute->IsActiveState(AttributeFlag::HighPower))
	{
		_pAttribute->UseStack(Attribute::HighPower);
		attackInfo.damage = 2;
	}
	else
	{
		attackInfo.damage = 1;
	}
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(17);
	if (_currDirection.x >= 0)
	{
		for (auto& range : ranges)
		{
			pAttackCollider->OnCollider(0.01f, 0.05f, playerX, (int)range.first, attackInfo, 0);
			pAttackCollider->OnCollider(0.01f, 0.05f, RandX, (int)range.first, attackInfo, 0);
			pAttackCollider->OnCollider(0.01f, 0.05f, (int)range.first, RandY, attackInfo, 0);
		}
		info.rotation = 90.f;
		info2.rotation = 90.f;
	}
	else
	{
		for (auto& range : ranges)
		{
			pAttackCollider->OnCollider(0.01f, 0.05f, playerX, (int)range.first, attackInfo, 0);
			pAttackCollider->OnCollider(0.01f, 0.05f, RandX, (int)range.first, attackInfo, 0);
			pAttackCollider->OnCollider(0.01f, 0.05f, (int)range.first, RandY, attackInfo, 0);
		}
		info.rotation = -90.f;
		info2.rotation = -90.f;
	}

	pEffect->AddComponent<Effect>(info);
	pEffect2->AddComponent<Effect>(info2);
	pEffect3->AddComponent<Effect>(info3);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect2);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect3);
	Camera::CameraShake(0.2f, 100.f);
}

void BossEnemyRealLaserWave::ShowAttackRange()
{
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(17);
	int index = 1;
	for (auto& grid : ranges)
	{
		_pGridEffect->OnEffect(playerX, (int)grid.first, index);
		_pGridEffect->OnEffect(RandX, (int)grid.first, index);
		_pGridEffect->OnEffect((int)grid.first, RandY, index);
	}
}

BossEnemyRealLaserWave* BossEnemyRealLaserWave::Create(BossEnemyScript* pScript)
{
	BossEnemyRealLaserWave* pInstance = new BossEnemyRealLaserWave;
	pInstance->BossEnemyState::Initialize(pScript);
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 6;
	frameEvent.animation = L"RealLaserWave";
	frameEvent.isRepeat = true;
	frameEvent.function = [pInstance]()
		{
			Sound::PlaySound("Voice_Sound_Voice_First_Attack4", (int)SoundGroup::FirstEnemy);
			Sound::PlaySound("Battle_Sound_Enemy_Common_Attack_Beam", (int)SoundGroup::Battle);
			pInstance->Attack();
		};
	pInstance->_pAnimation->AddFrameEvent(frameEvent);
	return pInstance;
}
