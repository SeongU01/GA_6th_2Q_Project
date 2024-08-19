#include "EliteEnemyGetShield.h"
#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "Player.h"
#include "DefenseScript.h"
#include "Attribute.h"
#include "Effect.h"

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
			GetShield();
			_isStateOn = true;
		}

	}
	return 0;
}

int EliteEnemyGetShield::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

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
	CloseInfo();
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
  Engine::Animation::FrameEvent frameEvent;
  frameEvent.activeFrame = 6;
  frameEvent.animation = L"Up";
  frameEvent.isRepeat = true;
  frameEvent.function = [pInstance]()
	  {
		  Sound::StopSound((int)SoundGroup::Battle);
		  Sound::PlaySound("Battle_Sound_Enemy_Elite_Assist_Shield", (int)SoundGroup::Battle, 0.8f, false);
	  };
  pInstance->_pAnimation->AddFrameEvent(frameEvent);
  return pInstance;
}

void EliteEnemyGetShield::GetShield()
{
	Attribute* pAttribute = _pOwner->GetComponent<Attribute>();
	pAttribute->AddState(AttributeFlag::Shield, 1);

	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.05f;
	info.textureTag = L"AIEffect_Buff";
	info.scale = _pOwner->transform.scale*1.5f;
	info.position = _pOwner->transform.position+Vector3(0.f,-50.f,0.f);
	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}
