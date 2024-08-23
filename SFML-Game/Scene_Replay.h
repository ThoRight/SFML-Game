#ifndef SCENE_REPLAY_H
#define SCENE_REPLAY_H
#include "Scene.h"
#include "Physics.h"
#include "Scene_Play.h"
class Scene_Replay :
	public Scene
{
	Entity* m_player = nullptr;
	std::vector<sf::Shape*> m_gridShape;
	std::vector<sf::Text*> m_gridText;
	sf::Text goldInfo;
	sf::Text bulletInfo;
	sf::Text heartInfo;
	sf::Text pointInfo;
	sf::View view;
	sf::View uiView;
	std::map<int, Action> replay;
	sf::Sound sound;
	sf::Sound mainSound;
	Scene_Play* m_scenePlay = nullptr;
	int m_heartNum = 3;
	int m_goldNum = 0;
	int m_bulletNum = 10;
	int m_scenePlayFrame = 0;
	int lastFrame = 0;
	int currentAction = 0;
	bool m_drawGrid = false;
	bool stillDrawGrid = false;
	bool stillPaused = false;
	void registerAction(int code, const std::string& s) override;
	void init();
	void update();
	void loadLevel(const std::string& filename);
	void turnPixelsToSFML(float& x, float& y);
	void createGrid();
	void resolve(Entity* e1, Entity* e2);
	void spawnPlayer();
	void spawnFire();
	void drawGrid()const;
	void sMovement();
	void handleMovementOtherEntities();
	void sUserInput();
	void sRender();
	void sAnimation();
	void hitGoldBox(Entity* e);
	void hitBombBox(Entity* e);
	void sEnemySpawner(int x, int y);
	void sCollision();
	void sDoAction(const Action& action) override;
	void writeActiontoFile(const Action& action, const std::string& filename);
	void readReplay(const std::string& filename);
	void gameOver();
	void completed();
	Entity* getPlayer();
	void resetForReplay();
	void resetScene();
public:
	Scene_Replay(Game* g, Scene* scenePlay) : Scene(g)
	{
		init();
		m_scenePlay = (Scene_Play*)scenePlay;
	}
	~Scene_Replay()
	{
		if (m_player != nullptr)
		{
			delete m_player;
			m_player = nullptr;
		}
		for (auto& g : m_gridShape)
		{
			if (g != nullptr)
			{
				delete g;
				g = nullptr;
			}
		}
		for (auto& t : m_gridText)
		{
			if (t != nullptr)
			{
				delete t;
				t = nullptr;
			}
		}
		sound.stop();
		mainSound.stop();
	}
};

#endif


