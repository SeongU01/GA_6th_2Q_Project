#include "RangeEnemyAttack.h"
#include "RangeEnemyScript.h"
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
int RangeEnemyAttack::Update(const float& deltaTime)
{
	if (_directionCheck == false)
	{
		const Vector3& gridPosition = *_pGridPosition;
		Vector3 Direction = _pPlayer->GetGridPosition() - gridPosition;

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
			_pAnimation->ChangeAnimation(L"Attack");
			//TODO : 공격하기. 피해 1, 허점부여
			_isStateOn = true;
		}

	}
	return 0;
}

int RangeEnemyAttack::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Attack"))
	{
		return (int)RangeEnemy::FSM::Idle;
	}
	return 0;
}

void RangeEnemyAttack::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void RangeEnemyAttack::OnExit()
{
	CloseInfo();
}

void RangeEnemyAttack::ShowInfo()
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

void RangeEnemyAttack::CloseInfo()
{
	__super::CloseInfo();
}

void RangeEnemyAttack::Attack()
{
	auto pEffect = Engine::GameObject::Create();

	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.03f;
	info.textureTag = L"AIEffect_Attack_Anim_VFX_Beam_E";
	info.scale = _pOwner->transform.scale;

	AttackCollider* pAttackCollider = _pOwner->GetComponent<AttackCollider>();
	AttackCollider::AttackInfo attackInfo;


	attackInfo.damage = 1;
	
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(2);
	if (_currDirection.x >= 0)
	{
		info.position = _pOwner->transform.position + Vector3(1000.f, 0.f, 0.f);
		for (auto& range : ranges)
		{
			int x = int(range.first + gridPosition.x);
			int y = int(range.second + gridPosition.y);
			pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);
		}
	}
	else
	{
		info.position = _pOwner->transform.position - Vector3(1000.f, 0.f, 0.f);
		for (auto& range : ranges)
		{
			int x = int(gridPosition.x - range.first);
			int y = int(range.second + gridPosition.y);
			pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);
		}
	}

	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

void RangeEnemyAttack::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(2);
	int index = 7;
	for (auto& grid : ranges)
	{
		if (_currDirection.x >= 0)
			_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
		else
			_pGridEffect->OnEffect(int(gridPosition.x - grid.first), int(gridPosition.y + grid.second), index);

	}
}

RangeEnemyAttack* RangeEnemyAttack::Create(RangeEnemyScript* pScript)
{
	RangeEnemyAttack* pInstance = new RangeEnemyAttack;
	pInstance->RangeEnemyState::Initialize(pScript);
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 5;
	frameEvent.animation = L"Attack";
	frameEvent.isRepeat = true;
	frameEvent.function = [pInstance]()
		{
			Sound::PlaySound("Battle_Sound_Enemy_Common_Attack_Beam", (int)SoundGroup::Battle);
			pInstance->Attack();
		};
	pInstance->_pAnimation->AddFrameEvent(frameEvent);
	return pInstance;
}
