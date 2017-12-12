#include "Play.h"

/// <summary>
/// Constructor for the play game.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Play::Play(sf::RenderWindow *window, GameState *state) : Screen(window)
{
	currentState = state;
	
	mapTexture.loadFromFile("ASSETS/SpriteSheets/DungeonTileSet.png");
	demoMap.initialise("Demo_Tile Layer 1.csv", "Demo_Tile Layer 2.csv", "", "", &mapTexture);
	player.Initialise();
	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);
	merchant.initialise();

	// Create the label.
	auto label = sfg::Label::Create("Shop!");

	// Create a simple button and connect the click signal.
	auto button = sfg::Button::Create("Greet SFGUI!");
	//button->GetSignal(sfg::Widget::OnLeftClick).Connect( );

	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(label);
	box->Pack(button, false);

	auto shopWindow = sfg::Window::Create();
	shopWindow->SetTitle("Shop!");
	shopWindow->Add(box);

	
	shop.Add(shopWindow);
	
}
void Play::closeShop()
{
	shopVisible = false;
}

/// 
/// /// <summary>
/// updates the player and changes the gamestate to pause if the escape key is pressed
/// </summary>
void Play::Update(sf::Time dt)
{
	float time = dt.asSeconds();
	shop.Update(time);
	player.Update(dt, keyboard, &playerView);
	merchant.update(dt);
	for each  (std::vector<Tile>  v in demoMap.m_obstacleLayer)
	{
		for each  (Tile t in v)
		{
			tgui::FloatRect tileRect = t.m_sprite.getGlobalBounds();
			player.CheckCollision(tileRect);
		}
	}
	currentState;
	if (keyboard.isKeyPressed(keyboard.Escape))
	{
		GoToScreen(GameState::Pause);
	}
	if (keyboard.isKeyPressed(keyboard.Space) || keyboard.isKeyPressed(keyboard.E) || keyboard.isKeyPressed(keyboard.F))
	{
		if (distBetween(player.m_position, merchant.m_sprite.getPosition()) < 120)
		{
			shopVisible = true;
		}
		else
		{
			std::cout << std::endl;
		}
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
	playerView.setCenter(player.m_position);
	window->setView(playerView);
	demoMap.draw(window, sf::Vector2f(0, 0), true);
	
	

	player.Draw(window);
	merchant.draw(window);
	if (shopVisible)
	{
		sfgui.Display(*window);
	}
	window->setView(window->getDefaultView());
}


float Play::distBetween(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}

void Play::handleEvent(sf::Event e)
{
	shop.HandleEvent(e);
}