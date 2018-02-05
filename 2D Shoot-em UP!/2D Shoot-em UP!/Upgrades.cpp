#include "Upgrades.h"

Upgrades::Upgrades(sf::RenderWindow *window) : Screen(window)
{

}

void Upgrades::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("Upgrades", sf::Vector2f(250, 50), 50));

	currentState = state;

	auto btnBack = uiHelper::makeButton("Back", sf::Vector2f(500, 600), 200, 100);
	btnBack->connect("pressed", [&]() {
		GoToScreen(GameState::PostWaveMenu);
	});
	gui.add(btnBack);

	auto lv1ShipLabel = uiHelper::makeLabel("Lv1 Ship", sf::Vector2f(25, 200), 16);
	auto lv2ShipLabel = uiHelper::makeLabel("Lv2 Ship", sf::Vector2f(175, 200), 16);
	auto lv3ShipLabel = uiHelper::makeLabel("Lv3 Ship", sf::Vector2f(325, 200), 16);
	auto lv4ShipLabel = uiHelper::makeLabel("Lv4 Ship", sf::Vector2f(475, 200), 16);
	auto lv5ShipLabel = uiHelper::makeLabel("Lv5 Ship", sf::Vector2f(625, 200), 16);
	gui.add(lv1ShipLabel);
	gui.add(lv2ShipLabel);
	gui.add(lv3ShipLabel);
	gui.add(lv4ShipLabel);
	gui.add(lv5ShipLabel);

	auto btnLv1ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv1ShipCost), sf::Vector2f(0, 450), 100, 100);
	btnLv1ShipBuy->connect("pressed", [&]() {
		buy(1);
	});
	gui.add(btnLv1ShipBuy, "lv 1");

	auto btnLv2ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv2ShipCost), sf::Vector2f(150, 450), 100, 100);
	btnLv2ShipBuy->connect("pressed", [&]() {
		buy(2);
	});
	gui.add(btnLv2ShipBuy, "lv 2");

	auto btnLv3ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv3ShipCost), sf::Vector2f(300, 450), 100, 100);
	btnLv3ShipBuy->connect("pressed", [&]() {
		buy(3);
	});
	gui.add(btnLv3ShipBuy, "lv 3");

	auto btnLv4ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv4ShipCost), sf::Vector2f(450, 450), 100, 100);
	btnLv4ShipBuy->connect("pressed", [&]() {
		buy(4);
	});
	gui.add(btnLv4ShipBuy, "lv 4");

	auto btnLv5ShipBuy = uiHelper::makeButton("Cost: " + std::to_string(m_lv5ShipCost), sf::Vector2f(600, 450), 100, 100);
	btnLv5ShipBuy->connect("pressed", [&]() {
		buy(5);
	});
	gui.add(btnLv5ShipBuy, "lv 5");
}

void Upgrades::Draw(sf::RenderWindow *window)
{
	gui.draw();
}

void Upgrades::buy(int shipLv)
{
	if (shipLv == 1)
	{
		m_lv1ShipCost = 0;
		tgui::Button::Ptr lv1 = gui.get<tgui::Button>("lv 1");
		lv1->setText("Purchased");
	}

	if (shipLv == 2)
	{
		m_lv2ShipCost = 0;
		tgui::Button::Ptr lv2 = gui.get<tgui::Button>("lv 2");
		lv2->setText("Purchased");
	}

	if (shipLv == 3)
	{
		m_lv3ShipCost = 0;
		tgui::Button::Ptr lv3 = gui.get<tgui::Button>("lv 3");
		lv3->setText("Purchased");
	}

	if (shipLv == 4)
	{
		m_lv4ShipCost = 0;
		tgui::Button::Ptr lv4 = gui.get<tgui::Button>("lv 4");
		lv4->setText("Purchased");
	}

	if (shipLv == 5)
	{
		m_lv5ShipCost = 0;
		tgui::Button::Ptr lv5 = gui.get<tgui::Button>("lv 5");
		lv5->setText("Purchased");
	}
}