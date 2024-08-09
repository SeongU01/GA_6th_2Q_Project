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
	if (_isTrue)  //활성화시킨다.
	{
		SetActive(true);
	}
	else //비활성화 시킨다
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