#pragma once
#include "GameObject.h"

class Defense:public Engine::GameObject
{
private:
	explicit Defense() = default;
	virtual ~Defense() = default;
private:
	void Initialize(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring& tag, const wchar_t* textureTag);
public:
	static Defense* Create(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring& tag,const wchar_t* textureTag);
private:
	std::wstring name;
};

