#include "DeckUI.h"

// Component
#include "DeckSystem.h"

bool DeckUI::Initialize()
{
    AddComponent<DeckSystem>();

    return true;
}

DeckUI* DeckUI::Create()
{
    DeckUI* pInstance = new DeckUI;

    if (pInstance->Initialize())
        return pInstance;

    return pInstance;
}
