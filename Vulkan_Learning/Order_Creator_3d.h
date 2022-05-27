#pragma once

#include "Data_Types.h"

/// <summary>
/// Set the order, with generated the parameters, to an ArtGallery
/// </summary>
//
namespace Cosmos::Order_Creator_3d
{
    void Create(
        Cosmos::Data_Types::Object3d_Data* pobj,
        const glm::vec3 pos,
        const glm::vec3 rot,
        const glm::vec3 scale);
	
}
