#include "Card.h"

// Component

void Card::Initialize()
{
}

Card* Card::Create()
{
    Card* pInstance = new Card;
    pInstance->Initialize();

    return pInstance;
}
