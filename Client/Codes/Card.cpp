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

#include "CardManager.h"
#include "Client_Define.h"


Card::Card(const CardData& cardData)
	: MonoBehavior(cardData.name.c_str()), _cardData(cardData)
{
}

void Card::Awake()
{
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
	CardManager* pCardManager = CardManager::GetInstance();

	Player* pPlayer = _pPlayer->GetComponent<Player>();
		
	CardEffect::CardEffectInfo info;
	info.effectType = _cardData.effectType[0];
	info.ranges = pCardManager->GetAttackRange(_cardData.targetNum[0]);
	info.additiveFlag = (unsigned long long)1 << _cardData.additiveCharState[0];
	info.additiveStack = _cardData.charStateNum[0];
	_pCardEffect[0] = CardEffect::Create(pPlayer, info);

	if (CardEffectType::None != _cardData.effectType[1])
	{
		info.effectType = _cardData.effectType[1];
		info.ranges = pCardManager->GetAttackRange(_cardData.targetNum[1]);
		info.additiveFlag = (unsigned long long)1 << _cardData.additiveCharState[1];
		info.additiveStack = _cardData.charStateNum[1];
		_pCardEffect[1] = CardEffect::Create(pPlayer, info);
	}
}

void Card::Update(const float& deltaTime)
{
	if (_isLerp)
	{
		_lerpTime += deltaTime / 0.3f;
		_offset = SmoothStep(_targetOffset[0], _targetOffset[1], _lerpTime);
	}
	if (_lerpTime >= 1.f)
	{
		_isLerp = false;
		_isThrow = false;
		_offset = _targetOffset[1];
	}	
}

void Card::LateUpdate(const float& deltaTime)
{
	if (_isHoldMouse)
	{
		_offset = { 0.f, -65.f, 0.f };
		_pCardEffect[0]->ShowRange();
		//if (_pCardEffect[1]) _pCardEffect[1]->ShowRange();
	}

	transform.position = _handDeckPosition + _offset;
}

void Card::DrawCard()
{
	transform.scale = Vector3(0.34f, 0.34f, 0.f);
	_pCollider->SetScale({ _pixelSize.width, _pixelSize.height, 0.f });
	_pCollider->SetActive(true);

	_isLerp = true;
	_lerpTime = 0.f;
	_targetOffset[0] = { 1000.f, 0.f, 0.f };
	_targetOffset[1] = { 0.f, 0.f, 0.f };
}

void Card::SetMouseHover(bool isHover)
{
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

bool Card::ActiveEffect()
{
	PlayerMP* pMP = _pPlayer->GetComponent<PlayerMP>();
	TimerSystem* pTimerSystem = _pPlayer->GetComponent<TimerSystem>();

	if (pMP->mp < _cardData.costMana)
		return false;

	if (pTimerSystem->GetRemainingTime() < _cardData.costTime)
		return false;

	pMP->mp -= _cardData.costMana;
	pTimerSystem->UseTime(_cardData.costTime);

	std::vector<std::pair<int, int>> attackRange = _pCardEffect[0]->GetAttackRange();
	
	if (CardEffectType::PathMove == _cardData.effectType[0])
	{
		Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();

		POINT mousePoint;
		GetCursorPos(&mousePoint);
		ScreenToClient(Engine::GetWindow(), &mousePoint);
		Vector3 currentGrid = pGrid->GetCurrGrid(Vector3((float)mousePoint.x, (float)mousePoint.y, 0.f));

		if (currentGrid.z >= 0)
		{
			bool isFind = false;
			for (auto& range : attackRange)
			{
				if (currentGrid.x == range.first && currentGrid.y == range.second
					&&pGrid->IsTileWalkable(currentGrid.x,currentGrid.y))
				{
					_pPlayer->GetComponent<Player>()->SetGridPostion(currentGrid);
					_pPlayer->GetComponent<GridMovement>()->MoveToCell(
						_pPlayer->GetComponent<Player>()->GetGridPosition(), 0.5f);
					isFind = true;
					break;
				}
			}

			if (!isFind)
				return false;
		}
	}

	if (CardEffectType::RangeAttack == _cardData.effectType[0])
	{
		Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
		for (auto& range : attackRange)
		{
			auto pEffect = Engine::GameObject::Create();
			Effect::EffectInfo info;
			info.renderGroup = RenderGroup::FrontEffect;
			info.aniSpeed = 0.05f;
			info.textureTag = L"Effect";
			info.position = pGrid->GetTileCenter(range.first, range.second);
			pEffect->AddComponent<Effect>(info);
			Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (CardEffectType::SelfCast == _cardData.effectType[i])
		{
			AdditiveState* pAdditiveState = _pPlayer->GetComponent<AdditiveState>();
			pAdditiveState->AddState(1 << _cardData.additiveCharState[i], _cardData.charStateNum[i]);
		}
	}

	return true;
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

void Card::Free()
{
	SafeRelease(_pCardEffect[0]);
}
