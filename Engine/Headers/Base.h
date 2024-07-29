#pragma once
#include "Engine_Define.h"

namespace Engine
{
	class Base abstract
	{
	protected:
		explicit Base() = default;
		virtual ~Base() = default;

	public:
		void Release()
		{
			Free();
			delete this;
		}

		void SetActive(bool isActive) { _isActive = isActive; }
		void SetName(const char* name) { _name = name; }
		const char* GetName() { return _name; }
		bool IsActive() const { return _isActive; }

	protected:
		virtual void Free() = 0;

	protected:
		const char* _name = nullptr;
		bool		_isActive = true;
	};
}