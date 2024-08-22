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
		static void ResetInstance() { _pInstance = nullptr; }
	private:
		static T* _pInstance;
	};
	template <typename T>
	T* SingleTon<T>::_pInstance = nullptr;

	inline int RandomGeneratorInt(int first, int last)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> random(first, last);

		return random(gen);
	}
	inline float RandomGeneratorFloat(float first, float last)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> random(first, last);

		return random(gen);
	}

	template<typename T>
	inline constexpr T RandomGeneratorReal(T first, T last)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real<T> random(first, last);

		return random(gen);
	}
}