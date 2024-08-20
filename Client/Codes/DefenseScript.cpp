#include "DefenseScript.h"

#include "Effect.h"
#include "Grid.h"
#include "GridInfo.h"
#include "Tile.h"
#include "HP.h"
#include "HPHUD.h"
#include "ToolTip.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Client_Define.h"

DefenseScript::DefenseScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange, const wchar_t* type)
	:MonoBehavior(name), _name(type), _gridRange(gridRange)
{
	
}

void DefenseScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");

	if (_name == L"Defense_Generator") //발전기
		pCollider->SetScale(Vector3(90.f, 90.f, 0.f));
	else if (_name == L"Defense_Command")
		pCollider->SetScale(Vector3(190.f, 90.f, 0.f));

	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
	_pHP = GetComponent<HP>(L"HP");
	_pSpriteRenderer = GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer");
	_pToolTip = AddComponent<ToolTip>(L"name");
	if(_name==L"Defense_Generator") //발전기
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_002"), Vector3(-200.0f, -100.0f, 0.0f));
	else if(_name ==L"Defense_Command")
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_003"), Vector3(-200.0f, -100.0f, 0.0f));

	AddComponent<HPHUD>(_pHP, 0);
}

void DefenseScript::Start()
{
	_pOwner->_isDrawCollider = true;
	float x = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).x +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).x) / 2;
	float y = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).y +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).y) / 2;

	transform.position = Vector3(x, y, 0.f);
	for (int y = (int)_gridRange.first.y; y < (int)_gridRange.second.y + 1; y++)
	{
		for (int x = (int)_gridRange.first.x; x < (int)_gridRange.second.x + 1; x++)
		{
			_pGridInfo->GetGrid()->GetTiles()[y][x]->canMove = false;
		}
	}
	_gridPosition = { _gridRange.second.x, _gridRange.second.y ,0.f };
}

void DefenseScript::Update(const float& deltaTime)
{
}

void DefenseScript::LateUpdate(const float& deltaTime)
{
	_pSpriteRenderer->SetIndex((_pHP->GetMaxHP() - _pHP->hp));
	if (_isDestroy&& !_doDestoryEffect)
	{
		Explosion();
		_doDestoryEffect = true;
	}
}

void DefenseScript::Explosion()
{
	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = 0.03f;
	info.textureTag = L"Defense_Effect";
	info.position = _pOwner->transform.position;
	info.isFadeOut = true;
	info.life = 0.3f;
	info.fadeSpeed = 0.5f;
	info.scale = _pOwner->transform.scale*0.5f;

	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

void DefenseScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(true);
	}
	else if (*info.other==L"Attack")
	{
		if (!_pHP->IsInvinsible()) 
		{
			_pHP->hp--;
			if(_pHP->hp==0)
			{
				Sound::PlaySound("Effect_Sound_FX_Object_ProtectedBuilding_Break", (int)SoundGroup::SFX, 0.8f, false);
				std::string str = "Voice_Sound_Voice_Zero_Break_Tower" + std::to_string(Engine::RandomGeneratorInt(1, 2));
				Sound::StopSound((int)SoundGroup::Voice);
				Sound::PlaySound(str.c_str(), (int)SoundGroup::Voice, 0.8f, false);
				_isDestroy = true;
			}
			else
				Sound::PlaySound("Effect_Sound_FX_Object_ProtectedBuilding_Hit", (int)SoundGroup::SFX, 0.8f, false);
		}
	}
}

void DefenseScript::OnCollision(Engine::CollisionInfo& info)
{
}

void DefenseScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(false);
	}
}





