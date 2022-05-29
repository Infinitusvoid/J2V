#pragma once

#include "lve_frame_info.h"

#include "Data_Types.h"

namespace Cosmos
{
	class Universe_Controller
	{
		public:
			Universe_Controller();
			~Universe_Controller();

			
			void loop(GLFWwindow* window, lve::FrameInfo& frameInfo);


			void generate(Cosmos::Data_Types::VectorOfPointers_PointingTo_Procedural_ObjectData& data);

			bool call_generate = false;

			void scroll_callback_2(float y);

		private:
			void init(GLFWwindow* window, lve::FrameInfo& frameInfo);

			

			

			float ellapsed_time{};
			bool first_loop_cycle;
	};

}

