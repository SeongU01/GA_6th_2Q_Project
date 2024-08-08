#pragma once

inline void PlayRandomSound(const int count, const char* soundTag, float volume = 1.f, SoundGroup soundGroup = SoundGroup::SFX)
{
	std::uniform_int_distribution<int> randomSoundNumber(1, count);	
	std::string tag = soundTag;
	tag += "0" + std::to_string(randomSoundNumber(g_gen));

	Sound::PlaySound(tag.c_str(), (int)soundGroup, volume);
}

struct 
{
	template<typename T>
	inline void Log(T a)
	{
		std::cout << a << std::endl;
	}
}Debug;
