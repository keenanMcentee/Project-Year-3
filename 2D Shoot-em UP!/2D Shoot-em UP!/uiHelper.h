#ifndef TGUI
#define TGUI
#include <TGUI/TGUI.hpp>

#endif // !TGUI

#include <iostream>

#ifndef UIHELPER
#define UIHELPER
namespace uiHelper
{
	static tgui::Theme theme{ "./themes/Black.txt" };
	static tgui::Tabs::Ptr makeTab(int height, sf::Vector2f pos, std::vector<std::string> tabNames, int numOfTabs)
	{
		tgui::Tabs::Ptr tabs = tgui::Tabs::create();
		tabs->setRenderer(theme.getRenderer("Tabs"));
		tabs->setTabHeight(height);
		tabs->setPosition(pos.x, pos.y);
		for (int i = 0; i < numOfTabs; i++)
		{
			tabs->add(tabNames[i]);
		}
		return tabs;
	}
	static tgui::Label::Ptr makeLabel(std::string labelText, sf::Vector2f position, int size)
	{
		auto label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setText(labelText);
		label->setPosition(position.x,position.y);
		label->setTextSize(size);
		return label;
	}

	static tgui::Button::Ptr makeButton(std::string btnText, sf::Vector2f position, int width, int height)
	{
		tgui::Button::Ptr button = tgui::Button::create();
		button->setRenderer(theme.getRenderer("Button"));
		button->setPosition(position.x, position.y);
		button->setSize(width, height);
		button->setText(btnText);
		/*button->connect("pressed", [&]()
		{
			Screen::GoToScreen(nextState);
		});*/
		return button;
	}
}
#endif // !UIHELPER