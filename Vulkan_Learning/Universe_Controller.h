#pragma once

#include "lve_frame_info.h"


namespace Cosmos
{
	class Universe_Controller
	{
		public:
			Universe_Controller();
			~Universe_Controller();

			void loop(GLFWwindow* window, lve::FrameInfo& frameInfo);
		private:
			float ellapsed_time{};
	};

}

