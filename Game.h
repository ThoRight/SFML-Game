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
	std::string currentScene;
	void init();
	void quit();
	void update();
	void changeScene(const std::string& newScene);
	void sUserInput();
	void loadFromFile(const std::string& filename, const char c);
	
	Scene* getCurrentScene()
	{
		return m_sceneMap[currentScene];
	}
	
	
public:
	void run();
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
	~Game()
	{
		std::cout << "Game destroyed..";
		delete m_player;
		for (auto& e : m_sceneMap)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
		delete m_assets;
		delete m_window;
		
		delete this;
		
	}
};

#endif



