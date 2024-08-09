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
	//����â Ȱ��ȭ/��Ȱ��ȭ
	void ActiveToolTip(bool _isTrue);
	Vector3 AddToolTip(const ToolTipInfo& _info,Vector3 position);
	void DeleteToolTip(std::wstring _id) { _toolTipList.erase(_id); } //����
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	std::vector<ToolTipInfo> _toolTipinfos; 
	std::map<std::wstring, Pannel*> _toolTipList; // Ȱ��ȭ�� �г��� �����ϴ� ��
};

