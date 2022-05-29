#pragma once

#include <thread>
#include "Data_Types.h"
#include "Lve_model.h"

namespace Cosmos
{
	class Tonix
	{
		public:
			static constexpr int state_idle = 0;
			static constexpr int state_compute = 1;
			static constexpr int state_busy = 2;
			static constexpr int state_done = 3;

			Cosmos::Data_Types::VectorOfPointers_PointingTo_Procedural_ObjectData data;
			std::vector<lve::Lve_model::Builder*> model_builders;

			void run_foo();
			void run();
			std::atomic<bool> continue_executing;
			std::atomic<int> state;
		private:
			void run_computation();
			void clean_up_if_needed();
	};
	
	
	
}


