#include "Map.h"
#include "Screen.h"
#include "Player.h"
#include "Enemy.h"
#include <math.h>
#include <SFML\Graphics.hpp>
#ifndef PLAY
#define PLAY
class Play : public Screen
{
public:

	Play(sf::RenderWindow *window, GameState *state);

	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
	void HandleCollision();
	void updateEnemies(sf::Time dt);
	void generateWave(int randEnemy);

	void reset();

	//Map demoMap;
	//sf::Texture mapTexture;
	Player player;

	sf::View view;
	sf::View playerView;

	sf::Sprite m_ramEnemySprite;
	sf::Sprite m_shipEnemySprite;

	sf::Texture m_ramEnemyTexture;
	sf::Texture m_shipEnemyTexture;

	sf::RenderWindow *m_window;

	sf::Keyboard keyboard;
	sf::Keyboard pastKeyboard;

	sf::SoundBuffer shootingNoise;
	sf::Sound shootSound;

	sf::SoundBuffer enemyShootingNoise;
	sf::Sound enemyShootSound;
	//Merchant merchant;

	float distBetween(sf::Vector2f playerPos, sf::Vector2f OtherPos);

	int enemyCount;
	int deadEnemies;
	int enemyOffset;
	int bossSpawnCount;
	float enemySpeed;
	bool bossWave;

	void handleEvent(sf::Event e);

	std::vector<Enemy*> enemyArray;
	/*std::vector<Enemy*> largeSinWaveEnemies;
	std::vector<Enemy*> goToCenterEnemies;
	std::vector<Enemy*> leftToRightEnemies;
	std::vector<Enemy*> rightToLeftEnemies;*/
	Enemy trackerEnemyType;




	//ENEMY TEXTURES
	sf::Texture enemyOneTexture;
	sf::Texture enemyTwoTexture;
	sf::Texture enemyThreeTexture;
	sf::Texture enemyFourTexture;
	sf::Texture enemyFiveTexture;
	sf::Texture enemySixTexture;
	//Enemy Sprites!
	sf::Sprite enemyOneSprite;
	sf::Sprite enemyTwoSprite;
	sf::Sprite enemyThreeSprite;
	sf::Sprite enemyFourSprite;
	sf::Sprite enemyFiveSprite;
	sf::Sprite enemySixSprite;
};
#endif // !PLAY

