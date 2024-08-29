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
        FMOD::Channel* PlaySound(const char* soundTag, int channelID, float volume, bool isLoop);
        void StopSound();
        void StopSound(int channelID);
        void PauseSound(int groupID, bool isPause);
        void SetVolume(int groupID, float volume);
        void SetFadeVolume(int groupID, float volume);
        void SetPitch(int groupID, float pitch);
        void SetMasterVolume(float volume);
        bool SetUpSound(int maxGroup);
        void SetMode(int groupID, FMOD_MODE mode);

        void LoadSound(const char* filePath);
        std::vector<std::string> GetSoundKey();

    private:
        // Base을(를) 통해 상속됨
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