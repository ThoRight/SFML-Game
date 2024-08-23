#ifndef SCENE_H
#define SCENE_H
#include "Game.h"
class Scene
{
protected:
	Game* m_game = nullptr;
	EntityManager m_eM;
	int m_currentFrame = 0;
	std::map<int, std::string> m_actionMap;
	bool m_paused = false;
	bool m_hasEnded = false;
public:
	virtual void update() = 0;
	virtual void sRender() = 0;
	
	virtual void sDoAction(const Action& action) = 0;
	virtual void registerAction(int code, const std::string& s) = 0;
	Scene(Game* g)
	{
		m_game = g;
		m_eM = EntityManager();
	}
	std::map<int, std::string>& getActionMap()
	{
		return m_actionMap;
	}
	virtual ~Scene()
	{

	}
	Game* getGame()
	{
		return m_game;
	}
};

#endif






