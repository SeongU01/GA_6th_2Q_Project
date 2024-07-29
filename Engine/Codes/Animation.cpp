#include "Animation.h"
#include "Texture.h"
#include "ResourceManager.h"

using namespace Engine;

Engine::Animation::Animation(const char* name)
	: Component(name)
{
}

void Engine::Animation::Update(const float& deltaTime)
{
	if (_animationData.empty())
		return;

	_isLastFrame = false;
	_isFrameChange = false;

	Frame& currFrame = _animationData[_currAnimation][_currIndex];
	_currFrame += deltaTime * currFrame.duration;

	if (_isReverse)
	{
		if (1.f <= _currFrame)
		{
			_currFrame = 0.f;
			_currIndex--;
			_isFrameChange = true;
		}

		if (_currIndex < 0)
		{
			_isLastFrame = true;
			_currIndex = (int)_animationData[_currAnimation].size() - 1;
		}
	}
	else
	{
		if (1.f <= _currFrame)
		{
			_currFrame = 0.f;
			_currIndex++;
			_isFrameChange = true;
		}

		if (_currIndex >= (int)_animationData[_currAnimation].size())
		{
			_isLastFrame = true;
			_currIndex = 0;
		}
	}	
}

void Engine::Animation::LateUpdate(const float& deltaTime)
{
	auto iter_end = _frameEvents.end();
	for (auto iter = _frameEvents.begin(); iter != iter_end;)
	{
		if (!lstrcmp(iter->animation, _currAnimation) &&
			iter->activeFrame == _currIndex)
		{
			if (_isFrameChange)
			{
				iter->function();

				if (iter->isRepeat)
				{
					++iter;
					continue;
				}
				else
					iter = _frameEvents.erase(iter);
			}
			else
				++iter;
		}
		else
			++iter;
	}
}

ID2D1Bitmap* Engine::Animation::GetCurrentImage()
{	 
	return _animationData[_currAnimation][_currIndex].pBitmap;
}

ID2D1Bitmap* Engine::Animation::GetImage(const int index)
{
	if (0 > index)
		return _animationData[_currAnimation][0].pBitmap;
	else
		return _animationData[_currAnimation][index].pBitmap;
}

void Engine::Animation::AddFrame(const wchar_t* animationTag, ID2D1Bitmap* pBitmap, const float& speed)
{
	_animationData[animationTag].push_back(Frame(pBitmap, 1.f / speed));
}

void Engine::Animation::AddAllFrame(const wchar_t* animationTag, Texture* pTexture, const float& speed)
{
	for (auto& Bitmap : pTexture->_imageData)
		_animationData[animationTag].push_back(Frame(Bitmap, 1.f / speed));
}

void Engine::Animation::AddFrameEvent(const FrameEvent& event)
{
	_frameEvents.push_back(event);
}

bool Engine::Animation::IsBetweenFrame(const int first, const int last) const
{
	return (first <= _currIndex) && (last >= _currIndex);
}

bool Engine::Animation::LoadAnimation(const wchar_t* animationTag)
{
	ResourceManager* pResourceManager = ResourceManager::GetInstance();

	_animationData = pResourceManager->FindAnimation(animationTag);

	if (_animationData.empty())
		return false;

	return true;
}

void Engine::Animation::SetFrame(int frame)
{
	_currIndex = frame;
	_currFrame = 0.f;
	_isLastFrame = false;
}

void Engine::Animation::SetLastFrame()
{
	_currIndex = (int)_animationData[_currAnimation].size() - 1;
	_currFrame = 0.f;
}

void Engine::Animation::SetReversePlay(bool isActive)
{
	_isReverse = isActive;
}

bool Engine::Animation::ChangeAnimation(const wchar_t* nextAnimation)
{
	if (lstrcmp(_currAnimation, nextAnimation))
	{
		_currAnimation = nextAnimation;
		_currIndex = 0;
		_isLastFrame = false;
		_isFrameChange = true;
		return true;
	}

	return false;
}

bool Engine::Animation::IsCurrAnimation(const wchar_t* animation) const
{
	return !lstrcmp(_currAnimation, animation);
}

void Engine::Animation::Free()
{
	for (auto& Data : _animationData)
	{
		Data.second.clear();
		Data.second.shrink_to_fit();
	}

	_animationData.clear();
}