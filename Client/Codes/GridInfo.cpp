#include "GridInfo.h"
#include "Client_Define.h"
#include "Grid.h"

GridInfo::GridInfo(const wchar_t* name)
	:MonoBehavior(name)
{
}

void GridInfo::Awake()
{
}

void GridInfo::Start()
{
	Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map");
	if (nullptr != pObject)
	{
		_pGrid = pObject->GetComponent<Grid>();
	}
}

void GridInfo::Update(const float& deltaTime)
{
}

void GridInfo::LateUpdate(const float& deltaTime)
{
}
