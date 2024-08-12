#include "Grid.h"
#include "Client_Define.h"
#include "Tile.h"

Grid::Grid(const wchar_t* name, MapInfo& _mapInfo,const Vector3& position)
	:MonoBehavior(name)
{
	Engine::Texture* pBitmap = Resource::FindTexture(L"Tile");
	_tileSize = pBitmap->GetImage(0)->GetSize();

	float width = _tileSize.width + _mapInfo.tileOffsetX;
	float height = _tileSize.height + _mapInfo.tileOffsetY;

	float maxWidth = _mapInfo.width * width;
	float maxHeight = _mapInfo.height * height;

	float offsetX = maxWidth * -0.5f + width * 0.5f;
	float offsetY = maxHeight * -0.5f + height * 0.5f + _mapInfo.mapOffsetY;

	_tiles.resize((size_t)_mapInfo.height);
	for (auto& iter : _tiles)iter.resize((size_t)_mapInfo.width);

	for (int i = 0; i < (int)_mapInfo.height; i++)
	{
		for (int j = 0; j < (int)_mapInfo.width; j++)
		{
			Tile* pTile = Tile::Create(Vector3(offsetX + j * (width), offsetY + i * (height), 0.f) + position,_mapInfo.mapData[i][j]);
			Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", pTile);
			_tiles[i][j] = pTile;
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

	bool canMove = (_tiles[y][x]->canMove);

	return canMove;
}

Vector3 Grid::GetTileCenter(int x, int y) const
{
	int width = (int)_tiles[0].size();
	int height = (int)_tiles.size();
	y = std::clamp(y, 0, height - 1);
	x = std::clamp(x, 0, width - 1);
	return _tiles[y][x]->transform.position;
}
