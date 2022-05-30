#include "Operations_3d.h"

// glm
#include <glm/gtc/constants.hpp>

// std
#include <functional>
#include <vector>

#include "Data_Types.h"

namespace Cosmos::Operations_3d
{
	void vertices_randomize_positions(Mesh data, const float rnd_ammout)
	{
		for (auto& v : data->vertices)
		{
			float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			v.position += glm::vec3{ x * rnd_ammout, y * rnd_ammout, z * rnd_ammout };
		}
	}

	void add_quad_every_vertex_color(
		Mesh data,
		const glm::vec3& p0,
		const glm::vec3& p1,
		const glm::vec3& p2,
		const glm::vec3& p3,
		const glm::vec3& color_0,
		const glm::vec3& color_1,
		const glm::vec3& color_2,
		const glm::vec3& color_3)
	{
		uint32_t start_pos_indices = data->indices.size();
		uint32_t start_pos_vertex = data->vertices.size();

		glm::vec3 A = p1 - p0;
		glm::vec3 B = p2 - p0;

		const glm::vec3 normal = -glm::vec3(
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x
		);




		{
			Cosmos::Data_Types::Vert v;
			v.position = p0;
			v.color = color_0;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p1;
			v.color = color_1;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p2;
			v.color = color_2;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p3;
			v.color = color_3;
			v.normal = normal;
			data->vertices.push_back(v);
		}



		data->indices.push_back(start_pos_vertex);
		data->indices.push_back(start_pos_vertex + 1);
		data->indices.push_back(start_pos_vertex + 2);

		data->indices.push_back(start_pos_vertex + 2);
		data->indices.push_back(start_pos_vertex + 3);
		data->indices.push_back(start_pos_vertex + 0);
	}

	void add_quad(
		Mesh data,
		const glm::vec3& p0,
		const glm::vec3& p1,
		const glm::vec3& p2,
		const glm::vec3& p3,
		const glm::vec3& color)
	{
		uint32_t start_pos_indices = data->indices.size();
		uint32_t start_pos_vertex = data->vertices.size();

		glm::vec3 A = p1 - p0;
		glm::vec3 B = p2 - p0;

		const glm::vec3 normal = -glm::vec3(
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x
		);




		{
			Cosmos::Data_Types::Vert v;
			v.position = p0;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p1;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p2;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Cosmos::Data_Types::Vert v;
			v.position = p3;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}



		data->indices.push_back(start_pos_vertex);
		data->indices.push_back(start_pos_vertex + 1);
		data->indices.push_back(start_pos_vertex + 2);

		data->indices.push_back(start_pos_vertex + 2);
		data->indices.push_back(start_pos_vertex + 3);
		data->indices.push_back(start_pos_vertex + 0);		

	}

	void add_quad_rnd_color(Mesh data, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		//srand(time(NULL));
		glm::vec3 color = glm::vec3(rand() / static_cast<float>(RAND_MAX),
			rand() / static_cast<float>(RAND_MAX),
			rand() / static_cast<float>(RAND_MAX));

		add_quad(data, v0, v1, v2, v3, color);
	}

	void add_circular(Mesh data,
		const int sections,
		const float radius_max,
		const float radius_min,
		const float hight,
		const glm::vec3& color_1,
		const glm::vec3& color_2,
		const glm::vec3& color_3,
		const glm::vec3& color_4)
	{
		const float angle_per_section = glm::two_pi<float>() / (float)sections;

		for (int i = 0; i < sections; i++)
		{
			float t1 = angle_per_section * i;
			float t2 = angle_per_section * (i + 1);

			float x0 = radius_min * glm::sin(t1);
			float y0 = radius_min * glm::cos(t1);

			float x1 = radius_max * glm::sin(t1);
			float y1 = radius_max * glm::cos(t1);

			float x2 = radius_max * glm::sin(t2);
			float y2 = radius_max * glm::cos(t2);

			float x3 = radius_min * glm::sin(t2);
			float y3 = radius_min * glm::cos(t2);


			glm::vec3 v0 = glm::vec3(x0, y0, 0.0f);
			glm::vec3 v1 = glm::vec3(x1, y1, 0.0f);
			glm::vec3 v2 = glm::vec3(x2, y2, 0.0f);
			glm::vec3 v3 = glm::vec3(x3, y3, 0.0f);
			add_quad(data, v0, v1, v2, v3, color_1);

			glm::vec3 v0_top = glm::vec3(x0, y0, hight);
			glm::vec3 v1_top = glm::vec3(x1, y1, hight);
			glm::vec3 v2_top = glm::vec3(x2, y2, hight);
			glm::vec3 v3_top = glm::vec3(x3, y3, hight);
			add_quad(data, v0_top, v1_top, v2_top, v3_top, color_2);

			glm::vec3 v0_side_external = glm::vec3(x2, y2, hight);
			glm::vec3 v1_side_external = glm::vec3(x1, y1, hight);

			glm::vec3 v2_side_external = glm::vec3(x1, y1, 0);
			glm::vec3 v3_side_external = glm::vec3(x2, y2, 0);
			add_quad(data, v0_side_external, v1_side_external, v2_side_external, v3_side_external, color_3);


			glm::vec3 v0_side_internal = glm::vec3(x0, y0, hight);
			glm::vec3 v1_side_internal = glm::vec3(x3, y3, hight);

			glm::vec3 v2_side_internal = glm::vec3(x3, y3, 0);
			glm::vec3 v3_side_internal = glm::vec3(x0, y0, 0);
			add_quad(data, v0_side_internal, v1_side_internal, v2_side_internal, v3_side_internal, color_4);

		}

	}

	//TODO make the same interface, but it's more efficienet than this one
	//than write a test that will give you confidence that the functions produce same results
	//you look at Data data.
	void add_double_layer_grid(
		Mesh data,
		const int size_x,
		const int size_y,
		const std::function<void(const glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)>& f_disp)
	{
		// ring one (internal / exterial )
		glm::vec3 a_v0;
		glm::vec3 a_v1;
		glm::vec3 a_v2;
		glm::vec3 a_v3;

		glm::vec3 a_v0_color;
		glm::vec3 a_v1_color;
		glm::vec3 a_v2_color;
		glm::vec3 a_v3_color;

		// ring two ( internal / exterial)
		glm::vec3 b_v0;
		glm::vec3 b_v1;
		glm::vec3 b_v2;
		glm::vec3 b_v3;

		glm::vec3 b_v0_color;
		glm::vec3 b_v1_color;
		glm::vec3 b_v2_color;
		glm::vec3 b_v3_color;

		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				if (x == 0)
				{
					f_disp(glm::vec3(0.0f, 0.0f, 0.0f + y), a_v0, a_v0_color, b_v0, b_v0_color);
					f_disp(glm::vec3(0.0f, 0.0f, 1.0f + y), a_v1, a_v1_color, b_v1, b_v1_color);
					f_disp(glm::vec3(1.0f, 0.0f, 1.0f + y), a_v2, a_v2_color, b_v2, b_v2_color);
					f_disp(glm::vec3(1.0f, 0.0f, 0.0f + y), a_v3, a_v3_color, b_v3, b_v3_color);
				}
				else
				{
					a_v0 = a_v3;
					a_v1 = a_v2;
					a_v0_color = a_v3_color;
					a_v1_color = a_v2_color;

					b_v0 = b_v3;
					b_v1 = b_v2;
					b_v0_color = b_v3_color;
					b_v1_color = b_v2_color;


					f_disp(glm::vec3(1.0f + x, 0.0f, 1.0f + y), a_v2, a_v2_color, b_v2, b_v2_color);
					f_disp(glm::vec3(1.0f + x, 0.0f, 0.0f + y), a_v3, a_v3_color, b_v3, b_v3_color);
				}


				add_quad_every_vertex_color(data,
					a_v0, a_v1, a_v2, a_v3,
					a_v0_color, a_v1_color, a_v2_color, a_v3_color
				);
				add_quad_every_vertex_color(data,
					b_v0, b_v1, b_v2, b_v3,
					b_v0_color, b_v1_color, b_v2_color, b_v3_color
				);

			}
		}
	}

	

	void ring_000(
		Mesh data,
		int num_x,
		int num_y,
		const Cosmos::Data_Types::Info::Ring_Info_000& ring_info)
	{
		

		const float x_proc = 1.0f / (float)num_x;
		const float y_proc = 1.0f / (float)num_y;

		auto lambda = [x_proc, y_proc, &ring_info](glm::vec3 v, glm::vec3& v1_out, glm::vec3& v1_out_color, glm::vec3& v2_v_out, glm::vec3& v2_out_color) {



			v.x *= x_proc;// * 5.0;
			v.z *= y_proc;// * 5.0;

			const float angle = v.x * glm::two_pi<float>();
			const float length = v.z;

			// v1
			{
				float amp_modul_a = ring_info.radius_a;
				
				float amp_a_0 = 0.0f;
				for (int i = 0; i < ring_info.sinus_signals_angleAttribute_a_radius.size(); i++)
				{
					amp_a_0 += ring_info.sinus_signals_angleAttribute_a_radius[i].amplitude *
						sin(ring_info.sinus_signals_angleAttribute_a_radius[i].offset +
							ring_info.sinus_signals_angleAttribute_a_radius[i].frequency *
							angle);
				}

				float amp_a_1 = 0.0f;
				for (int i = 0; i < ring_info.sinus_signals_lengthAttribute_a_radius.size(); i++)
				{
					amp_a_1 +=
						ring_info.sinus_signals_lengthAttribute_a_radius[i].amplitude *
						sin(ring_info.sinus_signals_lengthAttribute_a_radius[i].offset + 
							ring_info.sinus_signals_lengthAttribute_a_radius[i].frequency *
							length);
				}
				amp_modul_a += amp_a_0 + amp_a_1;
				//radius, amp1, amp2, angle, length
				v1_out_color = ring_info.f_color_a(ring_info.radius_a, amp_a_0, amp_a_1, angle, length);

				float lerp_fak = 1 - (abs(length - 0.5f) * 2);
				lerp_fak = pow(lerp_fak, ring_info.interpolation_exponent_a);

				amp_modul_a = std::lerp(ring_info.radius_merge, amp_modul_a, lerp_fak);



				v1_out.x = amp_modul_a * glm::sin(angle);
				v1_out.y = amp_modul_a * glm::cos(angle);
				v1_out.z = length * 10;




				
			}

			//v2
			{
				float amp_modul_b = ring_info.radius_b;

				float amp_b_0 = 0.0f;
				for (int i = 0; i < ring_info.sinus_signals_angleAttribute_b_radius.size(); i++)
				{
					amp_b_0 += ring_info.sinus_signals_angleAttribute_b_radius[i].amplitude *
						sin(ring_info.sinus_signals_angleAttribute_b_radius[i].offset +
							ring_info.sinus_signals_angleAttribute_b_radius[i].frequency *
							angle);
				}

				float amp_b_1 = 0;
				for (int i = 0; i < ring_info.sinus_signals_lengthAttribute_b_radius.size(); i++)
				{
					amp_b_1 += ring_info.sinus_signals_lengthAttribute_b_radius[i].amplitude *
						sin(ring_info.sinus_signals_lengthAttribute_b_radius[i].offset +
							ring_info.sinus_signals_lengthAttribute_b_radius[i].frequency *
							length);
				}

				amp_modul_b += amp_b_0 + amp_b_1;

				v2_out_color = ring_info.f_color_b(ring_info.radius_b, amp_b_0, amp_b_1, angle, length);

				float lerp_fak = 1 - (abs(length - 0.5f) * 2);
				lerp_fak = pow(lerp_fak, ring_info.interpolation_exponent_b);

				amp_modul_b = std::lerp(ring_info.radius_merge, amp_modul_b, lerp_fak);



				v2_v_out.x = amp_modul_b * glm::sin(angle);
				v2_v_out.y = amp_modul_b * glm::cos(angle);
				v2_v_out.z = length * 10;

			}

			


			
		};

		add_double_layer_grid(data, num_x, num_y, lambda);

		
		//2x
		//{Signal
		//vector<{frequeny amplitude offset}> //Probably should be in datatypes

		//2x
		//vector<{frequeny amplitude offset}> //Probably should be in datatypes //for colors

		//2x 
		//exponent dumping

		//convergence radius value

		//1x
		//length multiplier
	}


	void ring_001(Mesh data, const Cosmos::Data_Types::Info::Ring_Info_001& ring_info)
	{
		const float x_proc = 1.0f / (float)ring_info.num_x;
		const float y_proc = 1.0f / (float)ring_info.num_y;

		auto lambda = [x_proc, y_proc, &ring_info](glm::vec3 v, glm::vec3& v1_out, glm::vec3& v1_out_color, glm::vec3& v2_v_out, glm::vec3& v2_out_color) {
			v.x *= x_proc;
			v.z *= y_proc;

			const float angle = v.x * glm::two_pi<float>();
			const float length = v.z;

			{
				Data_Types::Info::Ring_Info_001_f_Result result;

				ring_info.f(angle, length, result);

				
				{
					float ra = ring_info.radius_a + result.radius_offset_a;

					//a
					float lerp_fak_a = 1 - (abs(length - 0.5f) * 2);
					lerp_fak_a = pow(lerp_fak_a, ring_info.interpolation_exponent_a);

					ra = std::lerp(ring_info.radius_merge, ra, lerp_fak_a);

					v1_out.x = ra * glm::sin(angle);
					v1_out.y = ra * glm::cos(angle);
					v1_out.z = length * ring_info.length_multiplier;

				}
				
				//b

				{
					float rb = ring_info.radius_b + result.radius_offset_b;
					float lerp_fak_b = 1 - (abs(length - 0.5f) * 2);
					lerp_fak_b = pow(lerp_fak_b, ring_info.interpolation_exponent_b);

					rb = std::lerp(ring_info.radius_merge, rb, lerp_fak_b);

					v2_v_out.x = rb * glm::sin(angle);
					v2_v_out.y = rb * glm::cos(angle);
					v2_v_out.z = length * ring_info.length_multiplier;
				}
				
				v1_out_color = glm::vec3(result.color_a_r, result.color_a_g, result.color_a_b);
				v2_out_color = glm::vec3(result.color_b_r, result.color_b_g, result.color_b_b);

				int a = 10;
			}

		};
		

		add_double_layer_grid(data, ring_info.num_x, ring_info.num_y, lambda);
	}


}
