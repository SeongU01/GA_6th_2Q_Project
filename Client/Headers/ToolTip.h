#pragma once
#include "MonoBehavior.h"
#include "DataManager.h"

class Pannel;
class ToolTip :public Engine::MonoBehavior
{
public:
	explicit ToolTip(const wchar_t* name);
	explicit ToolTip(const wchar_t* name, float scale);
private:
	virtual ~ToolTip() = default;
public:
	//정보창 활성화/비활성화
	void DontDestoryToolTips();
	void ActiveToolTip(bool _isTrue);
	Vector3 AddToolTip(const ToolTipInfo& _info,Vector3 position);
	void ClearToolTip();
	bool FindToolTip(std::wstring str) { return _toolTipList[str] != nullptr; }
	void DeleteToolTip(std::wstring str);
	void MirrorToolTip(int _direction);
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	float _scale=1.0f;
	std::map<std::wstring, Pannel*> _toolTipList = {}; // 활성화된 패널을 관리하는 맵
};

