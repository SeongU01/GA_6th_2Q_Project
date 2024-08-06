#include "GridMovement.h"
#include "Client_Define.h"
#include "Grid.h"
GridMovement::GridMovement(const wchar_t* name)
	:MonoBehavior(name)
{
}

void GridMovement::Awake()
{
}

void GridMovement::Start()
{
	Engine::GameObject* pObject=Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map");
	if (nullptr != pObject)
	{
		_grid = pObject->GetComponent<Grid>();
	}
}

void GridMovement::Update(const float& deltaTime)
{
	//�����ֳ����� ����ó��
	
	//�̵�ó��
}

void GridMovement::LateUpdate(const float& deltaTime)
{
}

bool GridMovement::CanMove(Vector3& postion)
{
	return true;
}
