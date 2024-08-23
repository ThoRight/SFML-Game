#ifndef Scene_LEVELCOMPLETE
#define Scene_LEVELCOMPLETE
#include "Scene.h"
class Scene_LevelComplete :
	public Scene
{
	Entity* doneMenu;
	std::string doneMenuStates[2] = { "NewGame", "Quit" };
	int currentStateIndex = 0;
	sf::Text pointInfo;
public:
	void update();
	void sRender();
	void sDoAction(const Action& action);
	void registerAction(int code, const std::string& s);
	void init();
	void sAnimation();
	void buildDoneMenu(const std::string& s);
	Scene_LevelComplete(Game* g) : Scene(g)
	{
		init();
	}
	~Scene_LevelComplete()
	{
		if (doneMenu != nullptr)
		{
			delete doneMenu;
			doneMenu = nullptr;
		}
	}
};

#endif

