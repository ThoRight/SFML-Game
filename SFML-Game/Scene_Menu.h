#ifndef SCENE_MENU
#define SCENE_MENU
#include "Scene.h"
class Scene_Menu
	: public Scene
{
	Entity* menu;
	std::string menuStates[2] = { "Play", "Exit" };
	int currentStateIndex = 0;
public:
	void update();
	void sRender();
	void sDoAction(const Action& action);
	void registerAction(int code, const std::string& s);
	void init();
	void sAnimation();
	void buildMenu(const std::string& s);
	Scene_Menu(Game* g) : Scene(g)
	{
		init();
	}
	~Scene_Menu()
	{
		if (menu != nullptr)
		{
			delete menu;
			menu = nullptr;
		}
	}
};

#endif