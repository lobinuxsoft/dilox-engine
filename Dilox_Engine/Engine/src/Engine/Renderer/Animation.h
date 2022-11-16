#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Engine/Renderer/SubTexture2D.h"

namespace DiloxGE
{
	class DGE_API Animation
	{
	public:
		Animation(const std::vector<Ref<SubTexture2D>>& frames, const float& speed)
			: m_Frames(frames), m_Speed(speed) { }

		Ref<SubTexture2D> Animate(const float& delta)
		{
			m_Frame += delta * m_Speed;

			return m_Frames[static_cast<int>(m_Frame / m_Frames.size()) % m_Frames.size()];
		}

		void SetSpeed(const float& speed) { m_Speed = speed; }

		static Ref<Animation> Create(const std::vector<Ref<SubTexture2D>>& frames, const float& speed);

	private:
		std::vector<Ref<SubTexture2D>> m_Frames;
		float m_Speed;
		float m_Frame = 0.0f;
	};
}