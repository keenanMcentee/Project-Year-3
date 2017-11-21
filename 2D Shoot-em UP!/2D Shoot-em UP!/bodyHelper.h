#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#ifndef BODYHELPER
#define BODYHELPER
namespace bodyHelper
{
	static b2Body* makeBody(b2World* world, sf::Vector2f position, sf::Vector2f size,b2BodyType type)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.type = type;

		b2PolygonShape box;
		box.SetAsBox(size.x /2, size.y/2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;



		b2Body* body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		return body;
	}
}
#endif // !BODYHELPER