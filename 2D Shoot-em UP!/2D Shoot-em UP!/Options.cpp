#include "Options.h"

Options::Options(sf::RenderWindow *window) : Screen(window)
{
	fullScreen = true;
}
void Options::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("OPTIONS SCREEN", sf::Vector2f(100, 100), 32));
	gui.add(uiHelper::makeLabel("Volume", sf::Vector2f(350, 285), 32), "Options_volumeLabel");
	
	currentState = state;

	auto button = uiHelper::makeButton("Back", sf::Vector2f(500, 100), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Options_backBtn");

	gui.add(uiHelper::makeSlider(sf::Vector2f(500, 300), 200, 18, 100), "Options_volumeSlider");
	gui.add(uiHelper::makeCheckBox("Mute", sf::Vector2f(500, 500), 50, 50, false), "Options_fullScreen");


	gui.add(uiHelper::makeLabel("Mute", sf::Vector2f(750, 300), 32), "Options_volumeValue");
}
void Options::Update()
{
	sliderVolumeHandler();
	//chkFullScreenHandler();
}
void Options::Draw(sf::RenderWindow *window)
{
	gui.draw();
}
void Options::sliderVolumeHandler()
{
	tgui::Slider::Ptr volume = gui.get<tgui::Slider>("Options_volumeSlider");
	tgui::Label::Ptr volumeValue = gui.get<tgui::Label>("Options_volumeValue");
	volumeValue->setText(std::to_string(volume->getValue()) + "%");
}

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