#include "EliteEnemyWeekSearch.h"

#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "Player.h"
#include "DefenseScript.h"
#include "AttackCollider.h"
#include "Effect.h"

#include "DataManager.h"
#include "Client_Define.h"
int EliteEnemyWeekSearch::Update(const float& deltaTime)
{
	if (_directionCheck == false)
	{
		if (CheckRange(5, 2))
		{
			_pTargetPosition = &_pPlayer->GetGridPosition();
		}
		else
		{
			_pTargetPosition = &_pDefense->GetGridPosition();
		}
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
			_pAnimation->ChangeAnimation(L"Stab");
			//TODO : �����ϱ�. ���� 1, �����ο�
			_isStateOn = true;
		}

	}
	return 0;
}

int EliteEnemyWeekSearch::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Stab"))
	{
		return (int)EliteEnemy::FSM::Idle;
	}
	return 0;
}

void EliteEnemyWeekSearch::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void EliteEnemyWeekSearch::OnExit()
{
}

void EliteEnemyWeekSearch::ShowInfo()
{
	__super::ShowInfo();
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}
	_pTextRenderer->SetOffset(Vector3(-70.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[WeekFind] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemyWeekSearch::CloseInfo()
{
	__super::CloseInfo();
}

void EliteEnemyWeekSearch::Attack()
{
	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.03f;
	info.textureTag = L"AIEffect_Attack_Anim_VFX_Stab_E_Anim_VFX_Stab_01_E";
	info.scale = _pOwner->transform.scale;


	AttackCollider* pAttackCollider = _pOwner->GetComponent<AttackCollider>();
	AttackCollider::AttackInfo attackInfo;
	attackInfo.damage = 1;
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(16);
	if (_currDirection.x >= 0)
	{
		info.position = _pOwner->transform.position + Vector3(90.f, -30.f, 0.f);
		for (auto& range : ranges)
		{
			int x = int(range.first + gridPosition.x);
			int y = int(range.second + gridPosition.y);
			pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);
		}
	}
	else
	{
		info.position = _pOwner->transform.position + Vector3(-90.f, -30.f, 0.f);
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

void EliteEnemyWeekSearch::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(16);
	int index = 1;

	for (auto& grid : ranges)
	{
		if (_currDirection.x >= 0)
			_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
		else
			_pGridEffect->OnEffect(int(gridPosition.x - grid.first), int(gridPosition.y + grid.second), index);

	}
}

EliteEnemyWeekSearch* EliteEnemyWeekSearch::Create(EliteEnemyScript* pScript)
{
	EliteEnemyWeekSearch* pInstance = new EliteEnemyWeekSearch;
	pInstance->EliteEnemyState::Initialize(pScript);
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 6;
	frameEvent.animation = L"Stab";
	frameEvent.isRepeat = true;
	frameEvent.function = [pInstance]()
		{
			pInstance->Attack();
		};
	pInstance->_pAnimation->AddFrameEvent(frameEvent);
	return pInstance;
}
