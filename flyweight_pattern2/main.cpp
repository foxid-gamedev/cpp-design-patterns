// not really a flyweight pattern
// got improved in flyweight_pattern3
#include <iostream>
#include <array>

#include <cstdlib>
#include <ctime>
#include <algorithm>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
enum class Terrain
{
	grass = 0,
	hill,
	river,

	maximum
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class World
{
public:
	static constexpr uint16_t width = 4;
	static constexpr uint16_t height = 4;
	using Tiles = std::array<std::array<Terrain, width>, height>;

	explicit World() : m_tiles(Tiles()) {}

	// bad practice to calculate every data cell
	uint16_t getMovementCost(uint16_t x, uint16_t y) const
	{
		switch (m_tiles[y][x])
		{
		case Terrain::grass: return 1;
		case Terrain::hill: return 3; 
		case Terrain::river: return 2;
		default: return 0;
		}
	}

	bool isWater(uint16_t x, uint16_t y) const
	{
		switch (m_tiles[y][x])
		{
		case Terrain::grass: return false;
		case Terrain::hill: return false;
		case Terrain::river: return true;
		default: return false;
		}
	}

	Tiles m_tiles;
};

auto main() -> int
{
	World world{};

	srand(time(nullptr));

	std::cout << "world data: " << std::endl << std::endl;

	for (auto& rows : world.m_tiles)
	{
		for (auto& tile : rows)
		{
			tile = static_cast<Terrain>(rand() % (static_cast<uint16_t>(Terrain::maximum)));
			std::cout << static_cast<uint16_t>(tile);
		}
		std::cout << std::endl;
	}

	std::cout << "\nworld costs: " << std::endl << std::endl;

	for (uint16_t y = 0; y < World::height; y++)
	{
		for (uint16_t x = 0; x < World::width; x++)
		{
			std::cout << world.getMovementCost(x, y);
		}
		std::cout << std::endl;
	}

	std::cout << "\nworld isWater: " << std::endl << std::endl;

	for (uint16_t y = 0; y < World::height; y++)
	{
		for (uint16_t x = 0; x < World::width; x++)
		{
			std::cout << world.isWater(x, y);
		}
		std::cout << std::endl;
	}


}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//