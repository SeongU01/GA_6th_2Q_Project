#include "Card.h"
#include "CardSystem.h"
#include "GameObject.h"

// CardEffect
#include "CardEffect.h"

// Component
#include "TextRenderer.h"
#include "Collider.h"
#include "PlayerMP.h"
#include "TimerSystem.h"
#include "Player.h"
#include "Grid.h"
#include "Effect.h"
#include "AdditiveState.h"
#include "GridMovement.h"
#include "JobQueue.h"
#include "AttackCollider.h"
#include "EventInvoker.h"
#include "HP.h"
#include "CardSystem.h"
#include "Animation.h"

#include "DataManager.h"
#include "Client_Define.h"


Card::Card(const CardData& cardData)
	: MonoBehavior(cardData.name.c_str()), _cardData(cardData)
{
}

void Card::Awake()
{
	// Component
	_pEventInvoker = AddComponent<Engine::EventInvoker>(L"EventInvoker");

	// 카드 기본 이미지 설정
	Engine::Texture* pTexture = Resource::FindTexture(L"Card");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindTexture(pTexture);
	pSpriteRenderer->SetIndex((int)_cardData.type);

	_pixelSize = pTexture->GetImage(0)->GetSize();

	// 카드 아이콘 설정
	pSpriteRenderer = AddComponent<Engine::SpriteRenderer>(L"Icons");
	pSpriteRenderer->BindTexture(Resource::FindTexture(L"Card_Icon"));
	pSpriteRenderer->SetIndex(_cardData.iconID);

	// 기본 위치
	transform.position = Vector3(-9999.f, -9999.f, 0.f);

	// 카드 이름
	Engine::TextRenderer* pTextRenderer = AddComponent<Engine::TextRenderer>(L"Title", D2D1::ColorF::White, 50.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetText(_cardData.name.c_str());
	pTextRenderer->SetDrawRect(450.f, 100.f);
	pTextRenderer->SetOffset(Vector3(-225.f, -50.f, 0.f));
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// 카드 코스트
	pTextRenderer = AddComponent<Engine::TextRenderer>(L"CostTime", D2D1::ColorF::Black, 70.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	pTextRenderer->SetOffset(Vector3(-280.f, -390.f, 0.f));
	pTextRenderer->SetDrawRect(200.f, 200.f);
	wchar_t buffer[16];

	int integer = (int)_cardData.costTime * 100;
	int hundredths = int(_cardData.costTime * 100);

	wsprintf(buffer, L"%d:%d", (int)_cardData.costTime, hundredths - integer);
	_costTime = buffer;
	pTextRenderer->SetText(_costTime.c_str());

	pTextRenderer = AddComponent<Engine::TextRenderer>(L"CostMana", 0x5555ff, 55.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	pTextRenderer->SetOffset(Vector3(-245.f, -314.f, 0.f));
	pTextRenderer->SetDrawRect(200.f, 100.f);

	wsprintf(buffer, L"[%d]", _cardData.costMana);
	_costMana = buffer;
	pTextRenderer->SetText(_costMana.c_str());

	_pCollider = AddComponent<Engine::Collider>(L"Card");	
	_pCollider->SetActive(false);
}

void Card::Start()
{
	_pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr);
	DataManager* pDataManager = DataManager::GetInstance();

	Player* pPlayer = _pPlayer->GetComponent<Player>();
		
	CardEffect::CardEffectInfo info;
	info.effectType = _cardData.effectType[0];
	info.ranges = pDataManager->GetAttackRange(_cardData.targetNum[0]);
	info.additiveFlag = (unsigned long long)1 << _cardData.additiveCharState[0];
	info.additiveStack = _cardData.charStateNum[0];
	_pCardEffect[0] = CardEffect::Create(pPlayer, info);

	if (CardEffectType::None != _cardData.effectType[1])
	{
		info.effectType = _cardData.effectType[1];
		info.ranges = pDataManager->GetAttackRange(_cardData.targetNum[1]);
		info.additiveFlag = (unsigned long long)1 << _cardData.additiveCharState[1];
		info.additiveStack = _cardData.charStateNum[1];
		_pCardEffect[1] = CardEffect::Create(pPlayer, info);
	}
}

void Card::Update(const float& deltaTime)
{
	if (_isLerp)
	{
		_lerpTime += Time::GetGlobalDeltaTime() / 0.3f;
		_offset = SmoothStep(_targetOffset[0], _targetOffset[1], _lerpTime);
	}
	if (_lerpTime >= 1.f)
	{
		_isLerp = false;
		_offset = _targetOffset[1];
	}	
}

void Card::LateUpdate(const float& deltaTime)
{
	if (_isHoldMouse)
	{
		_offset = { 0.f, -65.f, 0.f };
		_pCardEffect[0]->ShowRange();
	}

	transform.position = _fixPosition + _offset;
}

void Card::DrawCard()
{
	transform.scale = Vector3(0.34f, 0.34f, 0.f);
	_pCollider->SetScale({ _pixelSize.width, _pixelSize.height, 0.f });
	_pCollider->SetActive(true);

	_isLerp = true;
	_isThrow = false;
	_lerpTime = 0.f;
	_targetOffset[0] = { 1000.f, 0.f, 0.f };
	_targetOffset[1] = { 0.f, 0.f, 0.f };

	HandDeckSetting();
}

bool Card::ActiveMouseHover(bool isHover)
{
	if (_isAddQueue || _isThrow)
		return false;

	if (isHover)
	{
		_priority = 2000.f;
		_targetOffset[1] = { 0.f, -65.f, 0.f };
		transform.scale = Vector3(0.34f, 0.34f, 0.f) * 1.1f;
	}
	else
	{
		_priority = 0.f;
		_targetOffset[1] = { 0.f, 0.f, 0.f };
		transform.scale = Vector3(0.34f, 0.34f, 0.f);
	}

	_targetOffset[0] = _offset;
	_lerpTime = 0.f;
	_isLerp = true;

	return true;
}

void Card::ThrowCard()
{
	_isLerp = true;
	_isThrow = true;
	_lerpTime = 0.f;
	_targetOffset[0] = { 0.f, 0.f, 0.f };
	_targetOffset[1] = { -2000.f, 0.f, 0.f };
	_pCollider->SetScale({ -9999.f, -9999.f, 0.f });
}

void Card::Reset()
{
	transform.scale = Vector3(1.f, 1.f, 0.f);
	_pCollider->SetScale({ -9999.f, -9999.f, 0.f });
	gameObject.SetActive(false);
}

bool Card::AddJobQueue()
{
	if (!_isAddQueue)
	{
		PlayerMP* pMP = _pPlayer->GetComponent<PlayerMP>();
		TimerSystem* pTimerSystem = _pPlayer->GetComponent<TimerSystem>();

		if (pMP->mp < _cardData.costMana)
			return false;

		if (pTimerSystem->GetRemainingTime() < _cardData.costTime)
			return false;		

		_attackRange = _pCardEffect[0]->GetAttackRange();

		for (int i = 0; i < 2; i++)
		{			
			if (CardEffectType::PathMove == _cardData.effectType[i] || CardEffectType::PathAttack == _cardData.effectType[i])
			{
				Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();

				POINT mousePoint;
				GetCursorPos(&mousePoint);
				ScreenToClient(Engine::GetWindow(), &mousePoint);
				Vector3 currentGrid = pGrid->GetCurrGrid(Vector3((float)mousePoint.x, (float)mousePoint.y, 0.f));

				const Vector3& gridPosition = _pPlayer->GetComponent<Player>()->GetNextGridPosition();

				if (currentGrid.z >= 0)
				{
					bool isFind = false;
					for (auto& range : _attackRange)
					{
						int x = int(range.first + gridPosition.x);
						int y = int(range.second + gridPosition.y);

						if (CardEffectType::PathMove == _cardData.effectType[i])
						{
							if (!pGrid->IsTileWalkable(x, y))
								return false;
						}

						if ((int)currentGrid.x == x && (int)currentGrid.y == y
							&& pGrid->IsTileWalkable((int)currentGrid.x, (int)currentGrid.y))
						{
							isFind = true;
							_toGridPosition = currentGrid;
							_pPlayer->GetComponent<Player>()->SetNextGridPosition(_toGridPosition);
							break;
						}
					}

					if (!isFind)
						return false;
				}
				else
					return false;
			}

			if (CardAdditiveState::OverClock == _cardData.additiveCardState[i])
			{
				HP* pHP = _pPlayer->GetComponent<HP>();

				if (1 >= pHP->hp)
					return false;

				pHP->hp--;
			}
		}

		pMP->mp -= _cardData.costMana;
		pTimerSystem->UseTime(_cardData.costTime);
		_pPlayer->GetComponent<JobQueue>()->AddQueue(this);
		JobQueueSetting();
	}

	return true;
}

void Card::ActiveEffect()
{	
	Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	const Vector3& gridPosition = _pPlayer->GetComponent<Player>()->GetGridPosition();
	_pPlayer->GetComponent<Engine::Animation>()->ChangeAnimation(_cardActions[0].animation.c_str());

	int degree = (int)_pCardEffect[0]->GetAttackDegree();
	if (180 == degree)
		_pPlayer->transform.scale = { -1.f, 1.f, 0.f };
	else if (0 == degree)
		_pPlayer->transform.scale = { 1.f, 1.f, 0.f };

	if (CardEffectType::PathAttack != _cardData.effectType[0])
	{
		for (auto& action : _cardActions)
		{
			_pEventInvoker->BindAction(action.delay, [=]()
				{
					for (auto& range : _attackRange)
					{
						int x = int(range.first + gridPosition.x);
						int y = int(range.second + gridPosition.y);

						if (!action.isOneDraw)
							CreateEffect(action, pGrid->GetTileCenter(x, y));
					}

					if (action.isOneDraw)
					{
						CreateEffect(action, _pPlayer->transform.position);
					}
				});
		}
	}

	for (int i = 0; i < 2; i++)
	{
		AttackCollider* pAttackCollider = _pPlayer->GetComponent<Player>()->GetPlayerAttackComponent();
		AttackCollider::AttackInfo attackInfo;
		attackInfo.damage = _cardData.variable[i];
		attackInfo.additiveState = (unsigned long long)1 << _cardData.additiveCharState[i];
		attackInfo.additiveStateStack = _cardData.charStateNum[i];

		if (CardEffectType::PathAttack == _cardData.effectType[i])
		{
			const Vector3& toGridPosition = _toGridPosition;

			auto handlePathAttack = [=](int fixedCoord, int start, int end, bool isXAxis)
				{
					for (int j = start; j < end; j++)
					{						
						auto pEffect = Engine::GameObject::Create();
						Effect::EffectInfo info;
						info.renderGroup = RenderGroup::FrontEffect;
						info.aniSpeed = 0.05f;
						info.scale = { 0.75f, 0.75f, 1.f };
						info.textureTag = L"Effect_Hit_Hit02";

						if (isXAxis)
							info.position = pGrid->GetTileCenter(j, fixedCoord);
						else
							info.position = pGrid->GetTileCenter(fixedCoord, j);

						pEffect->AddComponent<Effect>(info);
						Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);

						pEffect = Engine::GameObject::Create();
						info.textureTag = L"Effect_Hit_Hit03";

						pEffect->AddComponent<Effect>(info);
						Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);

						if (isXAxis)
							pAttackCollider->OnCollider(0.f, 0.1f, j, fixedCoord, attackInfo, i);
						else
							pAttackCollider->OnCollider(0.f, 0.1f, fixedCoord, j, attackInfo, i);
					}
				};

			_pEventInvoker->BindAction(0.5f, [=]()
				{
					if ((int)gridPosition.x == (int)toGridPosition.x)
					{
						int start = min((int)gridPosition.y, (int)toGridPosition.y);
						int end = max((int)gridPosition.y, (int)toGridPosition.y);

						if (start == (int)toGridPosition.y)
						{
							start++;
							end++;
						}

						handlePathAttack((int)gridPosition.x, start, end, false);
					}
					else if ((int)gridPosition.y == (int)toGridPosition.y)
					{
						int start = min((int)gridPosition.x, (int)toGridPosition.x);
						int end = max((int)gridPosition.x, (int)toGridPosition.x);

						if (start == (int)toGridPosition.x)
						{
							start++;
							end++;
						}

						handlePathAttack((int)gridPosition.y, start, end, true);
					}
				});
		}

		if (CardEffectType::PathMove == _cardData.effectType[i] || CardEffectType::PathAttack == _cardData.effectType[i])
		{
			_pEventInvoker->BindAction(0.25f, [=]()
				{
					_pPlayer->GetComponent<Player>()->SetGridPostion(_toGridPosition);
					_pPlayer->GetComponent<GridMovement>()->MoveToCell(_toGridPosition, 0.2f);
				});			
		}		

		if (CardEffectType::RangeAttack == _cardData.effectType[i])
		{						
			for (auto& action : _cardActions)
			{
				_pEventInvoker->BindAction(action.delay, [=]()
					{
						for (auto& range : _attackRange)
						{
							int x = int(range.first + gridPosition.x);
							int y = int(range.second + gridPosition.y);

							pAttackCollider->OnCollider(action.attackDelay, 0.1f, x, y, attackInfo, i);
						}
					});
			}
		}

		if (CardEffectType::RangeCast == _cardData.effectType[i])
		{
			Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
			const Vector3& gridPosition = _pPlayer->GetComponent<Player>()->GetGridPosition();

			for (auto& range : _attackRange)
			{
				pAttackCollider->OnCollider(0.f, 0.1f, int(range.first + gridPosition.x), int(range.second + gridPosition.y), attackInfo, i);
			}
		}

		if (CardEffectType::SelfCast == _cardData.effectType[i])
		{
			AdditiveState* pAdditiveState = _pPlayer->GetComponent<AdditiveState>();
			pAdditiveState->AddState((unsigned long long)1 << _cardData.additiveCharState[i], _cardData.charStateNum[i]);
		}

		if (CardEffectType::Reload == _cardData.effectType[i])
		{
			CardSystem* pCardSystem = _pPlayer->GetComponent<CardSystem>();
			pCardSystem->OnReloadCoolTime();
			pCardSystem->ReloadCard();
		}

		if (CardEffectType::Draw == _cardData.effectType[i])
		{
			_pPlayer->GetComponent<CardSystem>()->DrawCard();
		}
	}

	_isLerp = true;
	_lerpTime = 0.f;
	_targetOffset[0] = { 0.f, 0.f, 0.f };
	_targetOffset[1] = { 250.f, 0.f, 0.f };
}

void Card::SetHoldCard(bool isActive)
{
	_isHoldMouse = isActive;
}

Vector3 Card::SmoothStep(const XMVECTOR& v0, const XMVECTOR& v1, float t)
{
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
	t = t * t * (3.f - 2.f * t);
	return XMVectorLerp(v0, v1, t);
}

void Card::HandDeckSetting()
{
	// 카드 이미지
	GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer")->SetIndex((int)_cardData.type);

	// 아이콘
	GetComponent<Engine::SpriteRenderer>(L"Icons")->SetDrawOffset(Vector3(0.f, 0.f, 0.f));

	// 카드 이름
	GetComponent<Engine::TextRenderer>(L"Title")->SetActive(true);

	// 카드 코스트
	auto costTime = GetComponent<Engine::TextRenderer>(L"CostTime");
	costTime->SetOffset(Vector3(-280.f, -390.f, 0.f));
	costTime->SetDrawRect(200.f, 200.f);
	
	auto costMana = GetComponent<Engine::TextRenderer>(L"CostMana");
	costMana->SetOffset(Vector3(-245.f, -314.f, 0.f));
	costMana->SetDrawRect(200.f, 100.f);

	GetComponent<Engine::TextRenderer>(L"OptionText")->SetActive(true);
}

void Card::JobQueueSetting()
{
	_isLerp = false;
	_lerpTime = 0.f;
	_offset = { 0.f, 0.f, 0.f };

	// 카드 이미지
	GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer")->SetIndex((int)_cardData.type + 3);

	// 아이콘
	GetComponent<Engine::SpriteRenderer>(L"Icons")->SetDrawOffset(Vector3(0.f, 200.f, 0.f));

	// 카드 이름
	GetComponent<Engine::TextRenderer>(L"Title")->SetActive(false);

	// 카드 코스트
	auto costTime = GetComponent<Engine::TextRenderer>(L"CostTime");
	costTime->SetOffset(Vector3(-280.f, -160.f, 0.f));
	costTime->SetDrawRect(200.f, 200.f);

	auto costMana = GetComponent<Engine::TextRenderer>(L"CostMana");
	costMana->SetOffset(Vector3(-245.f, -84.f, 0.f));
	costMana->SetDrawRect(200.f, 100.f);

	GetComponent<Engine::TextRenderer>(L"OptionText")->SetActive(false);

	_isAddQueue = true;
}

void Card::CreateEffect(const Card::CardAction& action, const Vector3& offset)
{
	float degree = _pCardEffect[0]->GetAttackDegree();

	auto pEffect = Engine::GameObject::Create();
	Effect::EffectInfo info;
	info.renderGroup = RenderGroup::FrontEffect;
	info.aniSpeed = action.duration;
	info.textureTag = action.effectTag.c_str();
	info.position = offset + XMVector3TransformCoord(Vector3(action.position), XMMatrixRotationZ(XMConvertToRadians(degree)));
	info.scale = action.scale;

	if (action.isRotation)
		info.rotation = degree;

	if (action.isFollow)
	{
		info.position -= _pPlayer->transform.position;
		info.pTarget = &_pPlayer->transform;

		if (0.f > _pPlayer->transform.scale.x)
			info.scale.x *= -1.f;
	}

	pEffect->AddComponent<Effect>(info);
	Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
}

void Card::Free()
{
	for (int i = 0; i < 2; i++)
		SafeRelease(_pCardEffect[i]);
}