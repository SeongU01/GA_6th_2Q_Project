#include "DefaultEnemy.h"

void DefaultEnemy::Initialize()
{
}

DefaultEnemy* DefaultEnemy::Create()
{
	DefaultEnemy* pInstance = new DefaultEnemy;
	pInstance->Initialize();

	return pInstance;
}
