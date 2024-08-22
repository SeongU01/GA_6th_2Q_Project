#include "Operator.h"
#include "Pannel.h"
#include "EventManager.h"

// Component
#include "TextRenderer.h"
#include "TimerSystem.h"
#include "EventInvoker.h"

#include "Client_Define.h"

Operator::Operator()
	: MonoBehavior(L"Operator")
{
}

void Operator::Awake()
{
	_texts.push_back(L"제로, 제한 시간은 1분이야!\n남은 시간은 왼쪽 아래와 중앙 상단의 타이머로 확인할 수 있어.");
	_texts.push_back(L"카드를 사용해서 적을 공격하거나 이동할 수 있어.\n카드를 클릭한 후, 원하는 범위로 카드를 끌어 넣으면 돼.");
	_texts.push_back(L"카드는 코스트로 시간과 에너지를 소모해.\n코스트가 없으면 카드가 사용되지 않으니 주의해!");
	_texts.push_back(L"바로 그거야! 사용한 카드는 대기열에 등록돼.\n사고 가속이 해제되면, 대기열에 등록된 순서대로 카드가 사용돼.");
	_texts.push_back(L"사고 가속 상태에서는 시간이 흐르지 않아.\nSPACE를 눌러서 사고 가속을 활성화거나, 해제할 수 있어.");
	_texts.push_back(L"적들이 다가오고 있어. SPACE를 눌러 전투를 개시하자.");
	_texts.push_back(L"카드가 부족하면, 리로드 버튼을 눌러 패를 새로 받을 수 있어.");
	_texts.push_back(L"에너지 회복과 리로드는, 몇 초마다 자동으로 충전돼.");
	_texts.push_back(L"너마저 쓰러지면 인류는 끝이야. 부탁할게, 제로.");

	Pannel::PannelInfo info;
	info.fillColor = 0x000000;
	info.outlineColor = 0xFFFFFF;
	info.opacity = 0.9f;
	info.lineWidth = 3.f;
	info.parent = &transform;
	info.size = Vector3(800.f, 180.f, 0.f);
	info.position = Vector3(960.f, 150.f, 0.f);
	
	_pPannel = Pannel::Create(info);
	_pPannel->SetDontDestroyObject(true);
	_pPannel->SetRenderGroup((int)RenderGroup::Top);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _pPannel);

	_pTitle = _pPannel->AddComponent<Engine::TextRenderer>(L"Title", (DWORD)0xFFFFDB32, 30.f, DWRITE_FONT_WEIGHT_BOLD);
	_pTitle->SetText(L"오퍼레이터");
	_pTitle->SetDrawRect(800.f, 100.f);
	_pTitle->SetOffset(Vector3(-375.f, -70.f, 0.f));

	_pText = _pPannel->AddComponent<Engine::TextRenderer>(L"Text");
	_pText->SetText(_texts[3]);
	_pText->SetDrawRect(800.f, 200.f);
	_pText->SetOffset(Vector3(-375.f, -10.f, 0.f));

	_pPannel->SetActive(false);
}

void Operator::Start()
{
}

void Operator::Update(const float& deltaTime)
{
	float delta = Time::GetGlobalDeltaTime();

	if (_isTutorial1)
	{
		Text(delta, 3);

		if (3 == _count)
		{
			_pPannel->SetActive(false);
			_isTutorial1 = false;
		}
	}

	if (_isTutorial2)
	{
		Text(delta, 6);

		if (6 == _count)
		{
			_pPannel->SetActive(false);
			_isTutorial2 = false;
			TimerSystem* pTimerSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<TimerSystem>();
			pTimerSystem->TutorialTimeStop(false);
			pTimerSystem->TimeStop();
			_isTutorial2End = true;
			Sound::StopSound((int)SoundGroup::Time);
		}
	}

	if (_isTutorial3)
	{
		Text(delta, 9);

		if (9 == _count)
		{
			_pPannel->SetActive(false);
			_isTutorial3 = false;

			TimerSystem* pTimerSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<TimerSystem>();
			pTimerSystem->TutorialTimeStop(false);
			pTimerSystem->TimeStop();
			Sound::StopSound((int)SoundGroup::Time);
		}
	}
}

void Operator::LateUpdate(const float& deltaTime)
{
}

void Operator::Tutorial1()
{
	if (!_isTutorial)
	{
		Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_001", (int)SoundGroup::Voice);
		_pPannel->SetActive(true);
		_length = 0.f;
		_count = 0;
		_isTutorial1 = true;
		Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<TimerSystem>()->TutorialTimeStop(true);
		_isTutorial = true;
	}
}

bool Operator::Tutorial2()
{
	if (!_isTutorial2 && !_isTutorial1)
	{
		Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_100", (int)SoundGroup::Voice);
		_pPannel->SetActive(true);
		_length = 0.f;
		_count = 3;
		_isTutorial2 = true;
		Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<TimerSystem>()->TutorialTimeStop(true);

		return true;
	}
	else
		return false;
}

bool Operator::Tutorial3()
{
	if (!_isTutorial3 && _isTutorial && _isTutorial2End && !EventManager::GetInstance()->IsTimeStop())
	{			
		Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_200", (int)SoundGroup::Voice);
		_pPannel->SetActive(true);
		_length = 0.f;
		_count = 6;
		_isTutorial3 = true;
		Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<TimerSystem>()->TutorialTimeStop(true);

		return true;
	}

	return false;
}

void Operator::Text(const float& deltaTime, int count)
{
	if (count > _count)
	{
		_length += deltaTime / 0.05f;
		std::wstring text = _texts[_count];

		if (Input::IsKeyDown(Input::DIM_LB))
		{
			if ((size_t)_length >= text.length())
			{
				_length = 0.f;
				_count++;

				Sound::StopSound((int)SoundGroup::Voice);

				switch (_count)
				{
				case 1:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_002", (int)SoundGroup::Voice);
					break;
				case 2:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_003", (int)SoundGroup::Voice);
					break;
				case 4:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_101", (int)SoundGroup::Voice);
					break;
				case 5:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_102", (int)SoundGroup::Voice);
					break;
				case 7:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_201", (int)SoundGroup::Voice);
					break;
				case 8:
					Sound::PlaySound("Voice_Sound_Voice_Operator_Tuorial_202", (int)SoundGroup::Voice);
					break;
				}
			}
			else
				_length = (float)text.length();
		}

		text = text.substr(0, size_t(_length));
		_pText->SetText(text.c_str());
	}
}
