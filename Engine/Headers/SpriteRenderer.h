#pragma once
#include "Component.h"

#include "ShaderColor.h"
#include "ShaderComposite.h"
#include "ShaderMotionBlur.h"
#include "ShaderVignette.h"
#include "ShaderGaussianBluer.h"

namespace Engine
{
	class Transform;
	class Animation;
	class Texture;
	class Shader;
	class SpriteRenderer : public Component
	{
		friend class GameObject;
		friend class Renderer;
		using ShaderData = std::unordered_map<size_t, Shader*>;
	public:
		explicit SpriteRenderer(const wchar_t* name);
	private:
		virtual ~SpriteRenderer() = default;

	public:
		void Awake() override;
		void Render() override;

	public:
		void BindTexture(Texture* pTexture);
		void BindAnimation(Animation* pAnimation);
		void Draw();
		void Draw(ID2D1Bitmap* pBitmap);
		void DrawRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color = D2D1::ColorF::Lime, float width = 1.f);
		void DrawFillRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color, const float& opacity);
		void DrawLine(const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const D2D1::ColorF& color, float strokeWidth);
		void DrawTriangle(const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const D2D1_POINT_2F& point2, const D2D1::ColorF& color, float opacity = 1.f);

		template <typename T>
		T* AddShader()
		{
			static_assert(std::is_base_of<Shader, T>::value);
			
			if (nullptr != _shaderData[typeid(T).hash_code()])
				return nullptr;

			T* pShader = new T;
			pShader->Initialize(_pDeviceContext);

			_shaderData[typeid(T).hash_code()] = pShader;
			return pShader;
		}

		template <typename T>
		T* GetShader()
		{
			static_assert(std::is_base_of<Shader, T>::value);
			return static_cast<T*>(_shaderData[typeid(T).hash_code()]);
		}

		template <typename T, typename U>
		void CompositeShader()
		{
			static_assert(std::is_base_of<Shader, T>::value);
			static_assert(std::is_base_of<Shader, U>::value);

			_shaderData[typeid(T).hash_code()]->ComputeShader(GetBitmap());
			_shaderData[typeid(U).hash_code()]->ComputeShader(GetBitmap());

			ShaderComposite* pComposite = static_cast<ShaderComposite*>(_shaderData[typeid(ShaderComposite).hash_code()]);
			pComposite->CompositeShader(_shaderData[typeid(T).hash_code()]->GetEffect(),
										_shaderData[typeid(U).hash_code()]->GetEffect());

			_currShader = typeid(ShaderComposite).hash_code();
		}
	public:
		template <typename T>
		void SetShader()
		{
			static_assert(std::is_base_of<Shader, T>::value);
			_currShader = typeid(T).hash_code();
		}

		void SetIndex(const int index) { _index = index; }
		void SetDrawOffset(const Vector3& offset);
		void SetOneSelfDraw(bool isActive, const std::function<void()>& function = nullptr);

	private:
		ID2D1Bitmap* GetBitmap();
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		ShaderData				_shaderData;
		std::function<void()>	_oneSelfDrawFunction;
		Vector3					_drawOffset;
		Animation*				_pAnimation = nullptr;
		Texture*				_pTexture = nullptr;
		ID2D1DeviceContext*		_pDeviceContext = nullptr;
		ID2D1SolidColorBrush*	_pSolidColorBrush = nullptr;
		size_t					_currShader;
		int						_index = 0;
		bool					_isOneSelfDraw = false;
	};
}