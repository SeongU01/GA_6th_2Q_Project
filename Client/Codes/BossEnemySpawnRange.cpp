#include "BossEnemySpawnRange.h"
#include "BossEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "Effect.h"
#include "GridEffect.h"
#include "Attribute.h"
#include "GridMovement.h"
#include "Grid.h"
#include "RangeEnemy.h"

#include "Client_Define.h"
int BossEnemySpawnRange::Update(const float& deltaTime)
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
			_pAnimation->ChangeAnimation(L"SpawnRange");
			//TODO : 공격하기. 피해 1, 허점부여
			_isStateOn = true;
		}

	}
	return 0;
}

int BossEnemySpawnRange::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"SpawnRange"))
	{
		return (int)BossEnemy::FSM::Idle;
	}

	return 0;
}

void BossEnemySpawnRange::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = 1.f;
}

void BossEnemySpawnRange::OnExit()
{
	CloseInfo();
}

void BossEnemySpawnRange::ShowInfo()
{
	__super::ShowInfo();
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowSpawnRange();
	}
	_pTextRenderer->SetOffset(Vector3(-60.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Spawn] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void BossEnemySpawnRange::CloseInfo()
{
	__super::CloseInfo();
}

void BossEnemySpawnRange::Spawn()
{
	Vector3 spawnPos;
	if (0 == _spawnCount)
	{
		spawnPos = { 3.f,1.f,0.f };

		RangeEnemy* rangeEnemy = RangeEnemy::Create(spawnPos, L"player");
		Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Monster", rangeEnemy);
		SpawnEffect(spawnPos);

		spawnPos = { 13.f,6.f,0.f };

		RangeEnemy* rangeEnemy2 = RangeEnemy::Create(spawnPos, L"player");
		Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Monster", rangeEnemy2);
		SpawnEffect(spawnPos);
	}
	else
	{
		spawnPos = { 14.f,5.f,0.f };

		RangeEnemy* rangeEnemy = RangeEnemy::Create(spawnPos, L"player");
		Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Monster", rangeEnemy);
		SpawnEffect(spawnPos);

		spawnPos = { 2.f,2.f,0.f };

		RangeEnemy* rangeEnemy2 = RangeEnemy::Create(spawnPos, L"player");
		Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Monster", rangeEnemy2);
		SpawnEffect(spawnPos);
	}
	_spawnCount++;
}

void BossEnemySpawnRange::ShowSpawnRange()
{
	int index = 1;
	if (_spawnCount == 1)
	{
		_pGridEffect->OnEffect(3,1 , index);
		_pGridEffect->OnEffect(13,6 , index);
	}
	else
	{
		_pGridEffect->OnEffect(14,5, index);
		_pGridEffect->OnEffect(2,2, index);
	}
}

void BossEnemySpawnRange::SpawnEffect(const Vector3& Position)
{
	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.05f;
	info.textureTag = L"Enemy_SpawnEffect";
	info.position = _pMovement->_grid->GetTileCenter((int)Position.x, (int)Position.y) + Vector3(0.f, -40.f, 0.f);
	info.isFadeOut = true;
	info.life = 0.3f;
	info.fadeSpeed = 0.5f;
	info.scale = _pOwner->transform.scale;

	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

BossEnemySpawnRange* BossEnemySpawnRange::Create(BossEnemyScript* pScript)
{
	BossEnemySpawnRange* pInstance = new BossEnemySpawnRange;
	pInstance->BossEnemyState::Initialize(pScript);
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 6;
	frameEvent.animation = L"SpawnRange";
	frameEvent.isRepeat = true;
	frameEvent.function = [pInstance]()
		{
			Sound::PlaySound("Battle_Sound_Enemy_Elite_Attack_Weakness", (int)SoundGroup::Battle, 0.8f, false);
			pInstance->Spawn();
		};
	pInstance->_pAnimation->AddFrameEvent(frameEvent);
	return pInstance;
}

