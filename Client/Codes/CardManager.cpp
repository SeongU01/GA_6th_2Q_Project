#include "CardManager.h"

// Component
#include "TextRenderer.h"
#include "Card.h"

#include "Client_Define.h"

bool CardManager::LoadCard(const wchar_t* filePath)
{
    std::wstring path = filePath;

    if (!LoadCardDataRichText((path + L"/OptionRichText.csv").c_str()))
        return false;

    if (!LoadCardDataOptionText((path + L"/OptionText.csv").c_str()))
        return false;

    if (!LoadCardData((path + L"/Card.csv").c_str()))
        return false;

    return true;
}

void CardManager::SetRichText(int ID, Engine::TextRenderer* pTextRenderer)
{
    if ((size_t)ID >= _richTexts.size())
        return;

    for (auto& richText : _richTexts[ID])
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

Card* CardManager::CloneCard(int ID)
{
    const Card::CardData& cardData = _cardDatas[ID];

    Engine::GameObject* pCard = Engine::GameObject::Create(); 
    pCard->SetName(L"Card");
    pCard->SetRenderGroup((int)RenderGroup::Card);
    pCard->AddComponent<Card>(cardData);

    Engine::TextRenderer* pTextRenderer = pCard->AddComponent<Engine::TextRenderer>(L"OptionText", D2D1::ColorF::White, 40.f);
    pTextRenderer->SetOffset(Vector3(-225.f, 70.f, 0.f));
    pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

    pTextRenderer->SetTextLayout(_texts[cardData.textID].c_str(), 450.f, 300.f);
    SetRichText(cardData.textID, pTextRenderer);

    return pCard->GetComponent<Card>();
}

bool CardManager::LoadCardDataOptionText(const wchar_t* filePath)
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

        std::getline(wss, token, L','); // ID
        std::getline(wss, token, L',');
        
        std::wstring findString = L"\\n";
        size_t pos = 0;        
        while ((pos = token.find(findString, pos)) != std::wstring::npos)
        {
            token.replace(pos, findString.length(), L"\n");
            pos += 1;
        }

        _texts.emplace_back(token);
    }

    return true;
}

bool CardManager::LoadCardDataRichText(const wchar_t* filePath)
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
        int ID = _wtoi(token.c_str());

        if (ID != (int)_richTexts.size() - 1)
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

        _richTexts[ID].push_back(std::make_tuple(start, length, type, value));
    }

    return true;
}

bool CardManager::LoadCardData(const wchar_t* filePath)
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

        Card::CardData cardData;

        std::getline(wss, token, L','); // ID
        token.replace(0, 5, L"");
        cardData.ID = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        cardData.costMana = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        cardData.costTime = (float)_wtof(token.c_str());

        std::getline(wss, token, L',');
        cardData.delayBefore = (float)_wtof(token.c_str());

        std::getline(wss, token, L',');
        cardData.delayAfter = (float)_wtof(token.c_str());

        std::getline(wss, token, L',');
        cardData.type = static_cast<CardType>(_wtoi(token.c_str()));

        std::getline(wss, token, L',');
        cardData.effectRelation = _wtoi(token.c_str());

        for (int i = 0; i < 2; i++)
        {
            std::getline(wss, token, L',');
            if (!token.empty()) token.replace(1, token.length(), L"");
            cardData.effectType[i] = static_cast<CardEffectType>(_wtoi(token.c_str()));

            std::getline(wss, token, L',');
            cardData.targetNum[i] = _wtoi(token.c_str());

            std::getline(wss, token, L',');
            token = token.substr(0, 1);
            cardData.additiveCharState[i] = _wtoi(token.c_str());

            std::getline(wss, token, L',');
            cardData.charStateNum[i] = _wtoi(token.c_str());

            std::getline(wss, token, L',');
            token = token.substr(0, 1);
            cardData.additiveCardState[i] = static_cast<CardAdditiveState>(_wtoi(token.c_str()));
        }

        std::getline(wss, token, L',');
        cardData.name = token;

        std::getline(wss, token, L',');
        cardData.textID = _wtoi(token.c_str());

        std::getline(wss, token, L',');
        cardData.iconID = _wtoi(token.c_str());

        for (int i = 0; i < 4; i++)
        {
            std::getline(wss, token, L',');
            cardData.variable[i] = _wtoi(token.c_str());
        }

        _cardDatas.push_back(cardData);        
    }

    return true;
}

void CardManager::Free()
{
}
