#include "Elements_3d.h"

#include "Operations_3d.h"



namespace Cosmos::Elements_3d
{
	
	void CreateRing(const Cosmos::Data_Types::Info::Ring_Info_000& ring_info, Cosmos::Data_Types::Object3d_Data* pobj)
	{
		//Cosmos::Operations_3d::AddRing(pobj, ring_info.num_x, ring_info.num_y); //here is one but the could be multiple calls to different things

		Cosmos::Operations_3d::ring_002(pobj, ring_info.num_x, ring_info.num_y, ring_info);
	}
}