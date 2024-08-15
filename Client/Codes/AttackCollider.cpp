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
	gameObject._isDrawCollider = true;
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
			auto& [delay, duration, collider] = _colliders[i][j];

			if (delay > 0.f)
			{
				delay -= deltaTime;

				if (0.f > delay)
					collider->SetActive(true);
			}

			if (collider->IsActive())
			{
				duration -= deltaTime;
				collider->SetOffset(_pGrid->GetTileCenter(j, i) - transform.position);

				if (0.f > duration)
				{
					duration = 0.f;
					collider->SetActive(false);
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
			auto& [delay, duration, collider] = _colliders[i][j];
			if (nullptr == collider)
			{
				Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Attack");
				pCollider->SetScale(Vector3(90.f, 90.f, 0.f));
				pCollider->SetActive(false);
				collider = pCollider;
			}
		}
	}
}

void AttackCollider::OnCollider(float delay, float duration, int coordX, int coordY, const AttackInfo& info, int index)
{
	if (0 > coordX || 0 > coordY || _maxCoordX <= coordX || _maxCoordY <= coordY)
		return;

	auto& [_delay, _duration, _collider] = _colliders[coordY][coordX];
	_delay = delay;
	_duration = duration;
	_info[index] = info;
}
