#include "CutScene.h"
//component
#include "Fade.h"
#include "SpriteRenderer.h"
//scene
#include "Stage1Scene.h"

#include "Client_Define.h"

//페이드 인, 페이드 아웃 타이밍 넣기 + 컷씬 종료시 스테이지 넘겨주기.
void changeStage()
{
    Scene::ChagneScene(Stage1Scene::Create());
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
    CutTime += deltaTime;
    if (Input::IsKeyDown(DIK_1)) //스킵기능
    {
        changeStage();
    }

    if (CutTime >= _info._duration) //장면체인지
    {
        CutTime = 0.0f;
        setScene();
    }
    if (CutTime<-1.0f && CutTime>-2.0f) 
    {
        changeStage();
    }
    return 0;
}

int CutScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool CutScene::Initialize()
{
    //이미지셋팅
    pBObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pBObj->GetComponent<Engine::SpriteRenderer>();
    std::wstring name = L"CutScene_Part" + std::to_wstring(_stageNum);
    pSpriteRenderer->BindTexture(Resource::FindTexture(name.c_str()));
    pSpriteRenderer->SetIndex(0);
    pBObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"CutScene", pBObj); pBObj->SetRenderGroup((int)RenderGroup::BackGround);
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, 1); //컷신 정보 불러오기

    //사운드셋팅
    std::string soundName = "Bgm_Sound_BGM_Cut_Scene_" + (_stageNum);
    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound(soundName.c_str(), (int)SoundGroup::BGM, 1.0f, false);
    //페이드셋팅(들어갈 때 한 번, 나갈 때 한 번..)
    Fade::FadeInfo info;
    info.option = Fade::Fade_Option::Fade_In;
    info.color = 0xFF000000;
    info.duration = 3.0f;
    info.life = 30.0f;
    pFadeObj = Engine::GameObject::Create();
    Fade* _pFade = pFadeObj->AddComponent<Fade>(info);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", pFadeObj); pFadeObj->SetRenderGroup((int)RenderGroup::Fade);

    return true;
}

void CutScene::setScene()
{
    _info = DataManager::GetInstance()->GetCutSceneInfo(_stageNum, _info._order + 1); //다음 장면으로 변경
    if (_info._part != 0) {
        Engine::SpriteRenderer* pSpriteRenderer = pBObj->GetComponent<Engine::SpriteRenderer>();
        pSpriteRenderer->SetIndex(_info._order);
        if (_info._voiceTag != L"")
        {
         //   std::string str = "Voice_Sound_Voice_Enemy_Dead" + wstring_to_string(_info._voiceTag);
            Sound::StopSound((int)SoundGroup::Voice);
            Sound::PlaySound("Voice_Sound_Voice_Enemy_Dead1", (int)SoundGroup::Voice, 1.0f, false);
        }
        if (_info._dummySoundTag != L"")
        {
            Sound::PlaySound(wstring_to_string(_info._dummySoundTag).c_str(), (int)SoundGroup::SFX, 1.0f, false);
        }
    }
    else 
    {
        CutTime = -10.0f;
        Fade::FadeInfo info;
        info.option = Fade::Fade_Option::Fade_Out;
        info.color = 0xFF000000;
        info.duration = 3.0f;
        info.life = 30.0f;
        pFadeObj = Engine::GameObject::Create();
        Fade* _pFade = pFadeObj->AddComponent<Fade>(info);
        Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", pFadeObj); pFadeObj->SetRenderGroup((int)RenderGroup::Fade);
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