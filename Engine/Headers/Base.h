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
		inline void SetName(const wchar_t* name) { _name = name; }
		inline const wchar_t* GetName() const { return _name; }
		inline bool IsActive() const { return _isActive; }
		inline bool operator==(const wchar_t* str) { return !lstrcmp(_name, str); }
		inline bool operator!=(const wchar_t* str) { return lstrcmp(_name, str); }

	protected:
		virtual void Free() = 0;

	private:
		const wchar_t*	_name;
		bool			_isActive = true;
	};
}