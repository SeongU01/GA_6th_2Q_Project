#include "Defense.h"

//component
#include "HP.h"
#include "DefenseScript.h"

#include "Client_Define.h"
void Defense::Initialize(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring tag, const wchar_t* textureTag)
{
	SetRenderGroup((int)RenderGroup::Object);
	SetName(tag.c_str());
	AddComponent<HP>(L"HP", 2);
	AddComponent<DefenseScript>(L"DefenseScript", gridRange);
	_pSpriteRenderer->BindTexture(Resource::FindTexture(textureTag));
	_pSpriteRenderer->SetDrawOffset(yoffset);
}

Defense* Defense::Create(const std::pair<Vector3, Vector3>& gridRange, const Vector3& yoffset, std::wstring tag, const wchar_t* textureTag)
{
	Defense* pInstance = new Defense;
	pInstance->Initialize(gridRange,yoffset,tag,textureTag);
	return pInstance;
}
