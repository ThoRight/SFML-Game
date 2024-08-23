#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include <iostream>
#include <fstream>
class Scene;
class Scene_Play;
class Game
{
	sf::RenderWindow* m_window;
	EntityManager m_eM;
	Entity* m_player;
	std::map<std::string, Scene*> m_sceneMap;
	Scene* scene;
	Assets* m_assets;
	const int m_width;
	const int m_height;
	int m_point = 0;
	bool replay_mode = false;
	std::string currentScene;
	void init();
	void update();
	void sUserInput();
	void loadFromFile(const std::string& filename, const char c);
	void newGame();
	Scene* getCurrentScene()
	{
		return m_sceneMap[currentScene];
	}
	
	
public:
	void run();
	void close();
	void changeScene(const std::string& newScene);
	Game(int width, int height): m_width(width),m_height(height)
	{
		init();
	}
	sf::RenderWindow* getWindow()
	{
		return m_window;
	}
	Assets* getAssets()
	{
		return m_assets;
	}
	void setReplay(bool b)
	{
		replay_mode = b;
	}
	bool isReplay()
	{
		return replay_mode;
	}
	void addPoint(int p)
	{
		m_point += p;
	}
	int getPoint()const
	{
		return m_point;
	}
	void resetGameForReplay();
	~Game()
	{
		std::cout << "Game destroyed..";
		if (m_player != nullptr)
		{
			delete m_player;
			m_player = nullptr;
		}
		for (auto& e : m_sceneMap)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
		if (m_assets != nullptr)
		{
			delete m_assets;
			m_assets = nullptr;
		}
		if (m_window != nullptr)
		{
			delete m_window;
			m_window = nullptr;
		}
		
	}
};

#endif



