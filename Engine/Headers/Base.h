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

		inline void SetActive(bool isActive) { _isActive = isActive; }
		inline void SetName(const char* name) { _name = name; }
		inline const char* GetName() const { return _name; }
		inline bool IsActive() const { return _isActive; }
		inline bool operator==(const char* str) { return !strcmp(_name, str); }
		inline bool operator!=(const char* str) { return strcmp(_name, str); }

	protected:
		virtual void Free() = 0;

	private:
		const char* _name = nullptr;
		bool		_isActive = true;
	};
}