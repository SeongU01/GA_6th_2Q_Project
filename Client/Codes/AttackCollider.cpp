#include "AttackCollider.h"

// Component
#include "Grid.h"
#include "Collider.h"
#include "Player.h"

#include "Client_Define.h"

AttackCollider::AttackCollider()
	: MonoBehavior(L"Attack")
{	
}

void AttackCollider::Awake()
{	
}

void AttackCollider::Start()
{
}

void AttackCollider::Update(const float& deltaTime)
{
	for (int i = 0; i < _maxCoordY; i++)
	{
		for (int j = 0; j < _maxCoordX; j++)
		{
			if (_colliders[i][j].second->IsActive())
			{
				_colliders[i][j].first -= deltaTime;
				_colliders[i][j].second->SetOffset(_pGrid->GetTileCenter(j, i) - transform.position);

				if (0.f >= _colliders[i][j].first)
				{
					_colliders[i][j].first = 0.f;
					_colliders[i][j].second->SetActive(false);
				}
			}
		}
	}
}

void AttackCollider::LateUpdate(const float& deltaTime)
{
}

void AttackCollider::Initialize(const wchar_t* name, int width, int height)
{	
	_maxCoordX = width;
	_maxCoordY = height;
	_colliders.resize(height);

	for (auto& collider : _colliders)
		collider.resize(width);

	_pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();

	for (size_t i = 0; i < _colliders.size(); i++)
	{
		for (size_t j = 0; j < _colliders[i].size(); j++)
		{
			if (nullptr == _colliders[i][j].second)
			{
				Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Attack");
				pCollider->SetScale(Vector3(90.f, 90.f, 0.f));
				pCollider->SetActive(false);
				_colliders[i][j].second = pCollider;
			}
		}
	}
}

void AttackCollider::OnCollider(float time, int coordX, int coordY, const AttackInfo& info)
{
	if (0 > coordX || 0 > coordY || _maxCoordX <= coordX || _maxCoordY <= coordY)
		return;

	_colliders[coordY][coordX].first = time;
	_colliders[coordY][coordX].second->SetActive(true);
	_info = info;
}
