#include "Upgrades.h"

Upgrades::Upgrades(sf::RenderWindow *window) : Screen(window)
{

}

void Upgrades::Initialise(GameState *state, Player *player)
{
	currentState = state;
	m_player = player;
	initLabels();
	initbuttons();
	initSprites();
}

void Upgrades::Draw(sf::RenderWindow *window)
{
	gui.draw();
	window->draw(m_lv1ShipSprite);
	window->draw(m_lv2ShipSprite);
	window->draw(m_lv3ShipSprite);
	window->draw(m_lv4ShipSprite);
	window->draw(m_lv5ShipSprite);
}

void Upgrades::buy(int shipLv)
{
	if (shipLv == 1)
	{
		m_lv1ShipCost = 0;
		tgui::Button::Ptr lv1 = gui.get<tgui::Button>("lv 1");
		lv1->setText("Purchased");

		m_player->m_sprite = m_lv1ShipSprite;
	}

	if (shipLv == 2)
	{
		m_lv2ShipCost = 0;
		tgui::Button::Ptr lv2 = gui.get<tgui::Button>("lv 2");
		lv2->setText("Purchased");

		m_player->m_sprite = m_lv2ShipSprite;
	}

	if (shipLv == 3)
	{
		m_lv3ShipCost = 0;
		tgui::Button::Ptr lv3 = gui.get<tgui::Button>("lv 3");
		lv3->setText("Purchased");

		m_player->m_sprite = m_lv3ShipSprite;
	}

	if (shipLv == 4)
	{
		m_lv4ShipCost = 0;
		tgui::Button::Ptr lv4 = gui.get<tgui::Button>("lv 4");
		lv4->setText("Purchased");

		m_player->m_sprite = m_lv4ShipSprite;
	}

	if (shipLv == 5)
	{
		m_lv5ShipCost = 0;
		tgui::Button::Ptr lv5 = gui.get<tgui::Button>("lv 5");
		lv5->setText("Purchased");

		m_player->m_sprite = m_lv5ShipSprite;
	}
}

void Upgrades::initbuttons()
{
	auto btnLv1ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv1ShipCost), sf::Vector2f(230, 150), 100, 100);
	btnLv1ShipBuy->connect("pressed", [&]() {
		buy(1);
	});
	gui.add(btnLv1ShipBuy, "lv 1");

	auto btnLv2ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv2ShipCost), sf::Vector2f(570, 150), 100, 100);
	btnLv2ShipBuy->connect("pressed", [&]() {
		buy(2);
	});
	gui.add(btnLv2ShipBuy, "lv 2");

	auto btnLv3ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv3ShipCost), sf::Vector2f(230, 325), 100, 100);
	btnLv3ShipBuy->connect("pressed", [&]() {
		buy(3);
	});
	gui.add(btnLv3ShipBuy, "lv 3");

	auto btnLv4ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv4ShipCost), sf::Vector2f(570, 325), 100, 100);
	btnLv4ShipBuy->connect("pressed", [&]() {
		buy(4);
	});
	gui.add(btnLv4ShipBuy, "lv 4");

	auto btnLv5ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv5ShipCost), sf::Vector2f(230, 530), 100, 100);
	btnLv5ShipBuy->connect("pressed", [&]() {
		buy(5);
	});
	gui.add(btnLv5ShipBuy, "lv 5");

	auto btnBack = uiHelper::makeButton("Back", sf::Vector2f(450, 550), 200, 100);
	btnBack->connect("pressed", [&]() {
		GoToScreen(GameState::PostWaveMenu);
	});
	gui.add(btnBack);
}

void Upgrades::initLabels()
{
	gui.add(uiHelper::makeLabel("Upgrades", sf::Vector2f(250, 0), 50));
	gui.add(uiHelper::makeLabel("Lv1 Ship", sf::Vector2f(100, 90), 16));
	gui.add(uiHelper::makeLabel("Lv2 Ship", sf::Vector2f(400, 90), 16));
	gui.add(uiHelper::makeLabel("Lv3 Ship", sf::Vector2f(100, 280), 16));
	gui.add(uiHelper::makeLabel("Lv4 Ship", sf::Vector2f(400, 280), 16));
	gui.add(uiHelper::makeLabel("Lv5 Ship", sf::Vector2f(100, 480), 16));
}

void Upgrades::initSprites()
{
	m_lv1ShipTexture.loadFromFile("ASSETS/player/level 1 ship.png");
	m_lv2ShipTexture.loadFromFile("ASSETS/player/level 2 ship.png");
	m_lv3ShipTexture.loadFromFile("ASSETS/player/level 3 ship.png");
	m_lv4ShipTexture.loadFromFile("ASSETS/player/level 4 ship.png");
	m_lv5ShipTexture.loadFromFile("ASSETS/player/level 5 ship.png");

	m_lv1ShipSprite.setTexture(m_lv1ShipTexture);
	m_lv2ShipSprite.setTexture(m_lv2ShipTexture);
	m_lv3ShipSprite.setTexture(m_lv3ShipTexture);
	m_lv4ShipSprite.setTexture(m_lv4ShipTexture);
	m_lv5ShipSprite.setTexture(m_lv5ShipTexture);


	m_lv1ShipSprite.setOrigin(m_lv1ShipSprite.getLocalBounds().width / 2, m_lv1ShipSprite.getLocalBounds().height / 2);
	m_lv1ShipSprite.setPosition(sf::Vector2f(250, 275));
	m_lv1ShipSprite.setScale(0.3f, 0.3f);

	m_lv2ShipSprite.setOrigin(m_lv2ShipSprite.getLocalBounds().width / 2, m_lv2ShipSprite.getLocalBounds().height / 2);
	m_lv2ShipSprite.setPosition(sf::Vector2f(400, 275));
	m_lv2ShipSprite.setScale(0.1f, 0.1f);

	m_lv3ShipSprite.setOrigin(m_lv3ShipSprite.getLocalBounds().width / 2, m_lv3ShipSprite.getLocalBounds().height / 2);
	m_lv3ShipSprite.setPosition(sf::Vector2f(250, 370));
	m_lv3ShipSprite.setScale(0.175f, 0.175f);

	m_lv4ShipSprite.setOrigin(m_lv4ShipSprite.getLocalBounds().width / 2, m_lv4ShipSprite.getLocalBounds().height / 2);
	m_lv4ShipSprite.setPosition(sf::Vector2f(410, 370));
	m_lv4ShipSprite.setScale(0.3f, 0.3f);

	m_lv5ShipSprite.setOrigin(m_lv5ShipSprite.getLocalBounds().width / 2, m_lv5ShipSprite.getLocalBounds().height / 2);
	m_lv5ShipSprite.setPosition(sf::Vector2f(250, 480));
	m_lv5ShipSprite.setScale(0.175f, 0.175f);
}