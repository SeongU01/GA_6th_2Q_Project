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
	ResizeCollider();
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
				{
					collider->SetActive(true);
					delay = 0.f;
				}
			}

			if (collider->IsActive())
			{
				duration -= deltaTime;
				
				// 부모 scale.x 의 부호 영향을 안받도록 보정
				Vector3 offset = _pGrid->GetTileCenter(j, i) - transform.position;
				
				if (0.f > transform.scale.x)
					offset.x *= -1.f;

				collider->SetOffset(offset);

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

void AttackCollider::OnCollider(float delay, float duration, int coordX, int coordY, const AttackInfo& info, int index)
{
	if (0 > coordX || 0 > coordY || _maxCoordX <= coordX || _maxCoordY <= coordY)
		return;

	auto& [_delay, _duration, _collider] = _colliders[coordY][coordX];
	_delay = delay;
	_duration = duration;
	_info[index] = info;
}

void AttackCollider::ResizeCollider()
{
	_pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();

	_maxCoordX = (int)_pGrid->GetTiles()[0].size();
	_maxCoordY = (int)_pGrid->GetTiles().size();
	_colliders.resize(_maxCoordY);

	for (auto& collider : _colliders)
		collider.resize(_maxCoordX);

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

void AttackCollider::ResetAttackInfo()
{
	memset(_info, 0, sizeof(_info));
}
