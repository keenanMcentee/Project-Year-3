#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>
class Merchant
{
public:
	Merchant();
	~Merchant();
	thor::Animator<sf::Sprite, std::string> animator;
	thor::FrameAnimation m_animation;

	void initialise();
	void update(sf::Time dt);
	void draw(sf::RenderWindow *window);
	void interaction();
	sf::Sprite m_sprite;
private:
	
	sf::Texture m_texture;

	sf::Vector2f m_pos;
};

