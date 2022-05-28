#pragma once

#include <thread>

namespace Cosmos
{
	class Tonix
	{
		public:
			void run();
			std::atomic<bool> continue_executing;
	};
	
	
	
}


