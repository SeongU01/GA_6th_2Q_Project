#pragma once
#include "MonoBehavior.h"

class UI;
class MainUHD : public Engine::MonoBehavior
{
public:
	explicit MainUHD();
private:
	virtual ~MainUHD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	std::vector<UI*> _UIs;
};

