#include "Procedural_Ring.h"

namespace Cosmos
{
	/*
	void Procedural_Ring::init_example_0()
	{
		num_radial_slices = 500;
		num_length_slices = 500;
		f_init = []() {};
		f_update = [](int l, int r) {};
		f_radius_External = Procedural_Ring::m_example_0_external;
		f_radius_Internal = Procedural_Ring::m_example_0_internal;
		f_disp_l = [](float l) { return l * 5.0f; };
		f_disp_r = Procedural_Ring::identitiy;
	}
	*/

	void Procedural_Ring::build(const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad)
	{
		float length_slice = 1.0f / (float)num_length_slices;
		float length_slice_radial = 1.0f / (float)num_radial_slices;
		f_init(); //TODO use init to calculate staff 

		for (int l_index = 0; l_index < num_length_slices; l_index++)
		{
			for (int r_index = 0; r_index < num_radial_slices; r_index++)
			{
				//TODO d1 should become d0 in next iteration of loop to avoid unecessery calulations

				float d0 = f_disp_l(l_index * length_slice);
				float d1 = f_disp_l((l_index + 1) * length_slice);

				float t0 = glm::two_pi<float>() * f_disp_r(length_slice_radial * r_index);
				float t1 = glm::two_pi<float>() * f_disp_r(length_slice_radial * (r_index + 1));

				float x0 = glm::sin(t0);
				float y0 = glm::cos(t0);

				float x1 = glm::sin(t1);
				float y1 = glm::cos(t1);

				f_update(l_index, r_index); //TODO udate to calculate above staff

				f_active_external();
				m_draw(r_index, l_index, x0, y0, x1, y1, d0, d1, f_addQuad, f_radius_External);
				f_active_iternal();
				m_draw(r_index, l_index, x0, y0, x1, y1, d0, d1, f_addQuad, f_radius_Internal);
			}
		}

	}


	void Procedural_Ring::m_draw(
		const int r_index,
		const int l_index,
		const float x0,
		const float y0,
		const float x1,
		const float y1,
		const float d0,
		const float d1,
		std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad,
		std::function<float(int, int)> f_radius
	)
	{

		const float offset_0_0 = f_radius(r_index, l_index);//Radius_External(r_index, l_index);
		const float offset_0_1 = f_radius(r_index, l_index + 1);
		const float offset_1_0 = f_radius(r_index + 1, l_index);
		const float offset_1_1 = f_radius(r_index + 1, l_index + 1);

		float x0_d0 = x0 * offset_0_0;
		float x0_d1 = x0 * offset_0_1;

		float y0_d0 = y0 * offset_0_0;
		float y0_d1 = y0 * offset_0_1;

		float x1_d0 = x1 * offset_1_0;
		float x1_d1 = x1 * offset_1_1;

		float y1_d0 = y1 * offset_1_0;
		float y1_d1 = y1 * offset_1_1;

		glm::vec3 v0(x0_d0, y0_d0, d0);
		glm::vec3 v1(x0_d1, y0_d1, d1);
		glm::vec3 v2(x1_d1, y1_d1, d1);
		glm::vec3 v3(x1_d0, y1_d0, d0);

		f_addQuad(v0, v1, v2, v3);
	}
	
	/*
	float Procedural_Ring::m_example_0_external(int r, int l)
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
	*/
	
	/*
	float Procedural_Ring::m_example_0_internal(int r, int l)
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
	*/

}



