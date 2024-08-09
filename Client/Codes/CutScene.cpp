#include "CutScene.h"

#include "TitleScene.h"

#include "Client_Define.h"
#include "DataManager.h"


int CutScene::Update(const float& deltaTime)
{
    return 0;
}

int CutScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool CutScene::Initialize()
{
    return true;
}

void CutScene::Free()
{
}

CutScene* CutScene::Create()
{
    return new CutScene;
}