#ifndef MAP
#define MAP
#include "Tile.h"
#include <fstream>
#include <sstream>
#include <iostream>
class Map
{
public:
	Map();
	~Map();
	void initialise(std::string layerOneFileName, std::string layerTwoFileName, std::string layerThreeFileName, std::string layerFourFileName, sf::Texture *texture);
	void loadFromFile(std::string fileName);
	void createLayer(std::string layerOne, sf::Texture *texture);
	void createTrackLayer(std::string layerOne, sf::Texture *texture);
	void createObstacleLayer(std::string layerOne, sf::Texture *texture);
	void draw(sf::RenderWindow* window, sf::Vector2f playerPos, bool minimap);
	std::vector< std::vector<Tile> > m_trackLayer;
	std::vector< std::vector<Tile> > m_obstacleLayer;

private:
	sf::Vector2f assignBlocks(int i);
	std::vector< std::vector<Tile> > m_mapLayerOne;
	std::vector< std::vector<int> > m_csvLoadedMap;
};
#endif // !MAP



