#include "Ring_Example_000.h"

namespace Cosmos
{
	void Ring_Example_000::init()
	{
		proc_ring.num_radial_slices = 500;
		proc_ring.num_length_slices = 500;
		proc_ring.f_init = []() {};
		proc_ring.f_update = [](int l, int r) {};
		proc_ring.f_radius_External = m_example_0_external;
		proc_ring.f_radius_Internal = m_example_0_internal;
		proc_ring.f_disp_l = [](float l) { return l * 5.0f; };
		proc_ring.f_disp_r = Procedural_Ring::identitiy;
	}

	float Ring_Example_000::m_example_0_external(int r, int l)
	{
		float r_angle = (r / (float)500) * glm::two_pi<float>();
		float l_fak = (l / (float)500);

		float this_offst = 1.5f +
			0.25f * glm::sin(r_angle * 10) +
			0.1f * glm::sin(l_fak * glm::two_pi<float>() * 20.0f);
		0.0025f * glm::sin(l_fak * glm::two_pi<float>() * 105.0f);

		float lerp_fak = 1 - (abs(l_fak - 0.5f) * 2);
		lerp_fak = pow(lerp_fak, 0.8f);

		return std::lerp(0.5f, this_offst, lerp_fak);
	}

	float Ring_Example_000::m_example_0_internal(int r, int l)
	{
		float r_angle = (r / (float)500) * glm::two_pi<float>();
		float l_fak = (l / (float)500);

		float this_offst = 0.7f +
			0.025 * glm::sin(r_angle * 25) +
			0.025 * glm::sin(l_fak * glm::two_pi<float>() * 8);

		float lerp_fak = 1 - (abs(l_fak - 0.5f) * 2);
		lerp_fak = pow(lerp_fak, 0.4f);

		float val = std::lerp(0.5f, this_offst, lerp_fak);
		return std::min(m_example_0_external(r, l), val);
	}

	void Ring_Example_000::build(const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad)
	{
		
		
	}

}
