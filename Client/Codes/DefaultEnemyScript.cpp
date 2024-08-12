#include "DefaultEnemyScript.h"
#include "Grid.h"

//component
#include "Animation.h"
#include "GridMovement.h"

#include "Client_Define.h"

DefaultEnemyScript::DefaultEnemyScript(const wchar_t* name, const Vector3& startPos)
	:MonoBehavior(name),_startPosition(startPos)
{
	
}

void DefaultEnemyScript::Awake()
{
	_movement = AddComponent<GridMovement>(L"Movement",500.f);
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Default_DefaultEnemy"))
		throw std::runtime_error("can't load animation!");
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);
}

void DefaultEnemyScript::Start()
{
	_gridPosition = _startPosition;
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);
}

void DefaultEnemyScript::Update(const float& deltaTime)
{
	if (Input::IsKeyDown(DIK_M))
	{
		gameObject.SetDead();
	}

}

void DefaultEnemyScript::LateUpdate(const float& deltaTime)
{
}
