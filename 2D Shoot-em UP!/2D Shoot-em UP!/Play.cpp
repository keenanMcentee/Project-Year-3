#include "Play.h"

/// <summary>
/// Constructor for the play game.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Play::Play(sf::RenderWindow *window, GameState *state) : Screen(window)
{
	currentState = state;
	player.Initialise();
	enemy.Initialise(4, window, sf::Vector2f(600, 200));
	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);

	blankTexture.loadFromFile("./ASSETS/blankTexture.png");
	backgroundSprite.setTexture(blankTexture);
	backgroundShader.loadFromFile("./ASSETS/shaders/fragmentShaders/ground_one.frag", sf::Shader::Fragment);
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
	//HandleCollision();
	enemy.Update(dt, player.m_position);

	currentState;
	if (keyboard.isKeyPressed(keyboard.Escape))
	{
		GoToScreen(GameState::Pause);
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
	player.Draw(window);
	enemy.Draw();
	playerView.setCenter(player.m_position);

	//window->setView(playerView);
	//demoMap.draw(window, sf::Vector2f(0, 0), true);

	//merchant.draw(window);
	window->setView(window->getDefaultView());
}

float Play::distBetween(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}

void Play::HandleCollision()
{
	if (player.getRect().intersects(enemy.getRect()))
	{
		GoToScreen(GameState::MainMenu);
	}
}
void Play::handleEvent(sf::Event e)
{

}