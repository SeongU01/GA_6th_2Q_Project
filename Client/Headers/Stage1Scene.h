#pragma once
#include "DefaultStageScene.h"

class Stage1Scene : public DefaultStageScene
{
private:
	explicit Stage1Scene() = default;
	virtual ~Stage1Scene() = default;

public:
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;

public:
	static Stage1Scene* Create();

private:
	bool _isSelectCard = false;
};