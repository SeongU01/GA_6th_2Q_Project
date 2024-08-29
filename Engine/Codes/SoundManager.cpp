#include "SoundManager.h"

using namespace Engine;

void Engine::SoundManager::Update(const float& deltaTime)
{
    for (int i = 0; i < _maxGroup; i++)
    {
        if (_soundVolum[i].currVolum > _soundVolum[i].targetVolum)
            _soundVolum[i].currVolum -= deltaTime;

        if (0.01f >= _soundVolum[i].currVolum)
        {
            _soundVolum[i].currVolum = 0.f;
            _channelGroups[i]->stop();
        }

        _channelGroups[i]->setVolume(_soundVolum[i].currVolum);
    }

    auto iter_end = _currPlayChannels.end();
    for (auto iter = _currPlayChannels.begin(); iter != iter_end;)
    {
        bool isPlaying = false;
        (*iter)->isPlaying(&isPlaying);

        if (!isPlaying)
            iter = _currPlayChannels.erase(iter);
        else
            iter++;
    }

    _pSystem->update();
}

FMOD::Channel* Engine::SoundManager::PlaySound(const char* soundTag, int groupID, float volume, bool isLoop)
{
    FMOD::Sound* pSound = _soundData[soundTag];

    if (nullptr != pSound)
    {
        FMOD::Channel* pChannel = nullptr;
        _currPlayChannels.push_back(pChannel);

        _pSystem->playSound(pSound, _channelGroups[groupID], FALSE, &pChannel);
        if (isLoop) pChannel->setMode(FMOD_LOOP_NORMAL);
        pChannel->setVolume(volume);

        return pChannel;
    }

    return nullptr;
}

void Engine::SoundManager::StopSound()
{
    _pMasterChannelGroup->stop();
}

void Engine::SoundManager::StopSound(int groupID)
{
    _channelGroups[groupID]->stop();
}

void Engine::SoundManager::PauseSound(int groupID, bool isPause)
{
    _channelGroups[groupID]->setPaused(isPause);
}

void Engine::SoundManager::SetVolume(int groupID, float volume)
{
    _soundVolum[groupID].currVolum = volume;
    _soundVolum[groupID].targetVolum = volume;
}

void Engine::SoundManager::SetFadeVolume(int groupID, float volume)
{
    _soundVolum[groupID].targetVolum = volume;
}

void Engine::SoundManager::SetPitch(int groupID, float pitch)
{
    _channelGroups[groupID]->setPitch(pitch);
}

void Engine::SoundManager::SetMasterVolume(float volume)
{
    _pMasterChannelGroup->setVolume(volume);
}

bool Engine::SoundManager::SetUpSound(int maxGroup)
{
    int numsoftwarechannels = 0;

    FMOD::System_Create(&_pSystem);
    _pSystem->getSoftwareChannels(&numsoftwarechannels);
    _pSystem->init(numsoftwarechannels, FMOD_INIT_NORMAL, nullptr);
   
    _channelGroups.resize(maxGroup);
    _soundVolum.resize(maxGroup);
    _maxGroup = maxGroup;

    for (int i = 0; i < maxGroup; i++)
    {
        char name[8] = "";
        sprintf_s(name, "%d", i);
        _pSystem->createChannelGroup(name, &_channelGroups[i]);
    }

    _pSystem->getMasterChannelGroup(&_pMasterChannelGroup);

    for (auto& Group : _channelGroups)
        _pMasterChannelGroup->addGroup(Group);

    _isSetUp = true;

    return true;
}

void Engine::SoundManager::SetMode(int groupID, FMOD_MODE mode)
{
    _channelGroups[groupID]->setMode(mode);
}

void Engine::SoundManager::LoadSound(const char* path)
{
    _finddatai64_t  fd;
    intptr_t handle;
    int result = 0;

    char rootPath[256] = "";

    strcpy_s(rootPath, sizeof(rootPath), path);
    strcat_s(rootPath, sizeof(rootPath), "/*");
    handle = _findfirst64(rootPath, &fd);

    if (-1 != handle)
    {
        int count = 0;
        while (true)
        {
            result = _findnext64(handle, &fd);

            if (-1 == result)
                break;

            if (!strcmp(".", fd.name) || !strcmp("..", fd.name))
                continue;
            
            if (0 == result && (fd.attrib & _A_SUBDIR))
            {
                int index = 0;
                char currPath[256] = "";

                while ('*' != rootPath[index])
                {
                    currPath[index] = rootPath[index];
                    index++;
                }

                strcat_s(currPath, sizeof(currPath), fd.name);
                LoadSound(currPath);
                continue;
            }

            char soundTag[64] = "";
            char filePath[256] = "";

            strcpy_s(filePath, sizeof(filePath), path);
            strcat_s(filePath, sizeof(filePath), "/");
            strcat_s(filePath, sizeof(filePath), fd.name);

            int index = 0;
            int offset = 0;
            int length = (int)strlen(filePath);

            while (3 != offset)
            {
                if ('/' == path[index++])
                    offset++;
            }

            offset = index;
            index = 0;
            while (offset < length)
            {
                soundTag[index] = filePath[offset++];

                if ('.' == filePath[offset])
                    break;

                if (soundTag[index] == '/')
                    soundTag[index] = '_';

                index++;
            }

            FMOD::Sound* pSound = nullptr;
            _pSystem->createSound(filePath, FMOD_DEFAULT, 0, &pSound);
            _soundData[soundTag] = pSound;
        }
    }
}

std::vector<std::string> Engine::SoundManager::GetSoundKey()
{
    std::vector<std::string> soundKey;

    for (auto& Data : _soundData)
        soundKey.push_back(Data.first);

    return soundKey;
}

void Engine::SoundManager::Free()
{
    if (!_isSetUp)
        return;
    
    for (auto& Pair : _soundData)
        Pair.second->release();

    for (auto& Group : _channelGroups)
        Group->release();

    _pMasterChannelGroup->release();

    _pSystem->close();
    _pSystem->release();

    _soundData.clear();
}
