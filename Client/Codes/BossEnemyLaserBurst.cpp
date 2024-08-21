#include "BossEnemyLaserBurst.h"
#include "BossEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "AttackCollider.h"
#include "Effect.h"
#include "GridEffect.h"
#include "Attribute.h"
#include "GridMovement.h"
#include "Grid.h"

#include "Client_Define.h"
int BossEnemyLaserBurst::Update(const float& deltaTime)
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
			_pAnimation->ChangeAnimation(L"LaserBurst");
			//TODO : 공격하기. 피해 1, 허점부여
			_isStateOn = true;
		}

	}
	return 0;
}

int BossEnemyLaserBurst::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn && !_useAttack)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"LaserBurst"))
	{
		CloseInfo();
		_useAttack = true;
		_pAnimation->ChangeAnimation(L"Idle");
	}

	if (_useAttack)
	{
		_relaxTime += deltaTime;
		if (_relaxTime >= 1.f)
		{
			
			_relaxTime = 0.f;
			return (int)BossEnemy::FSM::Idle;
		}
	}
	return 0;
}

void BossEnemyLaserBurst::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(2, 3);
}

void BossEnemyLaserBurst::OnExit()
{
}

void BossEnemyLaserBurst::ShowInfo()
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

void BossEnemyLaserBurst::CloseInfo()
{
	__super::CloseInfo();
}

void BossEnemyLaserBurst::Attack()
{
	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	
	AttackCollider* pAttackCollider = _pOwner->GetComponent<AttackCollider>();
	AttackCollider::AttackInfo attackInfo;
	if (_pAttribute->IsActiveState(AttributeFlag::HighPower))
	{
		_pAttribute->UseStack(Attribute::HighPower);
		attackInfo.damage = 3;
	}
	else
	{
		attackInfo.damage = 2;
	}
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(20);
	if (_currDirection.x >= 0)
	{
		for (auto& range : ranges)
		{
			int x = int(range.first + gridPosition.x);
			int y = int(range.second + gridPosition.y);
			pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);

			auto pEffect = Engine::GameObject::Create();
			Effect::EffectInfo info;
			info.textureTag= L"AIEffect_Attack_Anim_VFX_BeamDrop_02_E";
			info.aniSpeed = 0.03f;
			info.scale = _pOwner->transform.scale*0.1f;
			info.renderGroup = RenderGroup::FrontEffect;
			info.position = _pMovement->_grid->GetTileCenter(x, y) + Vector3(0.f, -70.f, 0.f);
			pEffect->AddComponent<Effect>(info);
			Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
		}
	}
	else
	{
		for (auto& range : ranges)
		{
			int x = int(gridPosition.x - range.first);
			int y = int(range.second + gridPosition.y);
			pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);

			auto pEffect = Engine::GameObject::Create();
			Effect::EffectInfo info;
			info.textureTag = L"AIEffect_Attack_Anim_VFX_BeamDrop_02_E";
			info.aniSpeed = 0.03f;
			info.scale = _pOwner->transform.scale * 0.1f;
			info.renderGroup = RenderGroup::FrontEffect;
			info.position = _pMovement->_grid->GetTileCenter(x, y) + Vector3(0.f, -70.f, 0.f);
			pEffect->AddComponent<Effect>(info);
			Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
		}
	}

	Camera::CameraShake(0.2f, 150.f);
}

void BossEnemyLaserBurst::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(20);
	int index = 1;

	for (auto& grid : ranges)
	{
		if (_currDirection.x >= 0)
			_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
		else
			_pGridEffect->OnEffect(int(gridPosition.x - grid.first), int(gridPosition.y + grid.second), index);

	}
}

BossEnemyLaserBurst* BossEnemyLaserBurst::Create(BossEnemyScript* pScript)
{
	BossEnemyLaserBurst* pInstance = new BossEnemyLaserBurst;
	pInstance->BossEnemyState::Initialize(pScript);
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 6;
	frameEvent.animation = L"LaserBurst";
	frameEvent.isRepeat = true;
	frameEvent.function = [pInstance]()
		{
			Sound::PlaySound("Battle_Sound_Enemy_Elite_Attack_Weakness", (int)SoundGroup::Battle, 0.8f, false);
			pInstance->Attack();
		};
	pInstance->_pAnimation->AddFrameEvent(frameEvent);
	return pInstance;
}
