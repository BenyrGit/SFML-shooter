#include "DataTables.hpp"
#include "Aircraft.hpp"

std::array<AircraftData, static_cast<std::size_t>(Aircraft::Type::TypeCount)> initializeAircraftData()
{
	std::array<AircraftData, static_cast<std::size_t>(Aircraft::Type::TypeCount)> data{};

	data[static_cast<std::size_t>(Aircraft::Type::Eagle)] =
	{
		100,
		300.f,
		Textures::ID::Eagle
	};

	data[static_cast<std::size_t>(Aircraft::Type::Raptor)] =
	{
		20,
		120.f,
		Textures::ID::Raptor
	};

	return data;
}
