#include "ToolTip.h"
#include "Client_Define.h"
#include "Tile.h"
#include "Pannel.h"

ToolTip::ToolTip(const wchar_t* name)
	:MonoBehavior(name)
{
}

void ToolTip::ActiveToolTip(bool _isTrue)
{
	if (_isTrue)  //Ȱ��ȭ��Ų��.
	{
		SetActive(true);
	}
	else //��Ȱ��ȭ ��Ų��
	{
		SetActive(false);
	}
}

void ToolTip::Awake()
{
}

void ToolTip::Start()
{
}

void ToolTip::Update(const float& deltaTime)
{
	
}

void ToolTip::LateUpdate(const float& deltaTime)
{

}