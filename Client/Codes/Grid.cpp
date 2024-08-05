#include "Grid.h"
#include "Client_Define.h"
#include "Tile.h"

Grid::Grid(const wchar_t* name, const Vector3&	matrix, const Vector3& offset,const Vector3& position)
	:MonoBehavior(name)
{
	_gridOffset = offset;
	_grids.resize((size_t)matrix.y);
	for (auto& iter : _grids)iter.resize((size_t)matrix.x);

	for (int i = 0; i < (int)matrix.y; i++)
	{
		for (int j = 0; j < (int)matrix.x; j++)
		{
			Engine::Texture* pBitmap=Resource::FindTexture(L"Test");
			D2D_SIZE_F tileSize = pBitmap->GetImage(0)->GetSize();
			Tile* pTile = Tile::Create(Vector3(j * (tileSize.width + offset.x), i * (tileSize.height + offset.y), 0.f)+position);
			Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", pTile);
			_grids[i][j]= pTile;
		}
	}
}

void Grid::Awake()
{
}

void Grid::Start()
{
}

void Grid::Update(const float& deltaTime)
{
	int a = -0;
}

void Grid::LateUpdate(const float& deltaTime)
{
}
