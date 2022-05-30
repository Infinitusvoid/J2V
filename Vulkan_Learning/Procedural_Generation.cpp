#include "Procedural_Generation.h"
#include "Order_Creator_3d.h";

namespace Proc
{
	Procedural_Generation::Procedural_Generation()
	{
		
		//We call object 3d controller -> which calls something in Generative 3d collection ( example small_rnd_ring() )
		//Generate 3d collection -> is using one or multiple calls into Elements 3d to generate a scene (this is the class that's holds functions
		//representing art peaces ( think of it as gallery ) Chouls I rename it to ArtGallery or Gallery ? 

		//Gallery uses Elements to assemle it's art peaces
		//Elements uses operations to build it's staff

		Cosmos::Data_Types::Object3d_Data* pobj = new Cosmos::Data_Types::Object3d_Data();

		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 20.0f);
		glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		Cosmos::Order_Creator_3d::Create(pobj, pos, rot, scale);


		data.push_back(pobj);
		
	}

	Procedural_Generation::~Procedural_Generation()
	{

		for (int i = 0; i < data.size(); i++)
		{
			delete data[i];
		}

		data.clear();
	}

}