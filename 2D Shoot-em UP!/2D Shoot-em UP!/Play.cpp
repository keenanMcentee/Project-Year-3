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
	//enemy.Initialise();
	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);
	merchant.initialise();

	 //Create the label.
	auto screen = this;
	// Create a simple button and connect the click signal.
	auto btnQuit = sfg::Button::Create("QUIT!");
	auto btnAssaultRifle = sfg::Button::Create("Assault Rifle");
	auto btnSMG = sfg::Button::Create("Sub Machine Gun");
	auto btnMachineGun = sfg::Button::Create("Machine Gun");

	//btnQuit->GetSignal(sfg::Widget::OnLeftClick).Connect([screen]() { screen->closeShop(); });

	auto box = sfg::Box::Create();
	
	box->Pack(btnAssaultRifle, false);
	box->Pack(btnSMG, false);
	box->Pack(btnMachineGun, false);
	box->Pack(btnQuit, false);

	box->Pack(sfg::Separator::Create());
	//
	auto shopWindow = sfg::Window::Create();
	shopWindow->SetPosition(sf::Vector2f(250, 200));
	//Requisition is Size...?
	
	shopWindow->SetRequisition(sf::Vector2f(800, 800));
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
	merchant.update(dt);
	player.Update(dt, keyboard, &playerView, &enemy);
	enemy.Update(dt, player.m_sprite.getPosition());
	for each  (std::vector<Tile>  v in demoMap.m_obstacleLayer)
	{
		for each  (Tile t in v)
		{
			tgui::FloatRect tileRect = t.m_sprite.getGlobalBounds();
			player.CheckCollision(tileRect);
		}
	}
	HandleCollision();
	
	
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
	enemy.Draw(window);
	
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

void Play::HandleCollision()
{
	if (player.getRect().intersects(enemy.getRect()))
	{
		GoToScreen(GameState::MainMenu);
	}
}
void Play::handleEvent(sf::Event e)
{
	shop.HandleEvent(e);
}