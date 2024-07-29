#include "Shader.h"

Engine::Shader::~Shader()
{
	Free();
}

void Engine::Shader::Free()
{
	SafeRelease(_pShaderEffect);
}
