#pragma once

#include <thread>

namespace Cosmos
{
	class Tonix
	{
		//static bool njok;

		public:
			void Calc();
			void doWork();
			std::atomic<bool> continue_executing;
	};
	
	
	
}


