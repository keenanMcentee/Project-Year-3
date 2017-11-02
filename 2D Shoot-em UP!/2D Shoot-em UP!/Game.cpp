#include "Game.h"




Game::Game() : m_window(sf::VideoMode(1280,720), "2D Shoot-em Up!", sf::Style::Default)
{
	m_window.setFramerateLimit(60);
}


Game::~Game()
{
}
/// <summary>
/// Core game loop for our game.
/// </summary>
void Game::Run()
{
	Initialise();
	sf::Event event;
	sf::Clock clock;
	while (m_window.isOpen()) {
		// Event processing.
		while (m_window.pollEvent(event)) {
			desktop.HandleEvent(event);
		
		}
		Update(clock);
		Draw();

	}

}
/// <summary>
/// Function to Initialise all elements of the game.
/// </summary>
void Game::Initialise()
{
	testLevelTexture.loadFromFile("SpriteSheet.png");
	testLevel.initialise("TestLevel_Tile Layer 1.csv", "TestLevel_Tile Layer 2.csv", "", "", &testLevelTexture);
	//SFGUI
	// Create the label.
	auto label = sfg::Label::Create("Hello world!");
	// Create a simple button and connect the click signal.
	button = sfg::Button::Create("Greet SFGUI!");
	button->GetSignal(sfg::Widget::OnLeftClick).Connect([label] { label->SetText("Hello SFGUI, pleased to meet you!"); });
	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(label);
	box->Pack(button, false);
	// Create a window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetTitle("Hello world!");
	window->Add(box);
	window->SetPosition(sf::Vector2f(100, 100));
	// Create a desktop and add the window to it.
	desktop.Add(window);
	// We're not using SFML to render anything in this program, so reset OpenGL
	// states. Otherwise we wouldn't see anything.
	m_window.resetGLStates();
}
/// <summary>
/// Function that handles updating all objects and elements of the game.
/// </summary>
void Game::Update(sf::Clock &clock)
{
	// Update SFGUI with elapsed seconds since last call.
	desktop.Update(clock.restart().asSeconds());
}
/// <summary>
/// Function that communicates with the window to output everything to screen.
/// </summary>
void Game::Draw()
{
	m_window.clear(sf::Color::Black);

	//Draw code here.
	testLevel.draw(&m_window,sf::Vector2f(640,640), false);
	sfgui.Display(m_window);
	m_window.display();
}