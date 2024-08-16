#pragma once
#include "MonoBehavior.h"
#include "DataManager.h"

class Tile;

class Grid :public Engine::MonoBehavior
{
public:
	explicit Grid(const wchar_t* name, const MapInfo& _mapInfo, const Vector3& position);
private:
	virtual ~Grid() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	bool IsTileWalkable(int x, int y) const;
	Vector3 GetTileCenter(int x, int y) const;
	Vector3 GetCurrGrid(const Vector3& _position)const;
	std::vector <std::vector<Tile*>> GetTiles()const { return _tiles; }
private:
	std::vector <std::vector<Tile*>>_tiles;
	MapInfo _currMapInfo;
	Vector3 _gridOffset;
	D2D_SIZE_F _tileSize;
};

