#include "Procedural_Ring.h"

namespace Cosmos
{
	
	void loop2d(int sy,int sx, const std::function<void(int, int)> f)
	{
		for (int y = 0; y < sy; y++)
		{
			for (int x = 0; x < sx; x++) {
				f(x, y);
			}
		}
	}


	void Procedural_Ring::build(const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad)
	{
		//--
		/*
		int length_slice = 1.0 / num_length_slices;
		float length_slice_radial = 1.0f / (float)num_radial_slices;

		loop2d(num_length_slices, num_radial_slices, [&](int r_index, int l_index) {
			float d0 = f_disp_l(l_index * length_slice);
			float d1 = f_disp_l((l_index + 1) * length_slice);

			float t0 = glm::two_pi<float>() * f_disp_r(length_slice_radial * r_index);
			float t1 = glm::two_pi<float>() * f_disp_r(length_slice_radial * (r_index + 1));

			float x0 = glm::sin(t0);
			float y0 = glm::cos(t0);

			float x1 = glm::sin(t1);
			float y1 = glm::cos(t1);

			f_active_external();
			m_draw(r_index, l_index, x0, y0, x1, y1, d0, d1, f_addQuad, f_radius_External);


			//f_update(r_index, l_index);

			f_active_iternal();
			m_draw(r_index, l_index, x0, y0, x1, y1, d0, d1, f_addQuad, f_radius_Internal);

		});
		*/
		//--
		//return;
		
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

				//f_update(r_index, l_index); //TODO udate to calculate above staff
				// Update
				



				f_active_external();
				m_draw(r_index, l_index, x0, y0, x1, y1, d0, d1, f_addQuad, f_radius_External);


				//f_update(r_index, l_index);

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
		std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad,
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


		glm::vec3  color = f_color(r_index, l_index);//color(0.2f, 0.8f, 0.3f);

		//f_addQuad(v0, v1, v2, v3, color);
		f_addQuad(v0, v1, v2, v3, color);
	}

}



