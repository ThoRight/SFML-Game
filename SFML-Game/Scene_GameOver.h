#ifndef SCENE_GAMEOVER
#define SCENE_GAMEOVER
#include "Scene.h"
class Scene_GameOver :
    public Scene
{
	Entity* goMenu;
	std::string goMenuStates[2] = { "NewGame", "Quit" };
	int currentStateIndex = 0;
	sf::Text pointInfo;
public:
	void update();
	void sRender();
	void sDoAction(const Action& action);
	void registerAction(int code, const std::string& s);
	void init();
	void sAnimation();
	void buildGoMenu(const std::string& s);
	Scene_GameOver(Game* g) : Scene(g)
	{
		init();
	}
	~Scene_GameOver()
	{
		if (goMenu != nullptr)
		{
			delete goMenu;
			goMenu = nullptr;
		}
	}
};

#endif

