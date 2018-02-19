#include "Upgrades.h"

Upgrades::Upgrades(sf::RenderWindow *window) : Screen(window)
{

}

void Upgrades::Initialise(GameState *state, PlayerStats* _stats)
{
	currentState = state;
	stats = _stats;
	initbuttons();
	initLabels();
}

void Upgrades::Draw(sf::RenderWindow *window, sf::Time dt)
{
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	menuBox.loadFromFile("./ASSETS/menu box.png");

	tgui::Label::Ptr lbl_cash = gui.get<tgui::Label>("lbl_Cash");
	lbl_cash->setText("Current cash: " + std::to_string(stats->cash));

	m_menuBox1.setTexture(menuBox);
	m_menuBox2.setTexture(menuBox);
	m_menuBox3.setTexture(menuBox);

	menuShader.setUniform("time", timeSinceStart);
	menuShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));

	stats->m_sprite.setRotation(0);
	stats->m_sprite.setScale(2,2);
	stats->m_sprite.setPosition(200, 200);

	window->draw(backgroundSprite, &menuShader);
	window->draw(stats->m_sprite);

	gui.draw();


	std::cout << stats->cash << std::endl;
}

void Upgrades::buy()
{
	stats->cash = stats->cash - (1000 * ((tempBodyLevel - stats->body_level) + (tempLWingLevel - stats->l_wing_level) + (tempRWingLevel - stats->r_wing_level)));

	tgui::Label::Ptr lbl_cash = gui.get<tgui::Label>("lbl_Cash");
	lbl_cash->setText("Current cash: " + std::to_string(stats->cash));

	stats->healthLevel = tempBodyLevel;
	stats->maxHealth = tempBodyLevel * 100;
	stats->l_wing_level = tempLWingLevel;
	stats->r_wing_level = tempRWingLevel;

	stats->m_damage = (stats->l_wing_level + stats->r_wing_level) * 10 +15;

	tgui::Label::Ptr lbl_Left_Wing_Lv = gui.get<tgui::Label>("lbl_Current_Left_Wing");
	lbl_Left_Wing_Lv->setText("Current left wing level: " + std::to_string(stats->l_wing_level));

	tgui::Label::Ptr lbl_Right_Wing_Lv = gui.get<tgui::Label>("lbl_Current_Right_Wing");
	lbl_Right_Wing_Lv->setText("Current right wing level: " + std::to_string(stats->r_wing_level));

	tgui::Label::Ptr lbl_Body_lv = gui.get<tgui::Label>("lbl_Current_Body");
	lbl_Body_lv->setText("Current body level: " + std::to_string(stats->body_level));
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
				setCost();
				setCurrentLevel();
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
				setCost();
				setCurrentLevel();
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
		setCost();
		setCurrentLevel();
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
		setCost();
		setCurrentLevel();
		setTexture();
	});
	gui.add(btnRightWingMinus, "rightWingMinus");


	/*
	BODY SECTION
	*/
	auto btnBodyPlus = uiHelper::makeButton("+", sf::Vector2f(getScreenSize().x / 12 * 11 - uiSizeX / 4, (getScreenSize().y / 6) * 4), uiSizeX, uiSizeY);
	btnBodyPlus->connect("pressed", [&]() {
		if (tempBodyLevel < stats->maxHealthLevel)
		{
			tempBodyLevel++;
		}
		setCost();
		setCurrentLevel();
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
		setCost();
		setCurrentLevel();
		setTexture();
	});
	gui.add(btnBodyMinus, "bodyMinus");



	auto btnBuy = uiHelper::makeButton("Confirm Purchase", sf::Vector2f(getScreenSize().x / 2 - uiSizeX / 4, (getScreenSize().y / 6) * 5), uiSizeX * 3, uiSizeY * 1.5);
	btnBuy->connect("pressed", [&]() {
		if (stats->cash >= 1000 * ((tempBodyLevel - stats->body_level) + (tempLWingLevel - stats->l_wing_level) + (tempRWingLevel - stats->r_wing_level)))
		{
			buy();
			setCost();
			std::cout << "buy" << std::endl;
		}
		else
		{
			tgui::Label::Ptr lbl = gui.get<tgui::Label>("lbl_total_Cost");
			lbl->setText("not enough money");
		}

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
	auto lbl_Cash = uiHelper::makeLabel("Current cash: " + std::to_string(stats->cash), sf::Vector2f(getScreenSize().x - 300, 200), 20);
	gui.add(lbl_Cash, "lbl_Cash");

	auto lbl_Current_Left_Wing = uiHelper::makeLabel("Current left wing level: " + std::to_string(stats->l_wing_level), sf::Vector2f(50,450), 12);
	gui.add(lbl_Current_Left_Wing, "lbl_Current_Left_Wing");

	auto lbl_Current_Right_Wing = uiHelper::makeLabel("Current right wing level: " + std::to_string(stats->r_wing_level), sf::Vector2f(300, 450), 12);
	gui.add(lbl_Current_Right_Wing, "lbl_Current_Right_Wing");

	auto lbl_Current_Body = uiHelper::makeLabel("Current body level: " + std::to_string(stats->body_level), sf::Vector2f(520, 450), 12);
	gui.add(lbl_Current_Body, "lbl_Current_Body");

	auto lbl_Total_Cost = uiHelper::makeLabel("Total Cost: " + std::to_string(1000 * ((tempBodyLevel - stats->body_level) + (tempLWingLevel - stats->l_wing_level) + (tempRWingLevel - stats->r_wing_level))), sf::Vector2f(420, 700), 12);
	gui.add(lbl_Total_Cost, "lbl_total_Cost");

	auto lbl_Left_Wing_Lv = uiHelper::makeLabel("left wing level: " + std::to_string(tempLWingLevel), sf::Vector2f(50, 550), 12);
	gui.add(lbl_Left_Wing_Lv, "lbl_Left_Wing_Lv");

	auto lbl_Right_Wing_Lv = uiHelper::makeLabel("right wing level: " + std::to_string(tempRWingLevel), sf::Vector2f(300, 550), 12);
	gui.add(lbl_Right_Wing_Lv, "lbl_Right_Wing_Lv");

	auto lbl_Body_Lv = uiHelper::makeLabel("body level: " + std::to_string(tempBodyLevel), sf::Vector2f(520, 550), 12);
	gui.add(lbl_Body_Lv, "lbl_Body_Lv");
}

void Upgrades::initSprites()
{

}

void Upgrades::setCurrentLevel()
{
	tgui::Label::Ptr lbl_LeftWing = gui.get<tgui::Label>("lbl_Left_Wing_Lv");
	lbl_LeftWing->setText("left wing level: " + std::to_string(tempLWingLevel));

	tgui::Label::Ptr lblRightWing = gui.get<tgui::Label>("lbl_Right_Wing_Lv");
	lblRightWing->setText("right wing level: " + std::to_string(tempRWingLevel));

	tgui::Label::Ptr lblBody = gui.get<tgui::Label>("lbl_Body_Lv");
	lblBody->setText("body level: " + std::to_string(tempBodyLevel));
}

void Upgrades::setCost()
{
	if (1000 * ((tempBodyLevel - stats->body_level) + (tempLWingLevel - stats->l_wing_level) + (tempRWingLevel - stats->r_wing_level)) >= 0)
	{
		tgui::Label::Ptr lbl = gui.get<tgui::Label>("lbl_total_Cost");
		lbl->setText("Total Cost: " + std::to_string(1000 * ((tempBodyLevel - stats->body_level) + (tempLWingLevel - stats->l_wing_level) + (tempRWingLevel - stats->r_wing_level))));
	}
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