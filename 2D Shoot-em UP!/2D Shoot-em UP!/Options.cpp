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
	gui.add(uiHelper::makeLabel("OPTIONS", sf::Vector2f(500, 100), 50));
	gui.add(uiHelper::makeLabel("Volume", sf::Vector2f(350, 285), 32), "Options_volumeLabel");
	
	currentState = state;

	auto button = uiHelper::makeButton("Back", sf::Vector2f(900, 600), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Options_backBtn");

	gui.add(uiHelper::makeSlider(sf::Vector2f(500, 300), 200, 18, 100), "Options_volumeSlider");
	gui.add(uiHelper::makeCheckBox("Mute", sf::Vector2f(500, 500), 50, 50, false), "Options_fullScreen");

	gui.add(uiHelper::makeLabel("Mute", sf::Vector2f(750, 300), 32), "Options_volumeValue");
}

/// <summary>
/// updates the Label for the volume slider and the function assigned to the back button
/// </summary>
/// <param name="fromPause"></param>
void Options::Update(bool fromPause)
{
	sliderVolumeHandler();
	backBtnHandler(fromPause);
	//chkFullScreenHandler();
}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void Options::Draw(sf::RenderWindow *window)
{
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