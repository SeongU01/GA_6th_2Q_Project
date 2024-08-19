#pragma once
#include "GameObject.h"

class Pannel : public Engine::GameObject
{
public:
	struct PannelInfo
	{
		Vector3 size{};
		Vector3 position{};
		Engine::Transform* parent{};
		unsigned int outlineColor{};
		unsigned int fillColor{};
		float opacity = 1.f;
		float lineWidth = 1.f;
	};
private:
	explicit Pannel() = default;
	virtual ~Pannel() = default;

private:
	bool Initialize(const PannelInfo& info);
public:
	Vector3 GetSize() { return _info.size; }
public:
	static Pannel* Create(const PannelInfo& info);
private:
	PannelInfo _info;
};

