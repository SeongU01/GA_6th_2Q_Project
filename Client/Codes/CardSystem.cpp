#include "CardSystem.h"

// Component
#include "TextRenderer.h"

#include "Client_Define.h"

bool CardSystem::LoadCard(const wchar_t* filePath)
{
    std::wstring path = filePath;

    if (!LoadCardDataRichText((path + L"/OptionRichText.csv").c_str()))
        return false;

    if (!LoadCardDataOptionID((path + L"/OptionID.csv").c_str()))
        return false;

    if (!LoadCardDataOptionText((path + L"/OptionText.csv").c_str()))
        return false;

    if (!LoadCardData((path + L"/Card.csv").c_str()))
        return false;

    return true;
}

void CardSystem::SetRichText(int ID, Engine::TextRenderer* pTextRenderer)
{
    for (auto& richText : _richTexts[ID - 1])
    {
        auto [start, length, type, value] = richText;
        if (L"Color" == type)
        {
            pTextRenderer->SetTextRangeEffectColor(start, length, value);
        }
        else if (L"Bold" == type)
        {
            pTextRenderer->SetTextRangeEffectBold(start, length);
        }
        else if (L"Underline" == type)
        {
            pTextRenderer->SetTextRangeEffectUnderline(start, length);
        }        
    }
}

bool CardSystem::LoadCardDataOptionID(const wchar_t* filePath)
{
    std::wifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::wstring line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::wstringstream wss(line);
        std::wstring token;

        std::getline(wss, token, L','); // ID

        std::getline(wss, token, L',');
        int type = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        int value = _wtoi(token.c_str());

        _optionValues.emplace_back(std::make_pair(type, value));
    }

    return true;
}

bool CardSystem::LoadCardDataOptionText(const wchar_t* filePath)
{    
    std::wifstream file(filePath);
    file.imbue(std::locale("en_US.UTF-8"));

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::wstring line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::wstringstream wss(line);
        std::wstring token;
        std::wstring effect;

        std::getline(wss, token, L','); // ID        

        while (std::getline(wss, token, L','))
        {   
            if (L"ID" == token.substr(0, 2))
            {        
                int ID = _wtoi(token.substr(2).c_str());
                wchar_t buffer[4];
                wsprintf(buffer, L"%d", _optionValues[ID - 1].second);
                effect += buffer;
            }
            else
            {
                std::wstring findString = L"\\n";
                size_t pos = 0;
                while ((pos = token.find(findString, pos)) != std::wstring::npos)
                {
                    token.replace(pos, findString.length(), L"\n");
                    pos += 1; // Move past the last replaced position
                }
                effect += token;
            }
        }
        
        _texts.emplace_back(effect);
    }

    return true;
}

bool CardSystem::LoadCardDataRichText(const wchar_t* filePath)
{
    std::wifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::wstring line;
    std::getline(file, line);

    while (std::getline(file, line))
    {        
        std::wstringstream wss(line);
        std::wstring token;

        std::getline(wss, token, L',');
        int id = _wtoi(token.c_str());

        if (id != (int)_richTexts.size())
            _richTexts.push_back(std::list<RichText>());

        std::getline(wss, token, L',');
        int start = _wtoi(token.c_str());
        
        std::getline(wss, token, L',');        
        int length = _wtoi(token.c_str());
        
        std::getline(wss, token, L',');
        std::wstring type = token;

        std::getline(wss, token, L',');
        int value;

        std::wstringstream hexStream;
        hexStream << std::hex << token;
        hexStream >> value;

        _richTexts[id - 1].push_back(std::make_tuple(start, length, type, value));
    }

    return true;
}

bool CardSystem::LoadCardData(const wchar_t* filePath)
{
    std::wifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    std::wstring line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::wstringstream wss(line);
        std::wstring token;

        std::getline(wss, token, L',');
        int id = _wtoi(token.c_str());

        if (id != (int)_richTexts.size())
            _richTexts.push_back(std::list<RichText>());

        std::getline(wss, token, L',');
        int start = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        int length = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        std::wstring type = token;

        std::getline(wss, token, L',');
        int value;

        std::wstringstream hexStream;
        hexStream << std::hex << token;
        hexStream >> value;

        _richTexts[id - 1].push_back(std::make_tuple(start, length, type, value));
    }

    return true;
}

void CardSystem::Free()
{
}
