#include "Order_Creator_3d.h"

#include "ArtGallery_3d.h"

namespace Cosmos::Order_Creator_3d
{
	void Create(
        Cosmos::Data_Types::Object3d_Data* pobj,
        const glm::vec3 pos,
        const glm::vec3 rot,
        const glm::vec3 scale)
	{

        //float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //pobj->position = glm::vec3(0.0f, 0.0f, 0.0f); //glm::vec3(x * 0.1, y * 0.1, 5.0f);//* 100 * 1.0f);

        pobj->position = pos;
        pobj->scale = scale;
        pobj->rotation = rot;


        //pobj.rotation = glm::vec3(0, 0, 0);
        //pobj->scale = glm::vec3(1.0, 1.0, 1.0);

        float option = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        
        if (option > 0.5f)
        {
            Cosmos::ArtGallery_3d::Create(pobj, false);
        }
        else {
            Cosmos::ArtGallery_3d::Create(pobj, true);
        }

        
        


        
	}
}