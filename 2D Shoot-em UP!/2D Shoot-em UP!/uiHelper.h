#ifndef TGUI
#define TGUI
#include <TGUI/TGUI.hpp>
#endif // !TGUI



#ifndef UIHELPER
#define UIHELPER
namespace uiHelper
{
	static tgui::Tabs::Ptr makeTab(tgui::Theme theme, int height, sf::Vector2f pos, std::vector<std::string> tabNames, int numOfTabs)
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

}
#endif // !UIHELPER



