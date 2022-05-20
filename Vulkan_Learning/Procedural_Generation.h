#pragma once

#include "lve_game_object.h"

#include <glm/glm.hpp>
#include <vector>

#include <math.h>       /* sin */

#include "Data_Types.h"

namespace Proc
{
	class Procedural_Generation
	{
	public:
		Procedural_Generation();
		~Procedural_Generation();

		Cosmos::Data_Types::VectorOfPointers_PointingTo_Procedural_ObjectData data;
	};
}
