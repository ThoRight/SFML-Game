#include "Scene_Play.h"
#include "Scene_Menu.h"
#include "Scene_GameOver.h"
#include "Scene_LevelComplete.h"
#include "Scene_Replay.h"
void Game::init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "SFML works!");
	m_assets = new Assets();
	m_window->setFramerateLimit(60);
	loadFromFile("./Assets/Textures.txt", 'T');
	loadFromFile("./Assets/Animations.txt", 'A');
	loadFromFile("./Assets/Fonts.txt", 'F');
	loadFromFile("./Assets/Sounds.txt", 'S');
	// LOAD ASSETS.
	// INIT. SCENE.
	Scene* s1 = new Scene_Play(this);
	Scene* s2 = new Scene_Menu(this);
	Scene* s3 = new Scene_GameOver(this);
	Scene* s4 = new Scene_LevelComplete(this);
	Scene* s5 = new Scene_Replay(this, s1);
	//	Scene* s3 = new Scene_Play(this);
	m_sceneMap["Play"] = s1;
	m_sceneMap["Menu"] = s2;
	m_sceneMap["GameOver"] = s3;
	m_sceneMap["LevelComplete"] = s4;
	m_sceneMap["Replay"] = s5;
	//changeScene("Play");
	changeScene("Menu");
}

void Game::changeScene(const std::string& newScene)
{
	if (currentScene == "GameOver" || currentScene == "LevelComplete")
	{
		newGame();
	}
	if (newScene == "Replay")
	{
		delete(m_sceneMap["Replay"]);
		m_sceneMap["Replay"] = new Scene_Replay(this, m_sceneMap["Play"]);
	}
	currentScene = newScene;
}
void Game::newGame()
{
	m_point = 0;
	if (m_sceneMap["Play"] != nullptr)
	{
		delete m_sceneMap["Play"];
		m_sceneMap["Play"] = nullptr;
	}
	Scene* s = new Scene_Play(this);
	m_sceneMap["Play"] = s;
}
void Game::loadFromFile(const std::string& filename, const char c)
{
	std::ifstream f(filename);
	if (!f)
	{
		std::cerr << "Failed to open the file." << std::endl;
	}
	
	if (c == 'T')
	{
		std::string textureName;
		std::string path;
		float width;
		float height;
		while (f >> textureName >> path >> width >> height)
		{
			m_assets->addTexture(textureName, path, width, height);
		}
	}
	else if(c == 'A')
	{
		std::string animName;
		std::string textureName;
		float vecSizeX;
		float vecSizeY;
		int totalFrame;
		float startPixelX;
		float startPixelY;
		int animSpeed;
		float vecScaleX;
		float vecScaleY;
		int isRepeated;
		int lifespan;
		while (f >> animName >> textureName >> vecSizeX >> vecSizeY >> totalFrame >> startPixelX
			>> startPixelY >>animSpeed >> vecScaleX >> vecScaleY >> isRepeated >> lifespan)
		{
			Animation* a = new Animation(animName, m_assets->getTexture(textureName), 
				Vec2(vecSizeX, vecSizeY), 
				totalFrame, startPixelX, startPixelY, animSpeed, 
				Vec2(vecScaleX, vecScaleY), isRepeated, lifespan);
			m_assets->addAnimation(animName, a);
		}
	}
	else if (c == 'F')
	{
		std::string fontName;
		std::string path;
		while (f >> fontName >> path)
		{
			m_assets->addFont(fontName, path);
		}
	}
	else if (c == 'S')
	{
		std::string soundName;
		std::string path;
		while (f >> soundName >> path)
		{
			m_assets->addSound(soundName, path);
		}
	}
	f.close();

	
}

void Game::run()
{
    while (m_window->isOpen())
    {
		//m_eM.update();
		update();
		sUserInput();
		//scene->test();
		scene->update();
    }
}
void Game::update()
{
	scene = getCurrentScene();
}
void Game::sUserInput()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			close();
		}
		if (!replay_mode && event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (scene->getActionMap().find(event.key.code) != scene->getActionMap().end())
			{
				const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
				scene->sDoAction(Action(scene->getActionMap().at(event.key.code), actionType));
			}

		}
	}
}
void Game::close()
{
	m_window->close();
}

void Game:: resetGameForReplay() {

}







