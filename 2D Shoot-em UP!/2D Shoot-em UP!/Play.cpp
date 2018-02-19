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
	deadEnemies = 0;
	bossSpawnCount = 100;

	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);

	blankTexture.loadFromFile("./ASSETS/blankTexture.png");
	backgroundSprite.setTexture(blankTexture);
	backgroundShader.loadFromFile("./ASSETS/shaders/fragmentShaders/ground_one.frag", sf::Shader::Fragment);

	enemyOneTexture.loadFromFile("ASSETS/enemyBallThingie.png");
	enemyOneSprite.setTexture(enemyOneTexture);

	enemyTwoTexture.loadFromFile("ASSETS/Enemies/fidgetspinner.png");
	enemyTwoSprite.setTexture(enemyTwoTexture);

	enemyThreeTexture.loadFromFile("ASSETS/Enemies/fidgetspinner.png");
	enemyThreeSprite.setTexture(enemyThreeTexture);
	

	enemyFourTexture.loadFromFile("ASSETS/Enemies/cargoship.png");
	enemyFourSprite.setTexture(enemyFourTexture);

	enemyFiveTexture.loadFromFile("ASSETS/Enemies/spacestation.png");
	enemyFiveSprite.setTexture(enemyFiveTexture);

	enemySixTexture.loadFromFile("ASSETS/BulletShootingShip.png");
	enemySixSprite.setTexture(enemySixTexture);

	enemySpeed = 0.5f;


}
void Play::reset()
{
	
}

/// 
/// /// <summary>
/// updates the player and changes the gamestate to pause if the escape key is pressed
/// </summary>
void Play::Update(sf::Time dt)
{
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	backgroundShader.setUniform("time", timeSinceStart);
	backgroundShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));

	player.Update(dt, keyboard, &playerView);
	updateEnemies(dt);
	HandleCollision();


	if (deadEnemies >= bossSpawnCount)
	{
		bossWave = true;
	}

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

	if (!bossWave)
	{
		if (enemyCount <= 25)
		{
			int randEnemy1 = rand() % 6;
			int randEnemy2 = rand() % 6;
			if (randEnemy2 = randEnemy1)
			{
				int randEnemy2 = rand() % 5;
			}
			generateWave(randEnemy1);
			generateWave(randEnemy2);
		}
	}
	
	if (bossWave)
	{
		
		/*for (int i = 0; i < enemyArray.size(); i++)
		{
			if (enemyArray[i]->m_type != enemyArray[i]->BOSS_TYPE)
			{
				enemyArray[i]->m_health = 0;
			}
		}*/
		if (enemyCount < 1)
		{
			generateWave(7);
		}
	}

	currentState;

	if (keyboard.isKeyPressed(keyboard.Escape))
	{
		GoToScreen(GameState::Pause);
	}

	if (player.m_health <= 0)
	{
		GoToScreen(GameState::MainMenu);
	}

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
	

	for (int i = 0; i < enemyArray.size(); i++)
	{
		enemyArray[i]->Draw();
	}

	trackerEnemyType.Draw();

	playerView.setCenter(player.m_position);

	player.Draw();
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
			if (enemyArray[i]->m_type != enemyArray[i]->BOSS_TYPE)
			{
				player.m_health -= enemyArray[i]->m_damage;
				enemyArray[i]->m_health = 0;
			}
			else if (enemyArray[i]->m_type == enemyArray[i]->BOSS_TYPE)
			{
				player.m_position.y += player.m_speed;
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
				if (enemyArray[i]->m_type != enemyArray[i]->BOSS_TYPE)
				{
					enemyArray[i]->m_health -= player.m_damage;

					if (enemyArray[i]->m_health <= 0)
					{
						player.m_credits += enemyArray[i]->m_creditsValue;
						deadEnemies++;
						enemySpeed += 0.005f;
					}
				}

				if (enemyArray[i]->m_type == enemyArray[i]->BOSS_TYPE && enemyArray[i]->m_position.y >= 150)
				{

					if (enemyArray[i]->m_turretOneHealth > 0)
					{
						enemyArray[i]->m_turretOneHealth -= player.m_damage;
					}

					if (enemyArray[i]->m_turretTwoHealth > 0 && enemyArray[i]->m_turretOneHealth <= 0)
					{
						enemyArray[i]->m_turretTwoHealth -= player.m_damage;
					}

					if (enemyArray[i]->m_turretThreeHealth > 0 && enemyArray[i]->m_turretOneHealth <= 0 && enemyArray[i]->m_turretTwoHealth <= 0)
					{
						enemyArray[i]->m_turretThreeHealth -= player.m_damage;
					}

					if (enemyArray[i]->m_turretThreeHealth <= 0 && enemyArray[i]->m_turretOneHealth <= 0 && enemyArray[i]->m_turretTwoHealth <= 0)
					{
						enemyArray[i]->alive = false;
						bossWave = false;
						deadEnemies = 0;
						bossSpawnCount += 50;
					}
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
		enemyArray[i]->Update(dt, player.m_position, enemySpeed);

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
			enemy->Initialise(0, true, m_window, sf::Vector2f(m_window->getSize().x + (enemyOffset * i), 300 + (enemyOffset * i)), enemyOneSprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy *enemy = new Enemy();
			enemy->Initialise(1, true, m_window, sf::Vector2f(-50 - (enemyOffset * i), 300 + (enemyOffset * i)), enemyOneSprite, 50, 15, 50);
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
			enemy->Initialise(2, false, m_window, sf::Vector2f(-50 - (enemyOffset * i), 50), enemyTwoSprite, 30, 5, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 3)
	{
		for (int i = 0; i < 10; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(3, false, m_window, sf::Vector2f(m_window->getSize().x + (enemyOffset * i), 175), enemyThreeSprite, 30, 5, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 4)
	{
		Enemy *enemy = new Enemy();
		enemy->Initialise(4, false, m_window, sf::Vector2f(100, -50), enemyFourSprite, 100, 5, 50);
		enemyArray.push_back(enemy);
		enemyCount++;
	}

	if (randEnemy == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(5, true, m_window, sf::Vector2f(100 + (100 * i), -100), enemyFiveSprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 6)
	{
		for (int i = 0; i < 5; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(5, true, m_window, sf::Vector2f(100 + (100 * i), -100), enemySixSprite, 50, 15, 50);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}

	if (randEnemy == 7)
	{
		for (int i = 0; i < 1; i++)
		{
			Enemy* enemy = new Enemy();
			enemy->Initialise(7, false, m_window, sf::Vector2f(350,-300), enemySixSprite, 500, 10, 50000);
			enemyArray.push_back(enemy);
			enemyCount++;
		}
	}
}

void Play::handleEvent(sf::Event e)
{

}