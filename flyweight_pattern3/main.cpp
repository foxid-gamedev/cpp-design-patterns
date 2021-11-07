#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class Texture {};

// define some pseudo examples for the texture handles:
Texture GrassTexture;
Texture HillTexture;
Texture RiverTexture;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class Terrain
{
public:
	enum class Type
	{
		grass = 0,
		hill,
		river
	};

	Terrain() = default; // compiler cries when no standard constructor is defined. 
	// I don't know why thats necessary..

	explicit Terrain(Type type, uint16_t moveCost, bool isWater, Texture texture)
		: m_type(type), m_moveCost(moveCost), m_isWater(isWater), m_texture(std::move(texture)) {}

	int getMoveCost() const { return m_moveCost; }
	bool isWater() const { return m_isWater; }
	const Texture& getTexture() const { return m_texture; }
	Type getType() const { return m_type; }
private:
	Type m_type;
	uint16_t m_moveCost;
	bool m_isWater;
	Texture m_texture;
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
class World
{
public:
	static constexpr uint16_t width = 4;
	static constexpr uint16_t height = 4;

	using Tiles = std::array<std::array<Terrain*, width>, height>;

	explicit World() 
		: m_grassTerrain(Terrain(Terrain::Type::grass, 1, false, GrassTexture)),
		m_hillTerrain(Terrain(Terrain::Type::hill, 3, false, HillTexture)),
		m_riverTerrain(Terrain(Terrain::Type::river, 2, true, RiverTexture)),
		m_tiles(Tiles())
	{

	}

	void generateTerrain()
	{
		srand(time(nullptr));

		for (uint16_t y = 0; y < height; y++)
		{
			for (uint16_t x = 0; x < width; x++)
			{
				if (rand() % 101 >= 75) // check if a number between 0-100 gets at least 75 or higher
				{
					m_tiles[y][x] = &m_hillTerrain;
				}
				else
				{
					m_tiles[y][x] = &m_grassTerrain;
				}
			}
		}

		uint16_t x = rand() % width;

		for (uint16_t y = 0; y < height; y++)
		{
			m_tiles[y][x] = &m_riverTerrain;
		}
	}

	const Terrain& getTile(uint16_t x, uint16_t y) const
	{
		return *m_tiles[y][x];
	}
private:
	Terrain m_grassTerrain;
	Terrain m_hillTerrain;
	Terrain m_riverTerrain;

	Tiles m_tiles;
};

auto main() -> int
{
	World world{};

	world.generateTerrain();

	std::cout << "world data: " << std::endl << std::endl;

	for (uint16_t y = 0; y < World::height; y++)
	{
		for (uint16_t x = 0; x < World::height; x++)
		{
			std::cout << static_cast<uint16_t>(world.getTile(x, y).getType());
		}
		std::cout << std::endl;
	}


	std::cout << "\nworld costs: " << std::endl << std::endl;

	for (uint16_t y = 0; y < World::height; y++)
	{
		for (uint16_t x = 0; x < World::width; x++)
		{
			std::cout << world.getTile(x, y).getMoveCost();
		}
		std::cout << std::endl;
	}

	std::cout << "\nworld isWater: " << std::endl << std::endl;

	for (uint16_t y = 0; y < World::height; y++)
	{
		for (uint16_t x = 0; x < World::width; x++)
		{
			std::cout << world.getTile(x, y).isWater();
		}
		std::cout << std::endl;
	}
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//