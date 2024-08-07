#include "TitleScene.h"

//Ÿ��Ʋ ui (�˾� ��ũ�� ui ����)
#include "TitleHUD.h"
#include "InfoHUD.h"
#include "CreditHUD.h"
//�̵����� ��
#include "SelectScene.h"

#include "MapManager.h"
#include "Client_Define.h"


int TitleScene::Update(const float& deltaTime)
{
    return 0;
}

int TitleScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool TitleScene::Initialize()
{
    std::wstring path = rootPath;
    MapManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage1");

    return true;
}

void TitleScene::Free()
{
}

TitleScene* TitleScene::Create()
{
    return new TitleScene;
}