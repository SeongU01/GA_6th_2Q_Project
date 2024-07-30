#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Camera;
	class Renderer : public Base
	{
	public:
		struct RenderGroupInfo
		{
			ID2D1DeviceContext* pDeviceContext;
			int size;
			int width;
			int height;
		};
	private:
		using RenderGroup = std::vector<std::list<GameObject*>>;
		using SortInfo = std::vector<bool(*)(GameObject*, GameObject*)>;

	private:
		explicit Renderer() = default;
		virtual ~Renderer() = default;

	public:
		void Render_GameObject();
		bool SetUpRenderer(const RenderGroupInfo& info);
		void SetSortGroup(int sortGroup, bool(*sortFunc)(GameObject*, GameObject*));
		bool AddRenderGroup(int group, GameObject* pObject);
		void ResetRenderGroup();

	private:
		// Base을(를) 통해 상속됨
		void Free() override;

	public:
		static Renderer* Create();

	private:
		RenderGroupInfo			_info{};
		RenderGroup				_renderGroup{};
		SortInfo				_sortInfo{};
		Camera*					_pCurrCamera = nullptr;
		bool					_isSetUp = false;
	};
}

