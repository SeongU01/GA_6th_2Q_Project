#pragma once
#include "MonoBehavior.h"
#include "DataManager.h"

class ToolTip :public Engine::MonoBehavior
{


public:
	explicit ToolTip(const wchar_t* name);
private:
	virtual ~ToolTip() = default;
public:
	//정보창 활성화/비활성화
	void ActiveToolTip(bool _isTrue);
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	std::set<const wchar_t*, ToolTipInfo*> _toolTipList;
};

