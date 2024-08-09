#pragma once
#include "MonoBehavior.h"
#include "DataManager.h"

class Pannel;
class ToolTip :public Engine::MonoBehavior
{
public:
	explicit ToolTip(const wchar_t* name);
private:
	virtual ~ToolTip() = default;
public:
	//정보창 활성화/비활성화
	void ActiveToolTip(bool _isTrue);
	Vector3 AddToolTip(const ToolTipInfo& _info,Vector3 position);
	void DeleteToolTip(std::wstring _id) { _toolTipList.erase(_id); } //삭제
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	std::vector<ToolTipInfo> _toolTipinfos; 
	std::map<std::wstring, Pannel*> _toolTipList; // 활성화된 패널을 관리하는 맵
};

