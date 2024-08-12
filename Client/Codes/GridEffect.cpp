#include "GridEffect.h"

// Component
#include "Effect.h"
#include "Grid.h"

#include "Client_Define.h"

GridEffect::GridEffect(int width, int height)
	: MonoBehavior(L"GridEffect")
{
	_gridEffects.resize(height);

	for (auto& gridEffect : _gridEffects)
		gridEffect.resize(width);
}

void GridEffect::Awake()
{
	Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	
	for (int i = 0; i < _gridEffects.size(); i++)
	{
		for (int j = 0; j < _gridEffects[i].size(); j++)
		{
			auto pEffect = Engine::GameObject::Create();
			pEffect->SetActive(false);
			Effect::EffectInfo info;
			info.renderGroup = RenderGroup::BackEffect;
			info.position = pGrid->GetTileCenter(j, i);
			info.isFixFrame = true;
			info.fixFrame = 0;
			info.textureTag = L"GridEffect";
			info.isInfinity = true;
			pEffect->AddComponent<Effect>(info);
			Engine::AddObjectInLayer((int)LayerGroup::Object, L"Object", pEffect);
			_gridEffects[i][j] = pEffect;
		}
	}
}

void GridEffect::Start()
{	
}

void GridEffect::Update(const float& deltaTime)
{
	for (auto& height : _gridEffects)
	{
		for (auto& width : height)
		{
			width->SetActive(false);
		}
	}
}

void GridEffect::LateUpdate(const float& deltaTime)
{
}

void GridEffect::OnEffect(int x, int y, int type)
{
	if (y >= (int)_gridEffects.size() || y < 0)
		return;

	if (x >= (int)_gridEffects[y].size() || x < 0)
		return;

	_gridEffects[y][x]->SetActive(true);
	auto pEffect = _gridEffects[y][x]->GetComponent<Effect>();
	pEffect->SetFixFrame(type);
}
