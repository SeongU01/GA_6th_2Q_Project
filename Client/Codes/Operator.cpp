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
	_texts.push_back(L"����, ���� �ð��� 1���̾�!\n���� �ð��� ���� �Ʒ��� �߾� ����� Ÿ�̸ӷ� Ȯ���� �� �־�.");
	_texts.push_back(L"ī�带 ����ؼ� ���� �����ϰų� �̵��� �� �־�.\nī�带 Ŭ���� ��, ���ϴ� ������ ī�带 ���� ������ ��.");
	_texts.push_back(L"ī��� �ڽ�Ʈ�� �ð��� �������� �Ҹ���.\n�ڽ�Ʈ�� ������ ī�尡 ������ ������ ������!");
	_texts.push_back(L"�ٷ� �װž�! ����� ī��� ��⿭�� ��ϵ�.\n��� ������ �����Ǹ�, ��⿭�� ��ϵ� ������� ī�尡 ����.");
	_texts.push_back(L"��� ���� ���¿����� �ð��� �帣�� �ʾ�.\nSPACE�� ������ ��� ������ Ȱ��ȭ�ų�, ������ �� �־�.");
	_texts.push_back(L"������ �ٰ����� �־�. SPACE�� ���� ������ ��������.");
	_texts.push_back(L"ī�尡 �����ϸ�, ���ε� ��ư�� ���� �и� ���� ���� �� �־�.");
	_texts.push_back(L"������ ȸ���� ���ε��, �� �ʸ��� �ڵ����� ������.");
	_texts.push_back(L"�ʸ��� �������� �η��� ���̾�. ��Ź�Ұ�, ����.");

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
	_pTitle->SetText(L"���۷�����");
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
