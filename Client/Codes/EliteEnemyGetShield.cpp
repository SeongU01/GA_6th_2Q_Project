#include "EliteEnemyGetShield.h"
#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "Player.h"
#include "DefenseScript.h"

#include "DataManager.h"
#include "Client_Define.h"
int EliteEnemyGetShield::Update(const float& deltaTime)
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
			_pAnimation->ChangeAnimation(L"Up");
			//TODO : ½¯µå ¾ò±â
			_isStateOn = true;
		}

	}
	return 0;
}

int EliteEnemyGetShield::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Up"))
	{
		return (int)EliteEnemy::FSM::Idle;
	}
	return 0;
}

void EliteEnemyGetShield::OnStart()
{
  _directionCheck = false;
  _isStateOn = false;
  _currTime = 0.f;
  _delayTime = (float)Engine::RandomGeneratorInt(3,5);
}

void EliteEnemyGetShield::OnExit()
{
	
}

void EliteEnemyGetShield::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Shield] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemyGetShield::CloseInfo()
{
	__super::CloseInfo();
}


EliteEnemyGetShield* EliteEnemyGetShield::Create(EliteEnemyScript* pScript)
{
  EliteEnemyGetShield* pInstance = new EliteEnemyGetShield;
  pInstance->EliteEnemyState::Initialize(pScript);
  return pInstance;
}
