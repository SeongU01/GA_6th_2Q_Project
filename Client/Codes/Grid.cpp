#include "Grid.h"
#include "Client_Define.h"
#include "Tile.h"

Grid::Grid(const wchar_t* name, MapInfo& _mapInfo,const Vector3& position)
	:MonoBehavior(name)
{
	_currMapInfo = _mapInfo;
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

Vector3 Grid::GetCurrGrid(const Vector3& _position) const
{
	// 타일 크기와 오프셋을 고려하여 그리드 좌표를 계산
	float width = _tileSize.width + _currMapInfo.tileOffsetX;
	float height = _tileSize.height + _currMapInfo.tileOffsetY;

	// 그리드의 시작 위치
	float startX = _tiles[0][0]->transform.position.x - (width * 0.5f);
	float startY = _tiles[0][0]->transform.position.y - (height * 0.5f);

	// 현재 위치에서 타일 좌표를 계산
	int gridX = (int)((_position.x - startX) / width);
	int gridY = (int)((_position.y - startY) / height);

	// 그리드 범위를 벗어나는 경우 쓰레기 값 반환
	if (gridX < 0 || gridX >= (int)_tiles[0].size() || gridY < 0 || gridY >= (int)_tiles.size())
	{
		return Vector3(-1.f, -1.f, -1.f); // 쓰레기 값
	}

	// 타일의 경계 내에 있는지 확인
	float localX = (_position.x - (startX + gridX * width));
	float localY = (_position.y - (startY + gridY * height));

	// 타일 경계 내에 있는지 확인
	if (localX < 10 || localX >= width || localY < 10 || localY >= height)
	{
		return Vector3(-1.f, -1.f, -1.f); // 쓰레기 값
	}

	// 유효한 그리드 좌표 반환
	return Vector3((float)gridX, (float)gridY, 0.f);
}
