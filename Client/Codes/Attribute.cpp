#include "Attribute.h"

// Component
#include "BitFlag.h"
#include "Timer.h"
#include "PlayerMP.h"

#include "Client_Define.h"

Attribute::Attribute()
	: MonoBehavior(L"Attribute")
{
}

void Attribute::Awake()
{	
    std::wstring path = rootPath;
    std::wifstream file(path + L"Data/Card/AddtiveStateTable.csv");
    file.imbue(std::locale("en_US.UTF-8"));

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return;
    }

    std::wstring line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::wstringstream wss(line);
        std::wstring token;

        std::getline(wss, token, L','); // Comment
		std::getline(wss, token, L','); // ID
		int ID = _wtoi(token.c_str());

		while (std::getline(wss, token, L','))
			_stateDatas[ID - 1].push_back((float)_wtof(token.c_str()));
    }

	_pBitFlag = AddComponent<Engine::BitFlag>(L"BitFlag");
	_pTimer = AddComponent<Engine::Timer>(L"Timer", State::End);
}

void Attribute::Start()
{	
}

void Attribute::Update(const float& deltaTime)
{
}

void Attribute::LateUpdate(const float& deltaTime)
{
	for (int i = 0; i < State::End; i++)
	{
		unsigned long long flag = (unsigned long long)1 << (i + 1);

		if (0 >= _stateStacks[i])
			_pBitFlag->OffFlag(flag);

		if (State::Shield == i)
			continue;

		if (_pBitFlag->CheckFlag(flag))
		{
			_pTimer->SetActive(i, true);

			if (_pTimer->IsOverTime(i, _stateDatas[i][0]))
			{
				_pBitFlag->OffFlag(flag);
				_pTimer->SetElapsed(i, 0.f);
				_stateStacks[i]--;
			}
		}
		else
			_pTimer->SetActive(i, false);
	}
}

int Attribute::GetExtraRecoveryValue() const
{
	return (int)_stateDatas[State::Extra][1];
}

bool Attribute::IsActiveState(unsigned long long flag) const
{
	return _pBitFlag->CheckFlag(flag);
}

void Attribute::UseStack(State state)
{
	_stateStacks[state]--;
	if (0 > _stateStacks[state])
		_stateStacks[state] = 0;
}

void Attribute::AddState(unsigned long long flag, int stack)
{
	if (1 >= flag || AttributeFlag::OverCharge == flag) return;

	unsigned long long n = flag;
	int count = 0;

	while (1 < n)
	{
		n >>= 1;
		count++;
	}

	switch (flag)
	{
	case AttributeFlag::Charge:
		Sound::PlaySound("Battle_Sound_State_Get_Charge", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	case AttributeFlag::Extra://잔류
		Sound::PlaySound("Battle_Sound_State_Get_Residual", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	case AttributeFlag::HighPower://고출력
		Sound::PlaySound("Battle_Sound_State_Get_OverPower", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	case AttributeFlag::OverCharge://방전(없음
		Sound::PlaySound("Battle_Sound_State_Get_Discharge", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	case AttributeFlag::Shield:
		Sound::PlaySound("Battle_Sound_State_Get_Shield", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	case AttributeFlag::WeakPoint:
		Sound::PlaySound("Battle_Sound_State_Get_WeakPoint", (int)SoundGroup::Attribute, 0.8f, false);
		break;
	default:
		break;
	}

	_pBitFlag->OnFlag(flag);
	_stateStacks[count - 1] += stack;
}

void Attribute::Reset()
{
	_pBitFlag->SetFlag(0);
	for (int i = 0; i < State::End; i++)
	{		
		_pTimer->SetActive(i, false);
		_stateStacks[i] = 0;
	}
}

void Attribute::ActiveCharge()
{	
	if (_pBitFlag->CheckFlag(AttributeFlag::Charge))
	{
		Sound::PlaySound("Battle_Sound_State_Execute_Charge", (int)SoundGroup::AttributeActive, 0.8f, false);
		_pBitFlag->OnFlag(AttributeFlag::HighPower);
		_stateStacks[State::HighPower] += 1;
		_stateStacks[State::Charge]--;
		GetComponent<PlayerMP>()->mp++;
	}
}

int Attribute::ActiveHighPower()
{	
	if (_pBitFlag->CheckFlag(AttributeFlag::HighPower))
	{
		Sound::PlaySound("Battle_Sound_State_Execute_OverPower", (int)SoundGroup::AttributeActive, 0.8f, false);
		_stateStacks[State::HighPower]--;
		return (int)_stateDatas[Attribute::HighPower][1];
	}

	return 0;
}

int Attribute::ActiveWeakPoint()
{	
	if (_pBitFlag->CheckFlag(AttributeFlag::WeakPoint))
	{
		Sound::PlaySound("Battle_Sound_State_Execute_WeakPoint", (int)SoundGroup::AttributeActive, 0.8f, false);
		_stateStacks[State::WeakPoint]--;
		return (int)_stateDatas[State::WeakPoint][1];
	}

	return 0;
}
