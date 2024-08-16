#pragma once
#include "DefaultStageScene.h"

class Stage2Scene : public DefaultStageScene
{
private:
	explicit Stage2Scene() = default;
	virtual ~Stage2Scene() = default;

private:
	bool Initialize() override;

public:
	static Stage2Scene* Create();
};