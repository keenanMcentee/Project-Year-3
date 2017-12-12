#include "Map.h"

Map::Map()
{
}


Map::~Map()
{
}
/// <summary>
/// Handles creating the entire map.
/// </summary>
void Map::initialise(std::string layerOneFileName, std::string layerTwoFileName, std::string layerThreeFileName, std::string layerFourFileName, sf::Texture *texture)
{
	m_groundLayer.clear();
	m_obstacleLayer.clear();
	m_interactionLayer.clear();
	m_csvLoadedMap.clear();
	if (layerOneFileName != "")
		createLayer(layerOneFileName, texture);
	if (layerTwoFileName != "")
		createObstacleLayer(layerTwoFileName, texture);
	if (layerThreeFileName != "")
		createInteractiveLayer(layerThreeFileName, texture);
	if (layerFourFileName != "")
		createObstacleLayer(layerFourFileName, texture);
}
/// <summary>
/// Handles loading the map data from a file.
/// </summary>
void Map::loadFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) { std::cout << "NOT OPENED" << std::endl; }
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		if (!file.good())
			break;
		
		std::stringstream iss(line);
		std::vector<int> a;
		for (int col = 0; col < line.length(); ++col)
		{
			std::string val;
			std::getline(iss, val, ',');
			if (!iss.good())
				break;
			int value;
			std::stringstream convertor(val);
			convertor >> value;
			a.push_back(value);
		}
		m_csvLoadedMap.push_back(a);
	}
}
/// <summary>
/// Handles creating first layer of the map.
/// </summary>
void Map::createLayer(std::string layer, sf::Texture *texture)
{
	loadFromFile(layer);
	for (int row = 0; row < m_csvLoadedMap.size(); row++)
	{
		std::vector<Tile> a;
		for (int col = 0; col < m_csvLoadedMap[row].size(); col++)
		{
			if (m_csvLoadedMap[row][col] != -1)
			{
			sf::Vector2f texturepos = assignBlocks(m_csvLoadedMap[row][col]);
			a.push_back(Tile(texture, sf::IntRect(texturepos.x, texturepos.y, 64, 64), sf::Vector2f(col * 64, row * 64)));
		}
		}
		m_groundLayer.push_back(a);
	}
	m_csvLoadedMap.clear();
}
/// <summary>
/// Handles creating the layer of roads from the map.
/// </summary>
void Map::createObstacleLayer(std::string layerTwo, sf::Texture *texture)
{
	loadFromFile(layerTwo);
	for (int row = 0; row < m_csvLoadedMap.size(); row++)
	{
		std::vector<Tile> a;
		for (int col = 0; col < m_csvLoadedMap[row].size(); col++)
		{
			if (m_csvLoadedMap[row][col] != -1)
			{
				sf::Vector2f texturepos = assignBlocks(m_csvLoadedMap[row][col]);
				a.push_back(Tile(texture, sf::IntRect(texturepos.x, texturepos.y, 64, 64), sf::Vector2f(col * 64, row * 64)));
			}
		}
		m_obstacleLayer.push_back(a);
	}
	m_csvLoadedMap.clear();
}
/// <summary>
/// Handles creating the obstacle layer for our map.
/// </summary>
void Map::createInteractiveLayer(std::string layerObstacle, sf::Texture *texture)
{
	loadFromFile(layerObstacle);
	for (int row = 0; row < m_csvLoadedMap.size(); row++)
	{
		std::vector<Tile> a;
		for (int col = 0; col < m_csvLoadedMap[row].size(); col++)
		{
			if (m_csvLoadedMap[row][col] != -1)
			{
				sf::Vector2f texturepos = assignBlocks(m_csvLoadedMap[row][col]);
				a.push_back(Tile(texture, sf::IntRect(texturepos.x, texturepos.y, 64, 64), sf::Vector2f(col * 64, row * 64)));
			}
		}
		m_interactionLayer.push_back(a);
	}
	m_csvLoadedMap.clear();
}

void Map::draw(sf::RenderWindow *window, sf::Vector2f playerPos, bool minimap)
{
	int tilesDrawing = 0;
	for (int i = 0; i < m_groundLayer.size(); i++)
	{
		for (int j = 0; j < m_groundLayer[i].size(); j++)
		{
			if (!minimap)
			{
				tgui::FloatRect viewRect = tgui::FloatRect(playerPos.x - 800, playerPos.y - 800, 1600, 1600);

				if (
					m_groundLayer[i][j].m_sprite.getGlobalBounds().intersects(viewRect))
				{
					
					tilesDrawing++;
				}
				m_groundLayer[i][j].draw(window);
			}
			else
			{
				m_groundLayer[i][j].draw(window);
			}
		}
	}
	for (int i = 0; i < m_obstacleLayer.size(); i++)
	{
		for (int j = 0; j < m_obstacleLayer[i].size(); j++)
		{
			if (!minimap)
			{
				tgui::FloatRect viewRect = tgui::FloatRect(playerPos.x - 650, playerPos.y - 650, 1300, 1300);

				if (
					m_obstacleLayer[i][j].m_sprite.getGlobalBounds().intersects(viewRect))
				{
					m_obstacleLayer[i][j].draw(window);
					tilesDrawing++;
				}
			}
			else
			{
				m_obstacleLayer[i][j].draw(window);
			}
		}
	}
	for (int i = 0; i < m_interactionLayer.size(); i++)
	{
		for (int j = 0; j < m_interactionLayer[i].size(); j++)
		{
			if (!minimap)
			{
				tgui::FloatRect viewRect = tgui::FloatRect(playerPos.x - 650, playerPos.y - 650, 1300, 1300);

				if (
					m_interactionLayer[i][j].m_sprite.getGlobalBounds().intersects(viewRect))
				{
					m_interactionLayer[i][j].draw(window);
					tilesDrawing++;
				}
			}
			else
			{
				m_interactionLayer[i][j].draw(window);
			}
		}
	}
}

/// <summary>
/// Handles assigning the texture coordinate to each value in the tilemap.
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
sf::Vector2f Map::assignBlocks(int i)
{
	sf::Vector2f texCoord;
	if (i == 0)
	{
		texCoord = sf::Vector2f(0, 0);
	}
	else
	{
		int testX = (i - ((i / 9) * 10)) * 64;
		int testY = (i  / 10) * 64;
		texCoord = sf::Vector2f(testX, testY);
	}
	return texCoord;
}