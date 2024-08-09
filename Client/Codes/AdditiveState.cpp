#include "AdditiveState.h"

// Component
#include "BitFlag.h"
#include "Timer.h"

#include "Client_Define.h"

void AdditiveState::Awake()
{
	_pBitFlag = AddComponent<Engine::BitFlag>(L"BitFlag");
	_pTimer = AddComponent<Engine::Timer>(L"Timer", State::End);

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
}

void AdditiveState::Start()
{
}

void AdditiveState::Update(const float& deltaTime)
{	
}

void AdditiveState::LateUpdate(const float& deltaTime)
{
	if (_pBitFlag->CheckFlag(AdditiveFlag::Charge))
	{
		_pTimer->SetActive(State::Charge, true);

		if (_pTimer->IsOverTime(State::Charge, _stateDatas[State::Charge][0]))
		{
			_pBitFlag->OffFlag(AdditiveFlag::Charge);
			_pTimer->SetActive(State::Charge, false);
		}
	}

	if (_pBitFlag->CheckFlag(AdditiveFlag::Extra))
	{
		_pTimer->SetActive(State::Extra, true);

		if (_pTimer->IsOverTime(State::Extra, _stateDatas[State::Extra][0]))
		{
			_pBitFlag->OffFlag(AdditiveFlag::Extra);
			_pTimer->SetActive(State::Extra, false);
		}
	}
}

void AdditiveState::AddState(unsigned long long flag)
{
	_pBitFlag->OnFlag(flag);
}

bool AdditiveState::IsActiveState(unsigned long long flag) const
{
	return _pBitFlag->CheckFlag(flag);
}
