#pragma once
#include "UIComponent.h"

namespace Engine
{
	class TextRenderer;
	class Gameobject;
}

class CardSystem;
class UI;
class DeckSystem : public UIComponent
{
	enum DeckType { Current, Grave, Extra, End };
public:
	explicit DeckSystem();
private:
	virtual ~DeckSystem() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	CardSystem*				_pCardSystem = nullptr;
	Engine::TextRenderer*	_pDeck = nullptr;
	Engine::TextRenderer*	_pGrave = nullptr;
	UI*		_pReLoad = nullptr;
	std::wstring _deckCount[End];
};