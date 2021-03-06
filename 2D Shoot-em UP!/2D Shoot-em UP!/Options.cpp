#include "Options.h"

/// <summary>
/// Constructor for the Options screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Options::Options(sf::RenderWindow *window) : Screen(window)
{
	fullScreen = true;
	fromPause = false;
}

/// <summary>
/// Initialises the Options and its initial gamestate 
/// Creates the Labels and Buttons and assigns their functions
/// </summary>
/// <param name="state"></param>
void Options::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("OPTIONS", sf::Vector2f(150, 40), 25));
	gui.add(uiHelper::makeLabel("Volume", sf::Vector2f(150, 285), 32), "Options_volumeLabel");
	menuBox.loadFromFile("./ASSETS/menu box.png");
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(60, 30);
	m_menuBox.setScale(1.4, 0.8);
	currentState = state;

	auto button = uiHelper::makeButton("Back", sf::Vector2f(500, 600), 200, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Options_backBtn");

	gui.add(uiHelper::makeSlider(sf::Vector2f(300, 300), 100, 18, 100), "Options_volumeSlider");
	gui.add(uiHelper::makeCheckBox("Mute", sf::Vector2f(300, 400), 50, 50, false), "Options_fullScreen");

	gui.add(uiHelper::makeLabel("Mute", sf::Vector2f(550, 300), 32), "Options_volumeValue");
}

/// <summary>
/// updates the Label for the volume slider and the function assigned to the back button
/// </summary>
/// <param name="fromPause"></param>
void Options::Update(bool fromPause, sf::Time dt)
{
	sliderVolumeHandler();
	backBtnHandler(fromPause);
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	menuShader.setUniform("time", timeSinceStart);
	menuShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));
	//chkFullScreenHandler();
}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void Options::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &menuShader);
	window->draw(m_menuBox);
	gui.draw();
}

/// <summary>
/// updates a label to output the value of the slider
/// </summary>
void Options::sliderVolumeHandler()
{
	tgui::Slider::Ptr volume = gui.get<tgui::Slider>("Options_volumeSlider");
	tgui::Label::Ptr volumeValue = gui.get<tgui::Label>("Options_volumeValue");
	volumeValue->setText(std::to_string(volume->getValue()) + "%");
}

/// <summary>
/// TO DO
/// </summary>
void Options::chkFullScreenHandler()
{
	tgui::CheckBox::Ptr fullScreenChk = gui.get<tgui::CheckBox>("Options_fullScreen");
	if (fullScreenChk->isChecked() && fullScreen != true)
	{
		fullScreen = true;
		windowPtr->create(sf::VideoMode(1280, 720), "2D Shoot-em Up!", sf::Style::Fullscreen);
	}
		else
		{
			fullScreen = false;
			windowPtr->create(sf::VideoMode(1280, 720), "2D Shoot-em Up!", sf::Style::Default);
	}
}

/// <summary>
/// If options was entered from the pause menu the back buttons function assigned is set to return to the pasue menu 
/// If options was entered from the main menu the back buttons function assigned is set to return to the main menu 
/// </summary>
/// <param name="fromPause"></param>
void Options::backBtnHandler(bool fromPause)
{
	tgui::Button::Ptr backBtn = gui.get<tgui::Button>("Options_backBtn");
	if (fromPause)
	{
		backBtn->connect("pressed", [&]() {GoToScreen(GameState::Pause); });
	}
	else
	{
		backBtn->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	}
}