#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class TextRenderer;
}

class Pannel;
class Operator : public Engine::MonoBehavior
{
public:
	explicit Operator();
private:
	virtual ~Operator() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	bool Tutorial1();
	bool Tutorial2();
	bool Tutorial3();

private:
	void Text(const float& deltaTime, int count);

private:
	std::vector<const wchar_t*> _texts;
	Engine::TextRenderer*		_pTitle = nullptr;
	Engine::TextRenderer*		_pText = nullptr;
	Pannel*						_pPannel = nullptr;
	bool						_isTutorial = false;
	bool						_isTutorial1 = false;
	bool						_isTutorial2 = false;
	bool						_isTutorial2End = false;
	bool						_isTutorial3 = false;
	int							_count = 0;
	float						_length = 0.f;
};