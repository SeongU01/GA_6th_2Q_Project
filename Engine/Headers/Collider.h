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
		explicit Collider(const wchar_t* name);
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

		void SetScale(const Vector3& scale) { _originScale = scale; }
		void SetOffset(const Vector3& offset) { _offset = offset; }		

		void InsertOther(Collider* pCollider);
		void EraseOther(Collider* pCollider);
		bool FindOther(Collider* pCollider);

	private:
		void Free() override;

	private:
		std::unordered_set<Collider*>	_collidedOthers;
		Vector3							_originScale;
		Vector3							_scale;
		Vector3							_position;
		Vector3							_offset;
	};
}
