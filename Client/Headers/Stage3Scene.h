#pragma once
#include "DefaultStageScene.h"

class Stage3Scene : public DefaultStageScene
{
private:
	explicit Stage3Scene() = default;
	virtual ~Stage3Scene() = default;

private:
	bool Initialize() override;

public:
	static Stage3Scene* Create();
};