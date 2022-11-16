#include "dgepch.h"
#include "Animation.h"

namespace DiloxGE
{
	Ref<Animation> Animation::Create(const std::vector<Ref<SubTexture2D>>& frames, const float& speed)
	{
		return CreateRef<Animation>(frames, speed);
	}
}