#pragma once

// A temporary IMGUI Layer class until we've got proper layer abstraction.

#include <vector>
#include <string>

class ImGUILayer
{
public:
	
	ImGUILayer();
	~ImGUILayer();

	void AddFloatSlider(float* targetValue, float min, float max);
	
private:

	struct FloatSliderData{
	
		std::string name;
		float* value;
		float minVal;
		float maxVal;
	};

	std::vector<FloatSliderData> m_FloatSliders;

};