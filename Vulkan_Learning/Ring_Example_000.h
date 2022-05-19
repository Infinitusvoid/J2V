#pragma once

//#include "Procedural_Ring.h"

// std
#include <iostream>
#include <functional>
#include "Procedural_Ring.h"

// libs
#include <glm/glm.hpp>

namespace Cosmos
{
	class Ring_Example_000
	{
		//TODO here we will have class that sets the parameter of class Procedural ring and implements methods, and as a result create a cool visual!

		//We don't pass a parameter the Procedural ring object but we create the object inside the .cpp class,
		//composition over inheritence

	public:
		void init();
		void build(const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad);
	private:
		Procedural_Ring proc_ring;

		static float m_example_0_external(int r, int l);
		static float m_example_0_internal(int r, int l);
	};

}


