#pragma once
#include "Component.h"

namespace Engine
{
	class GameObject;
	class SpriteRenderer;
	class Transform;
	class Collider : public Component
	{
		friend GameObject;	
	public:
		explicit Collider(const char* name);
	private:
		virtual ~Collider() = default;

	public:
		void LateUpdate(const float& deltaTime) override;

	public:
#ifdef _DEBUG
		D2D1_RECT_F GetColliderRect() const;
#endif
		GameObject* GetOwner() { return _pOwner; }
		const Vector3& GetScale() const { return _scale; }
		const Vector3& GetPosition() const { return _position; }
		const Vector3& GetOffset() const { return _offset; }

		_uint GetID() const { return _ID; }
		void SetScale(const Vector3& scale) { _scale = scale; }
		void SetOffset(const Vector3& offset) { _offset = offset; }		

	private:
		void Free() override;

	private:
		Vector3			_scale;
		Vector3			_position;
		Vector3			_offset;
		_uint			_ID				= 0;

		static _uint	g_ID;
	};
}
