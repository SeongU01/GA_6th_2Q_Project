#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class SpriteRenderer;
}
class GridInfo;
class HP;
class DefenseScript : public Engine::MonoBehavior
{
public:
	explicit DefenseScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange);
private:
	virtual ~DefenseScript() = default;
public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	HP* _pHP = nullptr;
	GridInfo* _pGridInfo = nullptr;
	Engine::SpriteRenderer* _pSpriteRenderer=nullptr;
	std::pair<Vector3, Vector3>_gridRange;
};
