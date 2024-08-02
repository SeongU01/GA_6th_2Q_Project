#include "Tile.h"
#include "Client_Define.h"
void Tile::Initialize(const Vector3& _position)
{
  _pTransform->position = _position;
  SetRenderGroup((int)RenderGroup::Tile);
  _pSpriteRenderer->BindTexture(Resource::FindTexture(L"Test"));
}

Tile* Tile::Create(const Vector3& position)
{
  Tile* pInstance = new Tile();
  pInstance->Initialize(position);
  return pInstance;
}
