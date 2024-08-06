#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class TextRenderer;
}

class CardManagement final : public Engine::Base, public Engine::SingleTon<CardManagement>
{
	using RichText = std::tuple<unsigned int, unsigned int, std::wstring, unsigned int>;
	friend class SingleTon;

	enum EffectType { Test1, Test2, Test3 };
private:
	explicit CardManagement() = default;
	virtual ~CardManagement() = default;

public:
	bool LoadCard(const wchar_t* filePath);
	void SetRichText(int ID, Engine::TextRenderer* pTextRenderer);

private:
	bool LoadCardDataOptionText(const wchar_t* filePath);
	bool LoadCardDataRichText(const wchar_t* filePath);
	bool LoadCardData(const wchar_t* filePath);

private:
	// Base��(��) ���� ��ӵ�
	void Free() override;

private:
	std::vector<Engine::GameObject*> _cards;
	std::vector<std::wstring> _texts;
	std::vector<std::list<RichText>> _richTexts;
};