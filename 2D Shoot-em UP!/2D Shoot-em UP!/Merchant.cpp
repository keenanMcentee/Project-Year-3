#include "Merchant.h"
#include <iostream>


Merchant::Merchant()
{
	
}

void Merchant::initialise()
{
	m_texture.loadFromFile("./ASSETS/Merchant.png");
	m_sprite.setTexture(m_texture);

	std::vector<sf::IntRect> rectangles;
	int frames = 31;
	for (int i = 0; i < frames; i++)
	{
		sf::IntRect rect((m_texture.getSize().x / frames) * i, 0, m_texture.getSize().x / frames, m_texture.getSize().y);
		m_animation.addFrame(0.1f, rect);
	}
	animator.addAnimation("merchant", m_animation, sf::seconds(0.1f));
	m_sprite.setPosition(sf::Vector2f(600, 600));
}
void Merchant::update(sf::Time dt)
{	

	animator.update(dt);
	animator.animate(m_sprite);
	animator.playAnimation("merchant", true);
}

void Merchant::draw(sf::RenderWindow *window)
{
	if (animator.isPlayingAnimation())
		window->draw(m_sprite);
}

void Merchant::interaction()
{
	std::cout << "Merchant" << std::endl;
}
Merchant::~Merchant()
{
}
