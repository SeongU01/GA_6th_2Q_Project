#include "HP.h"

HP::HP(const wchar_t* name, int maxHp)
	:MonoBehavior(name),_maxHP(maxHp)
{
}

void HP::Awake()
{
	_HP = _maxHP;
}

void HP::Start()
{
}

void HP::Update(const float& deltaTime)
{
	_HP = std::clamp(_HP, 0, _maxHP);
}

void HP::LateUpdate(const float& deltaTime)
{
}
