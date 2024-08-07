#include "Tile.h"
#include "Client_Define.h"
void Tile::Initialize(const Vector3& _position,const int _tileIndex)
{
  _pTransform->position = _position;
  SetRenderGroup((int)RenderGroup::Tile);
  _pSpriteRenderer->BindTexture(Resource::FindTexture(L"Tile"));
  _pSpriteRenderer->SetIndex(_tileIndex);
}

Tile* Tile::Create(const Vector3& position, const int _tileIndex)
{
  Tile* pInstance = new Tile();
  pInstance->Initialize(position,_tileIndex);
  return pInstance;
}
