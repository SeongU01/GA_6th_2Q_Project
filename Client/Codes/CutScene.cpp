#include "CutScene.h"
//component
#include "Fade.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "EventManager.h"
//scene
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage4Scene.h"
#include "TitleScene.h"

#include "Client_Define.h"

//���̵� ��, ���̵� �ƿ� Ÿ�̹� �ֱ� + �ƾ� ����� �������� �Ѱ��ֱ�.
void changeStage(int stage,Player* player)
{
    if (player != nullptr)player->SetPlayerActives(true);
    EventManager::GetInstance()->SetStopGame(false);
    if (stage == 1) 
    {
        Scene::ChagneScene(Stage1Scene::Create());
    }
    else if (stage == 2)
    {
        Scene::ChagneScene(Stage2Scene::Create());
    }
    else if (stage == 4)
    {
        Scene::ChagneScene(Stage4Scene::Create());
    }
    else if (stage == 5)
    {
        if (player != nullptr)player->SetPlayerActives(false);
        Scene::ChagneScene(TitleScene::Create());
    }
}

CutScene::CutScene(int stage):_stageNum(stage)   
{
}

//���ڿ� ��ȯ�Լ�
std::string wstring_to_string(const std::wstring& wstr) {
    std::locale loc("");
    const wchar_t* from = wstr.c_str();
    const std::size_t len = wstr.size();
    std::vector<char> buffer(len * 4);
    std::use_facet<std::ctype<wchar_t>>(loc).narrow(from, from + len, '?', buffer.data());
    return std::string(buffer.data(), buffer.size());
}

int CutScene::Update(const float& deltaTime)
{
    _cutTime += deltaTime;
    if (Input::IsKeyDown(DIK_EQUALS)) //��ŵ���
    {
        changeStage(_stageNum,_pPlayer);
        return 0;
    }

    if (_cutTime >= _info._duration) //���ü����
    {
        _cutTime = 0.0f;
        setScene();
    }
    if (_cutTime<-8.0f && _cutTime>-9.0f)
    {
        changeStage(_stageNum, _pPlayer);
    }

    //��������
    for (int i = 0; i < (int)SoundGroup::End; i++)
    {
        if (i == (int)SoundGroup::Voice || i == (int)SoundGroup::SFX)
            continue;
        Sound::PauseSound(i, true);
    }
    return 0;
}

int CutScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool CutScene::Initialize()
{
    //�÷��̾� ����
    if (Engine::FindObject((int)LayerGroup::Player, L"Player", NULL) != nullptr) 
    {
        _pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>();
        _pPlayer->SetPlayerActives(false);
    }
    //�̹�������
    _pBObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = _pBObj->GetComponent<Engine::SpriteRenderer>();
    std::wstring name = L"CutScene_Part" + std::to_wstring(_stageNum);
    pSpriteRenderer->BindTexture(Resource::FindTexture(name.c_str()));
    pSpriteRenderer->SetIndex(0);
    _pBObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"CutScene", _pBObj); _pBObj->SetRenderGroup((int)RenderGroup::BackGround);
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, 1); //�ƽ� ���� �ҷ�����
    if (_info._voiceTag != L"")
    {
        Sound::StopSound((int)SoundGroup::Voice);
        Sound::PlaySound(wstring_to_string(_info._voiceTag).c_str(), (int)SoundGroup::Voice, 1.0f, false);
    }
    if (_info._dummySoundTag != L"")
    {
        Sound::PlaySound(wstring_to_string(_info._dummySoundTag).c_str(), (int)SoundGroup::SFX, 1.0f, false);
    }

    //�������
    std::string soundName = "Bgm_Sound_BGM_Cut_Scene_" + std::to_string(_stageNum);
    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound(soundName.c_str(), (int)SoundGroup::BGM, 0.5f, false);
    //���̵����(�� �� �� ��, ���� �� �� ��..)
    Fade::FadeInfo info;
    info.option = Fade::Fade_Option::Fade_In;
    info.color = 0xFF000000;
    info.duration = 1.0f;
    info.life = 3.0f;
    _pFadeObj = Engine::GameObject::Create();
    Fade* _pFade = _pFadeObj->AddComponent<Fade>(info);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", _pFadeObj); _pFadeObj->SetRenderGroup((int)RenderGroup::Fade);
    EventManager::GetInstance()->SetStopGame(true);
    return true;
}

void CutScene::setScene()
{
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, _info._order + 1); //���� ������� ����
    if (_info._part != 0) {
        Engine::SpriteRenderer* pSpriteRenderer = _pBObj->GetComponent<Engine::SpriteRenderer>();
        pSpriteRenderer->SetIndex(_info._order-1);
        if (_info._voiceTag != L"")
        {
            Sound::StopSound((int)SoundGroup::Voice);
            Sound::PlaySound(wstring_to_string(_info._voiceTag).c_str(), (int)SoundGroup::Voice, 1.0f, false);
        }
        if (_info._dummySoundTag != L"")
        {
            Sound::PlaySound(wstring_to_string(_info._dummySoundTag).c_str(), (int)SoundGroup::SFX, 1.0f, false);
        }
    }
    else 
    {
        _cutTime = -10.0f;
        Fade::FadeInfo info;
        info.option = Fade::Fade_Option::Fade_Out;
        info.color = 0xFF000000;
        info.duration = 1.0f;
        info.life = 3.0f;
        _pFadeObj = Engine::GameObject::Create();
        Fade* _pFade = _pFadeObj->AddComponent<Fade>(info);
        Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", _pFadeObj); _pFadeObj->SetRenderGroup((int)RenderGroup::Fade);
        _info._duration = 3.0;
    }
}

void CutScene::Free()
{

}

CutScene* CutScene::Create(int stage)
{
    return new CutScene(stage);
}