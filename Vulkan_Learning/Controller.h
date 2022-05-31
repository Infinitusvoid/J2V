#pragma once

#include "lve_frame_info.h"
#include "Data_Types.h"


namespace Cosmos::Controller
{
	void Initialization();

	void loop(GLFWwindow* window, lve::FrameInfo& frameInfo);

	void set_generate(bool value);
	bool get_generate_value();

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void init(GLFWwindow* window, lve::FrameInfo& frameInfo);
}
