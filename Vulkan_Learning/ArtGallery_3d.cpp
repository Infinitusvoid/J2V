#include "ArtGallery_3d.h"

//#include "Operations_3d.h";
#include "Elements_3d.h"

namespace Cosmos::ArtGallery_3d
{
	void Create(Cosmos::Data_Types::Object3d_Data* pobj)
	{
		//Cosmos::Operations_3d::AddRing(pobj);
		Cosmos::Elements_3d::Ring_Info ring_info{};
		ring_info.num_x = 100;
		ring_info.num_y = 100;
		
		Cosmos::Elements_3d::CreateRing(ring_info, pobj);
	}
}