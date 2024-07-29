#pragma once
#include "Base.h"
#include <fmod.hpp>

namespace Engine
{
    class SoundManager : public Base, public SingleTon<SoundManager>
    {
        friend class SingleTon;
    private:
        struct FadeSound
        {
            float currVolum = 1.f;
            float targetVolum = 1.f;
        };
    private:
        using SoundData = std::unordered_map<std::string, FMOD::Sound*>;
    private:
        explicit SoundManager() = default;
        virtual ~SoundManager() = default;
        NOCOPY(SoundManager)

    public:
        void Update(const float& deltaTime);
        void PlaySound(const char* soundTag, int channelID, float volume, bool isLoop);
        void StopSound();
        void StopSound(int channelID);
        void SetVolume(int groupID, float volume);
        void SetFadeVolume(int groupID, float volume);
        void SetPitch(int groupID, float pitch);
        void SetMasterVolume(float volume);
        bool SetUpSound(int maxGroup);
        void LoadSound(const char* filePath);
        std::vector<std::string> GetSoundKey();

    private:
        // Base��(��) ���� ��ӵ�
        void Free() override;

    private:
        SoundData                           _soundData;
        FMOD::System*                       _pSystem = nullptr;
        FMOD::ChannelGroup*                 _pMasterChannelGroup = nullptr;
        std::vector<FMOD::ChannelGroup*>    _channelGroups;
        std::list<FMOD::Channel*>           _currPlayChannels;
        std::vector<FadeSound>              _soundVolum;
        int                                 _maxGroup = 0;
        bool                                _isSetUp = false;
    };
}