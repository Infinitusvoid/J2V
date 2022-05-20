#pragma once

#include "Data_Types.h"

namespace Cosmos::Elements_3d
{
	struct Ring_Info
	{
		int num_x;
		int num_y;
	};

	void CreateRing(const Ring_Info& ring_info, Cosmos::Data_Types::Object3d_Data* pobj);
}
