#include "Play.h"

/// <summary>
/// Constructor for the play game.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Play::Play(sf::RenderWindow *window, GameState *state) : Screen(window)
{
	currentState = state;
	m_window = window;
	player.Initialise(window);
	
	enemyCount = 0;
	waveNumber = 1;

	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);

	blankTexture.loadFromFile("./ASSETS/blankTexture.png");
	backgroundSprite.setTexture(blankTexture);
	backgroundShader.loadFromFile("./ASSETS/shaders/fragmentShaders/ground_one.frag", sf::Shader::Fragment);

	m_ramEnemyTexture.loadFromFile("ASSETS/enemyBallThingie.png");
	m_ramEnemySprite.setTexture(m_ramEnemyTexture);
	m_ramEnemySprite.setScale(0.05f, 0.05f);

	m_shipEnemyTexture.loadFromFile("ASSETS/BulletShootingShip.png");
	m_shipEnemySprite.setTexture(m_shipEnemyTexture);
	m_shipEnemySprite.setScale(0.1f, 0.1f);
}

/// 
/// /// <summary>
/// updates the player and changes the gamestate to pause if the escape key is pressed
/// </summary>
void Play::Update(sf::Time dt)
{
	std::cout << player.bullets.size() << std::endl;
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	backgroundShader.setUniform("time", timeSinceStart);
	backgroundShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));

	player.Update(dt, keyboard, &playerView);
	updateEnemies(dt);
	HandleCollision();

	for (int i = 0; i < player.bullets.size(); i++)
	{
		if (player.bullets[i]->m_position.x  + player.bullets[i]->getRect().width > m_window->getSize().x || player.bullets[i]->m_position.x < 0 ||
			player.bullets[i]->m_position.y + player.bullets[i]->getRect().height > m_window->getSize().y || player.bullets[i]->m_position.y < 0)
		{
			player.bullets[i]->~Projectile();
			player.bullets[i] = nullptr;
			player.bullets.erase(player.bullets.begin() + i);
			i--;
		}
	}

	if (enemyCount < 1)
	{
		generateWave(7);
	}

	/*if (enemyCount <= 15)
	{
		int randEnemy1 = rand() % 6;
		int randEnemy2 = rand() % 6;
		if (randEnemy2 = randEnemy1)
		{
			int randEnemy2 = rand() % 5;
		}

		generateWave(randEnemy1);
		generateWave(randEnemy2);
	}*/

	currentState;
	if (keyboard.isKeyPressed(keyboard.Escape))
	{
		GoToScreen(GameState::Pause);
	}

	/*if (player.m_health <= 0)
	{
		GoToScreen(GameState::MainMenu);
	}*/

	pastKeyboard = keyboard;
}
/// <summary>
/// Function to handle drawing the player.
/// Changes the view to follow the player.
/// </summary>
/// <param name="window"></param>
void Play::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &backgroundShader);
	player.Draw();

	for (int i = 0; i < enemyArray.size(); i++)
	{
		enemyArray[i]->Draw();
	}

	trackerEnemyType.Draw();

	playerView.setCenter(player.m_position);

	//window->setView(playerView);
	//demoMap.draw(window, sf::Vector2f(0, 0), true);

	window->setView(window->getDefaultView());
}

float Play::distBetween(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}

void Play::HandleCollision()
{
	for (int i = 0; i < enemyArray.size(); i++)
	{
		if (player.getRect().intersects(enemyArray[i]->getRect()) && enemyArray[i]->alive == true)
		{
			if (!enemyArray[i]->m_type == 7)
			{
				enemyArray[i]->alive = false;
				player.m_health -= enemyArray[i]->m_damage;
			}
			else
			{
				player.m_health = 0;
			}
		}

		for (int j = 0; j < enemyArray[i]->bullets.size(); j++)
		{
			if (player.getRect().intersects(enemyArray[i]->bullets[j]->getRect()))
			{
				player.m_health -= enemyArray[i]->bullets[j]->m_damage;
				enemyArray[i]->bullets[j]->~Projectile();
				enemyArray[i]->bullets[j] = nullptr;
				enemyArray[i]->bullets.erase(enemyArray[i]->bullets.begin() + j);
				j--;
			}
		}

		for (int k = 0; k < player.bullets.size(); k++)
		{
			if (player.bullets[k]->getRect().intersects(enemyArray[i]->getRect()))
			{
				enemyArray[i]->m_health -= player.m_damage;
				if (enemyArray[i]->m_health <= 0)
				{
					player.m_credits += enemyArray[i]->m_creditsValue;
				}
				player.bullets[k]->~Projectile();
				player.bullets[k] = nullptr;
				player.bullets.erase(player.bullets.begin() + k);
				k--;
			}
		}
	}
}

void Play::updateEnemies(sf::Time dt)
{
	for (int i = 0; i < enemyArray.size(); i++)
	{
		enemyArray[i]->Update(dt, player.m_position);

		if (!enemyArray[i]->alive && enemyArray[i]->bullets.size() == 0)
		{
			enemyArray[i]->~Enemy();
			enemyArray[i] = nullptr;
			enemyArray.erase(enemyArray.begin() + i);
			i--;
			enemyCount--;
		}
	}
}


void Play::generateWave(int randEnemy)
{
	enemyOffset = 50;

	if (randEnemy == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy *enemy = new Enemy();
			enemy->Initialise(0, true, m_window, sf::Vector2f(m_window->getSize().x + (enemyOffset * i), 300 + (enemyOffset * i)), sf::Vector2f(2, 2), m_ramEnemySprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy *enemy = new Enemy();
			enemy->Initialise(1, true, m_window, sf::Vector2f(-50 - (enemyOffset * i), 300 + (enemyOffset * i)), sf::Vector2f(2, 2), m_ramEnemySprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 2)
	{
		enemyOffset = 80;
		for (int i = 0; i < 10; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(2, false, m_window, sf::Vector2f(-50 - (enemyOffset * i), 50), sf::Vector2f(2, 2), m_shipEnemySprite, 30, 5, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 3)
	{
		for (int i = 0; i < 10; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(3, false, m_window, sf::Vector2f(m_window->getSize().x + (enemyOffset * i), 175), sf::Vector2f(2, 2), m_shipEnemySprite, 30, 5, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 4)
	{
		Enemy *enemy = new Enemy();
		enemy->Initialise(4, false, m_window, sf::Vector2f(100, -50), sf::Vector2f(1, 1), m_shipEnemySprite, 100, 5, 50);
		enemyArray.push_back(enemy);
		enemyCount++;
	}

	if (randEnemy == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(5, true, m_window, sf::Vector2f(100 + (100 * i), -100), sf::Vector2f(2, 2), m_ramEnemySprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 6)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(5, true, m_window, sf::Vector2f(100 + (100 * i), -100), sf::Vector2f(2, 2), m_ramEnemySprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 7)
	{
		for (int i = 0; i < 1; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(7, false, m_window, sf::Vector2f(350,-300), sf::Vector2f(1,1), m_ramEnemySprite, 500, 10, 50000);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}
}

void Play::handleEvent(sf::Event e)
{

}