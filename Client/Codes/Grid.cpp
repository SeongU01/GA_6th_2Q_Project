#include "Grid.h"
#include "Client_Define.h"
#include "Tile.h"

Grid::Grid(const wchar_t* name, const Vector3&	matrix, const Vector3& offset,const Vector3& position)
	:MonoBehavior(name)
{
	_gridOffset = offset;
	_tiles.resize((size_t)matrix.y);
	for (auto& iter : _tiles)iter.resize((size_t)matrix.x);

	for (int i = 0; i < (int)matrix.y; i++)
	{
		for (int j = 0; j < (int)matrix.x; j++)
		{
			Engine::Texture* pBitmap=Resource::FindTexture(L"Tile");
			_tileSize = pBitmap->GetImage(0)->GetSize();
			Tile* pTile = Tile::Create(Vector3(j * (_tileSize.width + offset.x), i * (_tileSize.height + offset.y), 0.f)+position);
			Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", pTile);
			_tiles[i][j]= pTile;
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

bool Grid::IsTileWalkable(int x, int y) const
{
	int width = (int)_tiles[0].size();
	int height = (int)_tiles.size();
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}
	return _tiles[y][x]->canMove;
}

Vector3 Grid::GetTileCenter(int x, int y) const
{
	return _tiles[y][x]->GetTransform()->position;
}
