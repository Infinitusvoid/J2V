#include "Elements_3d.h"

#include "Operations_3d.h"



namespace Cosmos::Elements_3d
{
	
	void CreateRing(const Cosmos::Data_Types::Info::Ring_Info_000& ring_info, Cosmos::Data_Types::Object3d_Data* pobj)
	{
		Cosmos::Operations_3d::ring_000(pobj, ring_info.num_x, ring_info.num_y, ring_info);
	}

	void CreateRing_001(const Cosmos::Data_Types::Info::Ring_Info_001& ring_info, Cosmos::Data_Types::Object3d_Data* pobj)
	{
		Cosmos::Operations_3d::ring_001(pobj, ring_info);
	}
}