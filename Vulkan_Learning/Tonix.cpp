#include "Tonix.h"


#include <iostream>

namespace Cosmos {

	
	void Tonix::run()
	{
		continue_executing = true;
		
		int i = 0;
		constexpr int steps_before_bing = 100000000;
		while (continue_executing)//Tonix::cosmos_compute)
		{
			if (i % steps_before_bing == 0)
			{
				std::cout << "bing" << std::endl;
			}
			i++;
		}
	}
	
}