#pragma once
#include "MonoBehavior.h"

class Pannel;
class ToolTip :public Engine::MonoBehavior
{
public:
	struct ToolTipInfo {
		wchar_t* _title;
		wchar_t* _content;
		Pannel* _pannel;
	};

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
	std::set<wchar_t*, ToolTipInfo*> _toolTipList;
};

