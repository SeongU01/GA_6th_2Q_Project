#include "CutScene.h"

//component
#include "Fade.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "EventManager.h"
#include "TimerSystem.h"

//scene
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage4Scene.h"
#include "TitleScene.h"

#include "Client_Define.h"

//페이드 인, 페이드 아웃 타이밍 넣기 + 컷씬 종료시 스테이지 넘겨주기.
void changeStage(int stage,Player* player)
{
    for (int i = 0; i < (int)SoundGroup::End; i++)
        Sound::PauseSound(i, false);
    if (player != nullptr) 
    {
        player->SetPlayerActives(true);
        player->GetComponent<TimerSystem>()->TutorialTimeStop(false);
    }
    EventManager::GetInstance()->SetStopGame(false);
    if (stage == 1)
    {
        Engine::ChangeScene(Stage1Scene::Create());
    }
    else if (stage == 2)
    {
        Engine::ChangeScene(Stage2Scene::Create());
    }
    else if (stage == 4)
    {
        Engine::ChangeScene(Stage4Scene::Create());
    }
    else if (stage == 5)
    {
        if (player != nullptr)
        {
            player->SetPlayerActives(false);
            player->gameObject.SetDead();
        }

        if (player != nullptr)player->SetPlayerActives(false);
        for (int i = 0; i < (int)SoundGroup::End; i++)
        {
            Sound::StopSound(i);
        }

        Engine::RemoveAll();
        Engine::ChangeScene(TitleScene::Create());
    }

    ShowCursor(true);
}

CutScene::CutScene(int stage):_stageNum(stage)   
{
}

//문자열 변환함수
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
    //사운드제어
    for (int i = 0; i < (int)SoundGroup::End; i++)
    {
        if (i == (int)SoundGroup::Voice || i == (int)SoundGroup::SFX || i == (int)SoundGroup::BGM)
            continue;
        Sound::PauseSound(i, true);
    }
    float _deltaTime = Time::GetGlobalDeltaTime();
    _cutTime += _deltaTime;
    if (Input::IsKeyDown(DIK_EQUALS)) //스킵기능
    {
        changeStage(_stageNum, _pPlayer);
        return 0;
    }

    if (_cutTime >= _info._duration) //장면체인지
    {
        _cutTime = 0.0f;
        setScene();
    }
    if (_cutTime<-8.0f && _cutTime>-9.0f)
    {
        changeStage(_stageNum, _pPlayer);
    }

    POINT mousePoint = { WINCX >> 1, WINCY >> 1 };
    ScreenToClient(Engine::GetWindow(), &mousePoint);
    SetCursorPos(mousePoint.x, mousePoint.y);

    return 0;
}

int CutScene::LateUpdate(const float& deltaTime)
{    
    return 0;
}

bool CutScene::Initialize()
{
    ShowCursor(false);

    //플레이어 끄기
    if (Engine::FindObject((int)LayerGroup::Player, L"Player", NULL) != nullptr) 
    {
        _pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>();
        _pPlayer->SetPlayerActives(false);
        _pPlayer->GetComponent<TimerSystem>()->TutorialTimeStop(true);
    }
    //이미지셋팅
    _pBObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = _pBObj->GetComponent<Engine::SpriteRenderer>();
    std::wstring name = L"CutScene_Part" + std::to_wstring(_stageNum);
    pSpriteRenderer->BindTexture(Resource::FindTexture(name.c_str()));
    pSpriteRenderer->SetIndex(0);
    _pBObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"CutScene", _pBObj); _pBObj->SetRenderGroup((int)RenderGroup::BackGround);
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, 1); //컷신 정보 불러오기
    if (_info._voiceTag != L"")
    {
        Sound::StopSound((int)SoundGroup::Voice);
        Sound::PlaySound(wstring_to_string(_info._voiceTag).c_str(), (int)SoundGroup::Voice, 1.0f, false);
    }
    if (_info._dummySoundTag != L"")
    {
        Sound::PlaySound(wstring_to_string(_info._dummySoundTag).c_str(), (int)SoundGroup::SFX, 1.0f, false);
    }

    //페이드셋팅(들어갈 때 한 번, 나갈 때 한 번..)
    Fade::FadeInfo info;
    info.option = Fade::Fade_Option::Fade_In;
    info.color = 0xFF000000;
    info.duration = 1.0f;
    info.life = 3.0f;
    _pFadeObj = Engine::GameObject::Create();
    Fade* _pFade = _pFadeObj->AddComponent<Fade>(info);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", _pFadeObj); _pFadeObj->SetRenderGroup((int)RenderGroup::Fade);
    
    EventManager::GetInstance()->SetStopGame(true);

    //사운드셋팅
    std::string soundName = "Bgm_Sound_BGM_Cut_Scene_" + std::to_string(_stageNum);
    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound(soundName.c_str(), (int)SoundGroup::BGM, 0.5f, true);

    return true;
}

void CutScene::setScene()
{
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, _info._order + 1); //다음 장면으로 변경
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