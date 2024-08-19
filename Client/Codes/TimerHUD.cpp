#include "TimerHUD.h"

#include "TimerSystem.h"
#include "TextRenderer.h"
#include "ToolTip.h"
#include "Button.h"

#include "Client_Define.h"

TimerHUD::TimerHUD()
	:UIComponent(L"TimerHUD")
{
	_pTimer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<TimerSystem>(); //타이머시스템
}

void TimerHUD::Awake()
{
}

void TimerHUD::Start()
{
	UI* backpUI;
	//비네팅
	_pRedBene = AddUI(CreateInfo(L"UI_Bene", L"UI_HUD_Bene", 1, Vector3(float(WINCX >> 1), float(WINCY >> 1), -100.f), { 1.0f, 1.0f, 1.0f }, &transform));
	_pRedBene->SetActive(false);
	_pBene = AddUI(CreateInfo(L"UI_Bene", L"UI_HUD_Bene", 0, Vector3(float(WINCX >> 1), float(WINCY >> 1), -100.f), { 1.0f, 1.0f, 1.0f }, &transform));
	_pBene->SetActive(false);
	//카드 라인
	AddUI(CreateInfo(L"UI_Back", L"UI_HUD_Card", 0, { 960.0f , 980.f, -100.f }, { 1.0f, 1.0f, 1.0f }, &transform));
	backpUI = AddUI(CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Back", 0, { 210.0f , 980.f, -1.f }, { 1.0f, 1.0f, 1.0f }, &transform));
	AddUI(CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Box", 0, { 210.0f , 1030.f, -1.f }, { 1.0f, 1.3f, 1.0f }, &transform));
	_pRed = AddUI(CreateInfo(L"Timer_Red", L"UI_HUD_Timer_Gage", 0, { 210.0f , 1030.f, 0.f }, { 1.0f, 1.0f, 0.f }, &transform));
	_pYellow = AddUI(CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 210.0f , 1030.f, 0.f }, { 1.0, 1.0f, 0.f }, &transform));
	AddUI(CreateInfo(L"Timer_Back2", L"UI_HUD_Timer_Box", 1, { 210.0f , 1030.f, 0.f }, { 1.f, 1.f, 0.f }, &transform));
	//텍스트
	Engine::GameObject* pTextobj = Engine::GameObject::Create();
	pTextobj->SetNotAffectCamera(true);
	_pText = pTextobj->AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::White, 70.0f);
	_pText->SetDrawRect(200.f, 100.f);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pTextobj); pTextobj->SetRenderGroup((int)RenderGroup::UI);
	//하단 툴팁
	ToolTip* _ptoolTip = pTextobj->AddComponent<ToolTip>(L"TimerTool1");
	_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"UI_Cost_TimeLimit"), Vector3(300.0f, -100.0f, 0.0f));
	Engine::GameObject& oOwner = *pTextobj;
	Button* btn = pTextobj->AddComponent<Button>();
	btn->SetRange({ 210.0f , 1030.f, 0.f }, backpUI->GetSize());
	btn->SetOnHover([&oOwner] {
		ToolTip* pToolTip = oOwner.GetComponent<ToolTip>(L"TimerTool1");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&oOwner] {
		ToolTip* pToolTip = oOwner.GetComponent<ToolTip>(L"TimerTool1");
		pToolTip->ActiveToolTip(false);
		});
	//상단 타이머
	AddUI(CreateInfo(L"Timer_top_back", L"UI_HUD_Timer_Top", 0, { 960.0f, 30.0f, 0.f }, { 1.0f, 1.0f, 1.0f }, &transform));
	_pTopDefault = AddUI(CreateInfo(L"Timer_top_red", L"UI_HUD_Timer_Top", 3, { 960.0f, 30.0f, 0.f }, { 1.0f, 1.0f, 1.0f }, &transform));
	_pTopSkill = AddUI(CreateInfo(L"Timer_top_Orange", L"UI_HUD_Timer_Top", 4, { 0.0f, 30.0f, 1.f }, { 1.0f, 1.0f,1.0f }, &transform));
	//상단 툴팁
	_ptoolTip = AddComponent<ToolTip>(L"TimerTool2");
	_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"UI_Cost_TimeLimit"), Vector3(300.0f, 100.0f, 0.0f));
	Engine::GameObject& pOwner = transform.GetOwner();
	btn = AddComponent<Button>();
	btn->SetRange({ 960.0f, 30.0f, 0.f }, _pTopDefault->GetSize());
	btn->SetOnHover([&pOwner] {
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"TimerTool2");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&pOwner] {
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"TimerTool2");
		pToolTip->ActiveToolTip(false);
		});
}

void TimerHUD::Update(const float& deltaTime)
{
	float timer = _pTimer->GetRemainingTime();
	float rate = timer / _pTimer->GetMaxTime();
	_pRed->SetOffsetPosition(Vector3(_pRed->GetImageSize().width * -0.5f * (1.f - rate) + (1 - rate) * 12.0f, 0.f, 0.f));
	_pRed->SetScale({ rate, 1.0f, 0.f });

	float _skillValue = _pTimer->GetSkillTime();
	rate = _skillValue / 60;
	_pYellow->SetScale({ rate  ,1.0f,1.0f });
	_pYellow->SetPosition({
		_pRed->transform.position.x + (_pRed->GetSize().width) * 0.5f - 10.0f + (1 - (timer / _pTimer->GetMaxTime())) * 10 //맨끝으로 보정
		- (2.4f * _skillValue),//주황바 보정
		1030.f,
		0.0f
		});
	//상단 타이머ui
	rate = timer / _pTimer->GetMaxTime();
	_pTopDefault->SetOffsetPosition(Vector3(_pTopDefault->GetImageSize().width * -0.5f * (1.f - rate), 0.f, 0.f));
	_pTopDefault->SetScale({ rate, 1.0f, 0.f });
	//사용된 시간(주황탑
	rate = _skillValue / 60;
	_pTopSkill->SetScale({ rate  ,1.0f,1.0f });
	_pTopSkill->SetOffsetPosition({ _pTopDefault->GetSize().width - (15.8f * _skillValue), 0.0f,0.0f });
	//글씨조정
	swprintf(_buffer, sizeof(_buffer) / sizeof(_buffer[0]), L"%02d:%02d", (int)timer, (int)(timer * 100) % 100);
	_pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	_pText->transform.SetPosition({ 120,920 });
	_pText->SetText(_buffer);

	if (timer <= 0)
	{
		_pRed->SetScale({ 0.f,0.f,0.f });
		_pYellow->SetScale({ 0.f,0.f,0.f });
	}
	
	if (_soundTrigger && (timer <= 28 && timer > 10))
		_soundTrigger = false;
	if (!_soundTrigger && timer <=10)
	{
		_soundTrigger = true;
		Sound::StopSound((int)SoundGroup::Voice);
		Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_10_1", (int)SoundGroup::Voice, 0.8f, false);
	}
	else if (!_soundTrigger && timer <= 30 && timer>=29)
	{
		_soundTrigger = true;
		Sound::StopSound((int)SoundGroup::Voice);
		Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_30_1", (int)SoundGroup::Voice, 0.8f, false);
	}

	_pBene->SetActive(_pTimer->GetisSlow());
	if (timer <= 15) //time limit
		_pRedBene->SetActive(true);
}

void TimerHUD::LateUpdate(const float& deltaTime)
{
}
