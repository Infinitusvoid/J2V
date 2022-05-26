#include "Order_Creator_3d.h"

#include "ArtGallery_3d.h"

namespace Cosmos::Order_Creator_3d
{
	void Create(Cosmos::Data_Types::Object3d_Data* pobj)
	{

        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        pobj->position = glm::vec3(0.0f, 0.0f, 0.0f); //glm::vec3(x * 0.1, y * 0.1, 5.0f);//* 100 * 1.0f);




        //pobj.rotation = glm::vec3(0, 0, 0);
        pobj->scale = glm::vec3(1.0, 1.0, 1.0);

        

        Cosmos::ArtGallery_3d::Create(pobj, false);
        Cosmos::ArtGallery_3d::Create(pobj, true);


        
	}
}