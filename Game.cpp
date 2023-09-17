#include "Scene_Play.h"

void Game::init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "SFML works!");
	m_assets = new Assets();
	m_window->setFramerateLimit(60);
	loadFromFile("./Assets/Textures.txt", 'T');
	loadFromFile("./Assets/Animations.txt", 'A');
	loadFromFile("./Assets/Fonts.txt", 'F');
	// LOAD ASSETS.
	// INIT. SCENE.
	Scene* s1 = new Scene_Play(this);
	//	Scene* s2 = new Scene_Play(this);
	//	Scene* s3 = new Scene_Play(this);
	m_sceneMap["Play"] = s1;
	changeScene("Play");
}
void Game::changeScene(const std::string& newScene)
{
	currentScene = newScene;
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
			m_assets->addFont(fontName,path);
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
			quit();
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (scene->getActionMap().find(event.key.code) != scene->getActionMap().end())
			{
				const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
				scene->sDoAction(Action(scene->getActionMap().at(event.key.code), actionType));
			}

		}
	}
}
void Game::quit()
{
	m_window->close();
}







