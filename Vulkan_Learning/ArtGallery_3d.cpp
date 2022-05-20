#include "ArtGallery_3d.h"

//#include "Operations_3d.h";
#include "Elements_3d.h"

namespace Cosmos::ArtGallery_3d
{
	void Create(Cosmos::Data_Types::Object3d_Data* pobj)
	{
		//Cosmos::Operations_3d::AddRing(pobj);
		Cosmos::Data_Types::Info::Ring_Info ring_info{};

		ring_info.radius_a = 5;
		ring_info.radius_b = 8;
		
		ring_info.radius_merge = 3.0f;

		ring_info.num_x = 100;
		ring_info.num_y = 100;
		
		ring_info.sinus_signals_a.push_back({ 2.0f, 0.1f, 0.3f }); //Frequency, Amplitude, Offset
		ring_info.sinus_signals_a.push_back({ 3.0f, 0.4f, 0.0f });
		ring_info.sinus_signals_a.push_back({ 15.0f, 0.2f, 0.0f });

		ring_info.sinus_signals_b.push_back({ 2.0f, 0.1f, 0.3f }); //Frequency, Amplitude, Offset
		ring_info.sinus_signals_b.push_back({ 3.0f, 0.4f, 0.0f });
		ring_info.sinus_signals_b.push_back({ 15.0f, 0.2f, 0.0f });

		ring_info.interpolation_exponent_a = 2.0f;
		ring_info.interpolation_exponent_b = 2.0f;

		Cosmos::Elements_3d::CreateRing(ring_info, pobj);
	}
}