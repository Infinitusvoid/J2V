#include "Tonix.h"


#include <iostream>
#include "Order_Creator_3d.h"

namespace Cosmos {

	
	void Tonix::run_foo()
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

	void Tonix::run_computation()
	{
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		Cosmos::Data_Types::Object3d_Data* pobj = new Cosmos::Data_Types::Object3d_Data();

		

		glm::vec3 pos = glm::vec3(0.0f, y *  10.0f, 20.0f);
		glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		Cosmos::Order_Creator_3d::Create(pobj, pos, rot, scale);


		data.push_back(pobj);

		//Douplicate staff ( grrr!!! )
		//builder (unceserry non optimal ugly way for now)
		//{
			lve::Lve_model::Builder* modelBuilder = new lve::Lve_model::Builder();


			modelBuilder->vertices = std::vector<lve::Lve_model::Vertex>();//size);
			for (const Cosmos::Data_Types::Vert& vert : pobj->vertices)//for (const Proc::Vert& vert : data_obj->vertices)
			{
				modelBuilder->vertices.push_back(
					{ { vert.position.x, vert.position.y, vert.position.z },
													{ vert.color.r, vert.color.g, vert.color.b },
													{ vert.normal.x, vert.normal.y, vert.normal.z}
					}
				);
			}

			modelBuilder->indices = std::vector<uint32_t>(pobj->indices);

			model_builders.push_back(modelBuilder);
		//}
		


		



	}

	void Tonix::clean_up_if_needed()
	{
		//clean data
		if (data.size() > 0)
		{
			for (int i = 0; i < data.size(); i++)
			{
				delete data[i];
			}

			data.clear();
		}

		//clean builder grrr things to be removed in future
		if ( model_builders.size() > 0)
		{
			for (int i = 0; i < model_builders.size(); i++)
			{
				delete model_builders[i];
			}
			model_builders.clear();
		}
	}

	void Tonix::run()
	{
		continue_executing = true;

		while (continue_executing)
		{

			if (state == state_idle)
			{
				clean_up_if_needed();
			}
			else if (state == state_compute)
			{
				std::cout << "Tonix::run() State:state_compute" << std::endl;

				state = state_busy;
				run_computation();
				state = state_done;
			}

			
			//we externaly set to idle when we copy data
			
		}
		clean_up_if_needed();
	
	}

	

}