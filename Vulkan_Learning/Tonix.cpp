#include "Tonix.h"


#include <iostream>

namespace Cosmos {

	
	void Tonix::Calc()
	{
		continue_executing = true;
		//cosmos_compute = false;

		//Tonix::njok = false;
		//cosmos_compute = true;
		//std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
		/*
		int sum = 0;
		for (int i = 0; i < 1000000; i++)
		{
			sum += 1;
		}
		*/
		//std::cout << sum << std::endl;

		int i = 0;
		while (continue_executing)//Tonix::cosmos_compute)
		{
			if (i % 100000000 == 0)
			{
				std::cout << "bing" << std::endl;
			}

			i++;

		}
	}

	void Tonix::doWork()
	{
		//std::thread worker(Tonix::Calc);
		//worker.join();
		//worker.


	}

	
}