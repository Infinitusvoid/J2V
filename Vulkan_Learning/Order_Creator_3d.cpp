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
        pobj->position = pos;
        pobj->scale = scale;
        pobj->rotation = rot;

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