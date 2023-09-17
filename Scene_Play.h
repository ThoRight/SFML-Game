#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H
#include "Scene.h"
#include "Physics.h"
class Scene_Play :
	public Scene
{
	Entity* m_player = nullptr;
	std::vector<sf::Shape*> m_gridShape;
	std::vector<sf::Text*> m_gridText;
	sf::Text goldInfo;
	int health = 3;
	int m_goldInfo = 0;
	bool m_drawGrid = false;
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
	void tileExplosion(Entity* e);
	void sEnemySpawner(int x);
	void spawnBullet(Entity* e, Vec2& vec);
	void sCollision();
	void sDoAction(const Action& action) override;
public:
	Scene_Play(Game * g) : Scene(g)
	{
		init();
		goldInfo.setFont(*m_game->getAssets()->getFont("Arial"));
		goldInfo.setPosition(Vec2(32, 0));
		goldInfo.setOrigin(Vec2(-16, -16));
		goldInfo.setCharacterSize(32);
	}
	~Scene_Play()
	{
		if(m_player != nullptr)
		{
			delete m_player;
			m_player = nullptr;
		}
		for (auto& g : m_gridShape)
		{
			delete g;
		}
		for (auto& t : m_gridText)
		{
			delete t;
		}
	}
};

#endif


