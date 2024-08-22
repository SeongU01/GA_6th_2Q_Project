#include "BossEnemyScript.h"
#include "Grid.h"
#include "Tile.h"
//component
#include "FiniteStateMachine.h"
#include "Animation.h"
#include "GridMovement.h"
#include "Astar.h"
#include "HP.h"
#include "HPHUD.h"
#include "TopHUD.h"
#include "TextRenderer.h"
#include "Collider.h"
#include "Pannel.h"
#include "ToolTip.h"
#include "Defense.h"
#include "DefenseScript.h"
#include "Zero.h"
#include "Player.h"
#include "TextRenderer.h"
#include "Attribute.h"
#include "AttributeHUD.h"
#include "AttackCollider.h"
#include "Spectrum.h"
#include "HitColor.h"

//state
#include "BossEnemyIdle.h"
#include "BossEnemyMove.h"
#include "BossEnemySonicStab.h"
#include "BossEnemyMeteorSlash.h"
#include "BossEnemyRealMeteorSlash.h"
#include "BossEnemyLaserWave.h"
#include "BossEnemyRealLaserWave.h"
#include "BossEnemyReadyMove.h"
#include "BossEnemyLaserBurst.h"
#include "BossEnemySpawnRange.h"
#include "BossEnemyDeath.h"

#include "BossEnemyInformation.h"
#include "Client_Define.h"

BossEnemyScript::BossEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name),_startPosition(startPos), _targetObjectName(_targetName)
{
}

void BossEnemyScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetScale(Vector3(90.f, 90.f, 0.f));

	//_pOwner->_isDrawCollider = true;

	_pHP = AddComponent<HP>(L"HP", 15);
	AddComponent<HPHUD>(_pHP, 1);

	_aStar = AddComponent<AStar>(L"AStar", _targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement", 500.f);

	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Boss_BossEnemy"))
		throw std::runtime_error("can't load animation!");
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);

	Pannel::PannelInfo info;
	info.parent = &transform;
	info.position = Vector3(0.f, -170.f, 0.f);
	info.size = Vector3{ 200, 50, 0 }; //크기
	info.fillColor = 0x99AEAEAE; //색상
	info.outlineColor = 0xFF000000; //테두리 색상
	info.opacity = 0.4f;
	_pPannel = Pannel::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Ememyinfo", _pPannel);
	_pPannel->AddComponent<Engine::TextRenderer>(L"TextRenderer", D2D1::ColorF::Black, 20.f, DWRITE_FONT_WEIGHT_BOLD);
	_pPannel->SetActive(false);

	_pToolTip = AddComponent<ToolTip>(L"EliteToolTip");
	_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Character_003"), Vector3(0.0f, 0.0f, 0.0f));

	_pSpectrum = AddComponent<Spectrum>(0.1f, Vector3(20.f, -100.f, 0.f), Vector3(1.f, 1.f, 1.f));
	_pSpectrum->SetColor(XMFLOAT4(0.f, 0.f, 0.f, 0.f), XMFLOAT4(0.578f, 0.0859f, 0.1171875f, 1.f));	

	// 임시 추가한것
	_pAttribute = AddComponent<Attribute>();
	_pAttackCollider = AddComponent<AttackCollider>();
	AddComponent<AttributeHUD>(_pAttribute);
	AddComponent<HitColor>();

	// TOPHUD
	_pTopHud = Engine::GameObject::Create();
	_pTopHud->transform.SetPosition(Vector3{ 782.0f,40.0f,0.0f });
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"BossTopHP", _pTopHud);
	TopHUD* pTopHud = _pTopHud->AddComponent<TopHUD>(_pHP, 2);
	pTopHud->SetDontDestroyObjectUI(false);
	_pTopHud->SetRenderGroup((int)RenderGroup::UI);
	Engine::SpriteRenderer* name = _pTopHud->AddComponent<Engine::SpriteRenderer>(L"firstminute");
	name->BindTexture(Resource::FindTexture(L"UI_Text"));
	name->SetIndex(4);
	name->SetDrawOffset(Vector3(180.f, 75.0f, 0.f));
/*	Engine::TextRenderer* text = _pTopHud->AddComponent<Engine::TextRenderer>(L"Content", D2D1::ColorF::White, 20.f, DWRITE_FONT_WEIGHT_EXTRA_LIGHT);
	text->SetTextLayout(L"\"퍼스트 미닛\"", 250.f, 0.f);
	text->SetTextRangeEffectFontFamily(0, lstrlen(L"\"퍼스트 미닛\""), L"HY견고딕");
	text->SetOffset(Vector3(110.f, 55.0f, 0.f));
	text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)*/;

	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 1;
	frameEvent.animation = L"ReadyMove";
	frameEvent.function = [this]() {
		_pSpectrum->SetActive(true);
		};
	frameEvent.isRepeat = true;
	_pAnimation->AddFrameEvent(frameEvent);
	frameEvent.activeFrame = 11;
	frameEvent.function = [this]() {
		_pSpectrum->SetActive(false);
		};
	_pAnimation->AddFrameEvent(frameEvent);
}

void BossEnemyScript::Start()
{
	_pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>();
	_gridPosition = _startPosition;
	_aStar->SetGridMovement(_movement);
	_aStar->SetGridPosition(_startPosition);
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	pGrid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x]->canMove = false;

	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)BossEnemy::FSM::End);
	_pFSM->AddState((int)BossEnemy::FSM::Idle, BossEnemyIdle::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::Move, BossEnemyMove::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::SonicStab, BossEnemySonicStab::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::MeteorSlash, BossEnemyMeteorSlash::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::RealMeteorSlash, BossEnemyRealMeteorSlash::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::LaserWave, BossEnemyLaserWave::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::RealLaserWave, BossEnemyRealLaserWave::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::ReadyMove, BossEnemyReadyMove::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::LaserBurst, BossEnemyLaserBurst::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::SpawnRange, BossEnemySpawnRange::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::Death, BossEnemyDeath::Create(this));
	_pFSM->ChangeState((int)BossEnemy::FSM::Idle);

	Sound::PlaySound("Voice_Sound_Voice_Operator_Spawn_Boss", (int)SoundGroup::Operator);
}

void BossEnemyScript::Update(const float& deltaTime)
{
}

void BossEnemyScript::LateUpdate(const float& deltaTime)
{
	if (_pHP->IsZeroHP())
	{
		if (!_eraseTopHud)
		{
			_eraseTopHud = true;
			_pTopHud->SetDead();
			std::string str = "Voice_Sound_Voice_First_HP_0_" + std::to_string(Engine::RandomGeneratorInt(1, 3));
			Sound::PlaySound(str.c_str(), (int)SoundGroup::FirstEnemy, 1.0f, false);
		}
		_pFSM->ChangeState((int)BossEnemy::FSM::Death);
	}
}

void BossEnemyScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
}

void BossEnemyScript::OnCollision(Engine::CollisionInfo& info)
{
}

void BossEnemyScript::OnCollisionExit(Engine::CollisionInfo& info)
{
}
