#pragma once
#include "DefaultStageScene.h"

class Stage1Scene : public DefaultStageScene
{
private:
	explicit Stage1Scene() = default;
	virtual ~Stage1Scene() = default;

private:
	bool Initialize() override;

public:
	static Stage1Scene* Create();
};