#include "Player.h"
#include <iostream>
#include "vector2.h"
Player::Player()
{
}
/// <summary>
/// 
/// </summary>
void Player::Initialise(sf::RenderWindow *window)
{
	for (int i = 0; i < playerStats.body_max_level + 1; i++)
	{
		for (int j = 0; j < playerStats.r_wing_max_level + 1; j++)
		{
			for (int k = 0; k < playerStats.l_wing_max_level + 1; k++)
			{
				sf::Texture* temp = new sf::Texture();
				std::string textureName = "" + std::to_string(i) +"-"+ std::to_string(j) +"-"+ std::to_string(k);
				temp->loadFromFile("ASSETS/player/"+ textureName + ".png");
				temp->setSmooth(true);
				std::pair<std::string, sf::Texture*> *tempPair = new std::pair<std::string,sf::Texture*>();
				tempPair->first = textureName;
				tempPair->second = temp;
				playerStats.ships.push_back(tempPair);
			}
		}
	}
	healthBarOverlayTexture.loadFromFile("ASSETS/powerCore.png");
	healthBarOverlay.setTexture(healthBarOverlayTexture);
	healthBarOverlay.setPosition(-40, 0);
	healthBarOverlay.setScale(0.7, 0.5);
	blankTexture.loadFromFile("ASSETS/blankTexture.png");
	healthBar.setTexture(blankTexture);
	healthBarBackground.setTexture(blankTexture);
	healthBarShader.loadFromFile("ASSETS/shaders/fragmentShaders/healthBar.frag", sf::Shader::Fragment);
	healthBarBackground.setScale(0.1, 0.1);
	healthBar.setPosition(50, 15);
	
	setTexture();
	m_bulletTexture.loadFromFile("ASSETS/playerLaserSprite.png");

	playerStats.m_sprite.setOrigin(playerStats.m_sprite.getLocalBounds().width / 2, playerStats.m_sprite.getLocalBounds().height / 2);
	playerStats.m_sprite.setScale(0.5,0.5);

	m_position = sf::Vector2f(300, 300);
	m_speed = 2;
	m_fireRate = 0.2f;
	m_health = 100;
	m_damage = 35;
	m_window = window;
	shaderTimer = 0;
}
/// <summary>
/// 
/// </summary>
/// <param name="keyboard"></param>
void Player::Update(sf::Time dt, sf::Keyboard &keyboard, sf::View *view)
{
	m_previousPos = m_position;
	
	animator.update(dt);
	animator.animate(m_gunFlash);
	
	HandleMovement(keyboard, view);
	for (auto &b : bullets)
	{
		b->update();
	}
	playerStats.m_sprite.setPosition(m_position);

	m_timeSinceLastShot += dt.asSeconds();

	shaderTimer += dt.asSeconds();

	healthBarShader.setUniform("hp", m_health / 100.0f);
	healthBarShader.setUniform("time", shaderTimer);
	healthBarShader.setUniform("resolution", sf::Glsl::Vec2(720,720));
	healthBarShader.setUniform("r", (1.0f - (m_health / 100)));
	healthBarShader.setUniform("g", m_health / 100.0f);
	healthBar.setScale(0.1 * (m_health / 100.0f), 0.025);
}
/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Player::Draw()
{
	m_gunFlash.setPosition(m_position + sf::Vector2f(cos(rotation * 3.14 / 180) * 9, sin(rotation * 3.14 / 180) * 12));
	m_gunFlash.setRotation(rotation);
	lookAtMouse(*m_window);
	for (auto &b : bullets)
	{
		b->draw();
	}
	m_window->draw(playerStats.m_sprite);
	healthBar.setPosition(50, 15);
	m_window->draw(healthBar, &healthBarShader);
	healthBar.setPosition(50, 40);
	m_window->draw(healthBar, &healthBarShader);
	m_window->draw(healthBarOverlay);
}

/// <summary>
/// 
/// </summary>
/// <param name="keyboard"></param>
void Player::HandleMovement(sf::Keyboard &keyboard, sf::View *view)
{
	if (keyboard.isKeyPressed(keyboard.A))
	{
		m_position.x -= m_speed;
		view->move(sf::Vector2f(-m_speed, 0));
	}
	else if (keyboard.isKeyPressed(keyboard.D))
	{
		m_position.x += m_speed;
		view->move(sf::Vector2f(m_speed, 0));
	}
	if (keyboard.isKeyPressed(keyboard.W))
	{
		m_position.y -= m_speed;
		view->move(sf::Vector2f(0, -m_speed));
	}
	else if (keyboard.isKeyPressed(keyboard.S))
	{
		m_position.y += m_speed;
		view->move(sf::Vector2f(0, m_speed));
	}
	if (keyboard.isKeyPressed(keyboard.LShift))
	{
		m_speed = 10;
	}
	/*if (keyboard.isKeyPressed(keyboard.X))
	{
		playerStats.l_wing_level++;
		setTexture();
	}*/
	else
	{
		m_speed = 2;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_timeSinceLastShot > m_fireRate)
	{
		m_timeSinceLastShot = 0;
		Projectile *bullet = new Projectile(m_position, playerStats.m_sprite.getRotation(), 100, 50, 400, &m_bulletTexture, m_window);
		bullets.push_back(bullet);
	}
	prevLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
/// <summary>
/// 
/// </summary>
/// <param name="win"></param>
void Player::lookAtMouse(sf::RenderWindow &win) {
	sf::Vector2f curPos = playerStats.m_sprite.getPosition();
	sf::Vector2f position = win.mapPixelToCoords(sf::Mouse::getPosition(win));

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	float pi = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	rotation = ((atan2(dy, dx)) * 180 / PI) + 180;

	playerStats.m_sprite.setRotation(rotation);
}

tgui::FloatRect Player::getRect()
{
	sf::FloatRect boundingBox = playerStats.m_sprite.getGlobalBounds();
	return tgui::FloatRect(boundingBox.left, boundingBox.top, boundingBox.width, boundingBox.height);
}

void Player::bulletEnemyCollision(Projectile b, Enemy *enemy)
{
	if (b.getRect().intersects(enemy->getRect()))
	{
		enemy->alive = false;
	}
}

void Player::CheckCollision(tgui::FloatRect &tile)
{
	if (tile.intersects(playerStats.m_sprite.getGlobalBounds()))
	{
		m_position = m_previousPos;
	}
}
float Player::ToRadians(float x)
{
	float pi = 3.14159265;
	return (x * pi / 180);
}
void Player::setTexture()
{
	for (int i = 0; i < playerStats.ships.size(); i++)
	{
		std::string shipName = "" + std::to_string(playerStats.body_level) +"-"+ std::to_string(playerStats.r_wing_level) +"-"+ std::to_string(playerStats.l_wing_level);
		if (playerStats.ships[i]->first == shipName)
		{
			playerStats.m_sprite.setTexture(*playerStats.ships[i]->second);
		}
	}
}
void Player::reset()
{
	playerStats.maxHealth = playerStats.healthLevel * 100;
	m_position = sf::Vector2f(300, 300);
	m_speed = 2;
	m_fireRate = 0.2f;
	m_health = 100;
	m_damage = 35;
	shaderTimer = 0;
	
}