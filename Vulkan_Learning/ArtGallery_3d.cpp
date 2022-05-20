#include "ArtGallery_3d.h"

//#include "Operations_3d.h";
#include "Elements_3d.h"

namespace Cosmos::ArtGallery_3d
{
	void Create(Cosmos::Data_Types::Object3d_Data* pobj)
	{
		//Cosmos::Operations_3d::AddRing(pobj);
		Cosmos::Data_Types::Info::Ring_Info ring_info{};


		
		ring_info.radius_merge = 6.0f;

		ring_info.num_x = 500;
		ring_info.num_y = 500;
		
		//a
		ring_info.radius_a = 3;

		ring_info.sinus_signals_angleAttribute_a_radius.push_back({ 2.0f, 0.1f, 0.3f }); //Frequency, Amplitude, Offset
		ring_info.sinus_signals_angleAttribute_a_radius.push_back({ 3.0f, 0.4f, 0.0f });
		ring_info.sinus_signals_angleAttribute_a_radius.push_back({ 15.0f, 0.2f, 0.0f });

		ring_info.interpolation_exponent_a = 2.0f;

		ring_info.sinus_signals_lengthAttribute_a_radius.push_back({ 120.0f, 0.2f, 0.0f });
		ring_info.sinus_signals_lengthAttribute_a_radius.push_back({ 125.0f, 0.125f, 0.0f });

		//b
		ring_info.radius_b = 8;

		ring_info.sinus_signals_angleAttribute_b_radius.push_back({ 2.0f, 0.1f, 0.3f }); //Frequency, Amplitude, Offset
		ring_info.sinus_signals_angleAttribute_b_radius.push_back({ 3.0f, 0.4f, 0.0f });
		ring_info.sinus_signals_angleAttribute_b_radius.push_back({ 15.0f, 0.2f, 0.0f });

		ring_info.sinus_signals_lengthAttribute_b_radius.push_back({ 20.0f, 0.5f, 0.0f});
		ring_info.sinus_signals_lengthAttribute_b_radius.push_back({ 25.0f, 0.25f, 0.0f });

		ring_info.interpolation_exponent_b = 2.0f;

		//radius, amp1, amp2, angle, length
		//std::function<glm::vec3(float, float, float, float)> f_color_a;
		//std::function<glm::vec3(float, float, float, float)> f_color_b;
		ring_info.f_color_a = [](float radius, float amp1, float amp2, float angle, float length) {
			//return glm::vec3(0.01f, 0.8f, 0.3f);
			return glm::vec3(0.2, 0.8 + 0.3 * glm::sin(length * 100 + 0.1f * sin(angle * 100)), 0.1f);
		};
		//v1_out_color = glm::vec3(0.2, 0.8 + 0.3 * glm::sin(length * 100 + 0.1f * sin(angle * 100)), 0.1f);

		ring_info.f_color_b = [](float radius, float amp1, float amp2, float angle, float length) {
			//return glm::vec3(0.01f, 0.8f, 0.3f);
			return glm::vec3(0.2, 0.8 + 0.3 * glm::sin(length * 100 + 0.1f * sin(angle * 100)), 0.4f);
		};
		//glm::vec3(0.2, 0.8 + 0.3 * glm::sin(length * 100 + 0.1f * sin(angle * 100)), 0.1f);

		Cosmos::Elements_3d::CreateRing(ring_info, pobj);
	}
}