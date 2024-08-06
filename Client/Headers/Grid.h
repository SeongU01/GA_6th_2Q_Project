#pragma once
#include "MonoBehavior.h"

class Tile;
class Grid :public Engine::MonoBehavior
{
public:
	explicit Grid(const wchar_t* name, const Vector3& matrix, const Vector3& offset, const Vector3& position);
private:
	virtual ~Grid() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	std::vector <std::vector<Tile*>>_grids;
	Vector3 _gridOffset;
	D2D_SIZE_F _tileSize;
};

