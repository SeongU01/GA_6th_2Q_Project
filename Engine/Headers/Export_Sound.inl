#pragma once

// SoundMgr
FMOD::Channel* PlaySound(const char* soundTag, int channelID, float volume = 1.f, bool isLoop = false)
{
	return Engine::SoundManager::GetInstance()->PlaySound(soundTag, channelID, volume, isLoop);
}
void DistancePlaySound(const Vector3& position, const char* soundTag, int groupID, bool isloop = false)
{
	//Engine::SoundManager::GetInstance()->PlaySound(soundTag, groupID, isloop, position);
}
inline void SetFadeVolume(int groupID, float volume)
{
	Engine::SoundManager::GetInstance()->SetFadeVolume(groupID, volume);
}
inline void SetVolume(int groupID, float volume)
{
	Engine::SoundManager::GetInstance()->SetVolume(groupID, volume);
}
void StopSound(int groupID)
{
	Engine::SoundManager::GetInstance()->StopSound(groupID);
}
void SetSoundTarget(Engine::GameObject* pTarget)
{
	// Engine::SoundManager::GetInstance()->SetSoundTarget(pTarget);
}
void PauseSound(int groupID, bool isPause)
{
	Engine::SoundManager::GetInstance()->PauseSound(groupID, isPause);
}