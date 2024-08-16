#pragma once
#include "DefaultStageScene.h"

class Stage4Scene : public DefaultStageScene
{
private:
	explicit Stage4Scene() = default;
	virtual ~Stage4Scene() = default;

private:
	bool Initialize() override;

public:
	static Stage4Scene* Create();
};