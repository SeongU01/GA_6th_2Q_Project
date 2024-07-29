#pragma once

namespace Engine
{
	template <typename T>
	void SafeRelease(T& pointer)
	{
		if (pointer)
		{
			pointer->Release();
			pointer = nullptr;
		}
	}

	template <typename T>
	class SingleTon
	{
	protected:
		SingleTon() = default;
		~SingleTon() = default;

	public:
		static T* GetInstance()
		{
			if (nullptr == _pInstance)
				_pInstance = new T;

			return _pInstance;
		}
	private:
		static T* _pInstance;
	};
	template <typename T>
	T* SingleTon<T>::_pInstance = nullptr;
}