#pragma once
#include "Component.h"

namespace Engine
{
	class BitFlag final : public Component
	{	
	public:
		explicit BitFlag(const char* name) { _name = name; }
	private:
		virtual ~BitFlag() = default;

	public:
		void OnFlag(const _ullong& flag) { _flag |= flag; }
		void OffFlag(const _ullong& flag) { _flag &= ~flag; }
		void ToggleFlag(const _ullong& flag) { _flag ^= flag; }
		_ullong CheckFlag(const _ullong& flag) const { return _flag & flag; }
		void ResetFlag() { _flag = 0; }
		void SetFlag(const _ullong& flag) { _flag = flag; }

	private:
		virtual void Free() override;

	private:
		_ullong _flag = 0;
	};
}