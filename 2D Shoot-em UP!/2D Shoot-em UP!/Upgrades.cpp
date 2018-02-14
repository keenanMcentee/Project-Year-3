#include "Upgrades.h"

Upgrades::Upgrades(sf::RenderWindow *window) : Screen(window)
{

}

void Upgrades::Initialise(GameState *state, PlayerStats* _stats)
{
	currentState = state;
	stats = _stats;
	initbuttons();
}

void Upgrades::Draw(sf::RenderWindow *window, sf::Time dt)
{
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	menuShader.setUniform("time", timeSinceStart);
	menuShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));
	stats->m_sprite.setRotation(0);
	stats->m_sprite.setScale(2,2);
	stats->m_sprite.setPosition(200, 200);
	window->draw(backgroundSprite, &menuShader);
	window->draw(stats->m_sprite);
	gui.draw();
}

void Upgrades::buy()
{
	stats->body_level = tempBodyLevel;
	stats->l_wing_level = tempLWingLevel;
	stats->r_wing_level = tempRWingLevel;
}

void Upgrades::initbuttons()
{
	float uiSizeX = getScreenSize().x / 20;
	float uiSizeY = getScreenSize().y / 20;
	/*
	LEFT WING SECTION
	*/
			auto btnLeftWingPlus = uiHelper::makeButton("+", sf::Vector2f(getScreenSize().x / 12 * 3 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
			btnLeftWingPlus->connect("pressed", [&]() {
				if (tempLWingLevel < stats->l_wing_max_level)
				{
					tempLWingLevel++;
				}
				setTexture();
			});
			gui.add(btnLeftWingPlus, "leftWingPlus");
			auto lbl_L_wing = uiHelper::makeLabel("Left Wing", sf::Vector2f(getScreenSize().x / 12 * 2 - uiSizeX / 4 - 10, (getScreenSize().y / 6) * 4 + 10), 12);
			gui.add(lbl_L_wing);
	
			auto btnLeftWingMinus = uiHelper::makeButton("-", sf::Vector2f(getScreenSize().x / 12 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
			btnLeftWingMinus->connect("pressed", [&]() {
				if (tempLWingLevel > 0)
				{
					tempLWingLevel--;
				}
				setTexture();
			});
			gui.add(btnLeftWingMinus, "leftWingMinus");


	/*
	RIGHT WING SECTION
	*/
	auto btnRightWingPlus = uiHelper::makeButton("+", sf::Vector2f(getScreenSize().x / 12 * 7 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
	btnRightWingPlus->connect("pressed", [&]() {
		if (tempRWingLevel < stats->r_wing_max_level)
		{
			tempRWingLevel++;
		}
		setTexture();
	});
	gui.add(btnRightWingPlus, "rightWingPlus");
	auto lbl_R_wing = uiHelper::makeLabel("Right Wing", sf::Vector2f(getScreenSize().x / 12 * 6 - uiSizeX / 4 - 10, (getScreenSize().y / 6) * 4 + 10), 12);
	gui.add(lbl_R_wing);

	auto btnRightWingMinus = uiHelper::makeButton("-", sf::Vector2f(getScreenSize().x / 12 * 5 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
	btnRightWingMinus->connect("pressed", [&]() {
		if (tempRWingLevel > 0)
		{
			tempRWingLevel--;
		}
		setTexture();
	});
	gui.add(btnRightWingMinus, "rightWingMinus");


	/*
	BODY SECTION
	*/
	auto btnBodyPlus = uiHelper::makeButton("+", sf::Vector2f(getScreenSize().x / 12 * 11 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
	btnBodyPlus->connect("pressed", [&]() {
		if (tempBodyLevel < stats->body_max_level)
		{
			tempBodyLevel++;
		}
		setTexture();
	});
	gui.add(btnBodyPlus, "bodyPlus");
	auto lbl_body = uiHelper::makeLabel("Body", sf::Vector2f(getScreenSize().x / 12 * 10 - uiSizeX / 4 - 7, (getScreenSize().y / 6) * 4 + 10), 12);
	gui.add(lbl_body);

	auto btnBodyMinus = uiHelper::makeButton("-", sf::Vector2f(getScreenSize().x / 12 * 9 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
	btnBodyMinus->connect("pressed", [&]() {
		if (tempBodyLevel > 0)
		{
			tempBodyLevel--;
		}
		setTexture();
	});
	gui.add(btnBodyMinus, "bodyMinus");







	auto btnBuy = uiHelper::makeButton("Confirm Purchase", sf::Vector2f(getScreenSize().x / 2 - uiSizeX / 4, (getScreenSize().y / 6) * 5), uiSizeX * 3, uiSizeY * 1.5);
	btnBuy->connect("pressed", [&]() {
		buy();
	});
	gui.add(btnBuy, "buy");


	auto btnReturn = uiHelper::makeButton("Back", sf::Vector2f(getScreenSize().x / 12 * 10 - uiSizeX / 4, (getScreenSize().y / 6) * 5.5), uiSizeX * 2, uiSizeY);
	btnReturn->connect("pressed", [&]() {
		*currentState = GameState::Pause;
		stats->m_sprite.setScale(0.5, 0.5);
		reset();
	});
	gui.add(btnReturn, "");
}

void Upgrades::initLabels()
{

}

void Upgrades::initSprites()
{

}

void Upgrades::reset()
{
	tempLWingLevel = stats->l_wing_level;
	tempRWingLevel = stats->r_wing_level;
	tempBodyLevel = stats->body_level;
	setTexture();
}
void Upgrades::setTexture()
{
	for (int i = 0; i < stats->ships.size(); i++)
	{
		std::string shipName = "" + std::to_string(tempBodyLevel) + "-" + std::to_string(tempRWingLevel) + "-" + std::to_string(tempLWingLevel);
		if (stats->ships[i]->first == shipName)
		{
			stats->m_sprite.setTexture(*stats->ships[i]->second);
		}
	}
}