#include "DeckSystem.h"
#include "Pannel.h"
#include "CardSystem.h"

//Component
#include "Button.h"
#include "TextRenderer.h"

#include "Client_Define.h"

DeckSystem::DeckSystem()
	: UIComponent(L"DeckSystem")
{
}

void DeckSystem::Awake()
{	
	Pannel::PannelInfo info;
	info.fillColor = 0xffffff;
	info.outlineColor = 0x000000;
	info.parent = &transform;
	info.size = { 300.f, 200.f };
	info.position = { 0.f, 0.f, -1.f };
	info.opacity = 1.f;
	info.lineWidth = 2.f;

	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Pannel", Pannel::Create(info));

	info.size = { 150.f, 150.f };
	info.position = { -75.f, 25.f, -1.f };
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Pannel", Pannel::Create(info));

	info.size = { 130.f, 60.f };
	info.position = { 75.f, -65.f, -1.f };
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Pannel", Pannel::Create(info));

	info.size = { 130.f, 60.f };
	info.position = { 75.f, 8.f, -1.f };
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Pannel", Pannel::Create(info));

	info.size = { 130.f, 60.f };
	info.position = { 75.f, 81.f, -1.f };
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Pannel", Pannel::Create(info));

	Engine::TextRenderer* pTextRenderer = AddComponent<Engine::TextRenderer>(L"", 0x000000);
	pTextRenderer->SetText(L"ÀçÀåÀü");
	pTextRenderer->SetDrawRect(100.f, 50.f);
	pTextRenderer->SetOffset(Vector3(-110.f, 10.f, 0.f));

	pTextRenderer = AddComponent<Engine::TextRenderer>(L"", 0x000000);
	pTextRenderer->SetText(L"µ¦");
	pTextRenderer->SetDrawRect(100.f, 50.f);
	pTextRenderer->SetOffset(Vector3(92.5f, -85.f, 0.f));

	pTextRenderer = AddComponent<Engine::TextRenderer>(L"", 0x000000);
	pTextRenderer->SetText(L"¹¦Áö");
	pTextRenderer->SetDrawRect(100.f, 50.f);
	pTextRenderer->SetOffset(Vector3(80.f, -10.f, 0.f));

	pTextRenderer = AddComponent<Engine::TextRenderer>(L"", 0x000000);
	pTextRenderer->SetText(L"Á¦¿Ü");
	pTextRenderer->SetDrawRect(100.f, 50.f);
	pTextRenderer->SetOffset(Vector3(80.f, 65.f, 0.f));

	_pDeck = AddComponent<Engine::TextRenderer>(L"Deck", 0x000000);
	_pDeck->SetDrawRect(100.f, 50.f);
	_pDeck->SetOffset(Vector3(25.f, -85.f, 0.f));
	_pDeck->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	_pGrave = AddComponent<Engine::TextRenderer>(L"Grave", 0x000000);
	_pGrave->SetDrawRect(100.f, 50.f);
	_pGrave->SetOffset(Vector3(25.f, -10.f, 0.f));
	_pGrave->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	_pExtra = AddComponent<Engine::TextRenderer>(L"Extra", 0x000000);
	_pExtra->SetDrawRect(100.f, 50.f);
	_pExtra->SetOffset(Vector3(25.f, 65.f, 0.f));
	_pExtra->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);	
}

void DeckSystem::Start()
{
	_pCardSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<CardSystem>();

	Button* pButton = AddComponent<Button>();
	pButton->SetRange(transform.position + Vector3(-75.f, 25.f, 0.f), {150.f, 150.f});
	pButton->SetOnPressed([this]() { _pCardSystem->ReloadCard(); });
}

void DeckSystem::Update(const float& deltaTime)
{
}

void DeckSystem::LateUpdate(const float& deltaTime)
{
	wchar_t buffer[4];
	wsprintf(buffer, L"%d", (int)_pCardSystem->GetCurrentDeckSize());
	_deckCount[Current] = buffer;
	_pDeck->SetText(_deckCount[Current].c_str());

	wsprintf(buffer, L"%d", (int)_pCardSystem->GetGraveDeckSize());
	_deckCount[Grave] = buffer;
	_pGrave->SetText(_deckCount[Grave].c_str());

	wsprintf(buffer, L"%d", (int)_pCardSystem->GetExtraDeckSize());
	_deckCount[Extra] = buffer;
	_pExtra->SetText(_deckCount[Extra].c_str());
}
