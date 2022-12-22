#pragma once

#include "glm/glm.hpp"

namespace RoadMath {

	template <typename T>
	inline T clamp(T val, T min, T max)
	{
		if (val < min)
		{
			return min;
		}

		else if (val > max)
		{
			return max;
		}

		else
		{
			return val;
		}
	}

	template <typename T>
	inline T normalizeAngle(T val, T min, T max)
	{
		while (val > max)
		{
			val -= max;
		}

		while(val < min)
		{
			val += max;
		}
		
		return val;
	}

} // namespace RoadMath