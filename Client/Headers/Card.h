#pragma once
#include "MonoBehavior.h"

enum class CardType;
class Card final : public Engine::MonoBehavior
{
public:
	explicit Card(const wchar_t* name, int costMana, float costTime, float delayBefore, float delayAfter, const wchar_t* textureTag, int index, CardType type, int targetType, int targetNum);
private:
	virtual ~Card() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	const wchar_t* _title = nullptr;
	int _cardID = 0;
	int _costMana = 0;
	float _costTime = 0.f;

	float _delayBefore = 0.f;
	float _delayAfter = 0.f;

	CardType _cardType;
	int _target_Type_ID;
	int _target_Num;
	
	/*Additive_CharState
	CharState_Num
	Additive_CardState
	CardState_Num
	Additive_AfterState
	Variable*/
};

