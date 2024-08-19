#include "Defense.h"

//component
#include "HP.h"
#include "DefenseScript.h"

#include "Client_Define.h"
void Defense::Initialize(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring& tag, const wchar_t* textureTag, int hp)
{
	SetRenderGroup((int)RenderGroup::Object);
	name = tag;
	SetName(name.c_str());
	AddComponent<HP>(L"HP", hp);
	AddComponent<DefenseScript>(L"DefenseScript", gridRange, textureTag);
	_pSpriteRenderer->BindTexture(Resource::FindTexture(textureTag));
	_pSpriteRenderer->SetDrawOffset(yoffset);
}

Defense* Defense::Create(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring& tag, const wchar_t* textureTag, int hp)
{
	Defense* pInstance = new Defense;
	pInstance->Initialize(gridRange,yoffset,tag,textureTag,hp);
	return pInstance;
}
