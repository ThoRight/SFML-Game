#include "Scene_Play.h"
#include <iostream>

void Scene_Play::spawnPlayer()
{
	Entity* e = m_eM.addEntity("Player");
	e->cTransform = new CTransform(Vec2(50, 110), Vec2(0, 0), Vec2(0, 0), -5);
	e->cInput = new CInput();
	e->cGravity = new CGravity(0.2);
	e->cBoundingBox = new CBoundingBox(Vec2(46, 50));
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandRight"));
	e->cState = new CState("StandRight",true);
	m_player = e;
	
	
	//m_player->cAnimation->animations.push_back(*m_game->getAssets()->getAnimation("RobeRight"));
}
void Scene_Play::spawnFire()
{
	Entity* e = m_eM.addEntity("Fire");
	Vec2 fireSpeed(0, 0);
	Vec2 firePos(0, 0);
	firePos = m_player->cTransform->position;
	if (m_player->cState->dirRight)
	{
		fireSpeed.x += 8;
		firePos.x += 10;
	}
	else
	{
		fireSpeed.x -= 8;
		firePos.x -= 10;
	}
	e->cTransform = new CTransform(firePos, fireSpeed, Vec2(0, 0), -5);
	e->cBoundingBox = new CBoundingBox(Vec2(16, 16));
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("Fire"));
	e->cLifespan = new CLifespan(120);
	--m_bulletNum;
}

void Scene_Play::sEnemySpawner(int x, int y)
{
	Entity* e = m_eM.addEntity("Enemy");
	e->cTransform = new CTransform(Vec2(x, y), Vec2(2, 2), Vec2(0, 0), -5);
	e->cBoundingBox = new CBoundingBox(Vec2(60, 60));
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("RunRightE"));
	e->cState = new CState("RunRightE", true);
	e->cGravity = new CGravity(0.2);
}

void Scene_Play::registerAction(int code, const std::string& s)
{
	getActionMap()[code] = s;
}

void Scene_Play::init()
{
	int m_heartNum = 3;
	int m_goldNum = 0;
	int m_bulletNum = 10;
	int m_scenePlayFrame = 0;
	int currentAction = 0;
	bool m_paused = false;
	bool stillPaused = false;
	bool m_drawGrid = false;
	bool stillDrawGrid = false;

	std::ofstream file("Replay.txt", std::ios::trunc);
	std::cout << "File has been emptied successfully." << std::endl;
	file.close();

	view.setSize(m_game->getWindow()->getSize().x, m_game->getWindow()->getSize().y);
	uiView = sf::View(sf::FloatRect(0, 0, m_game->getWindow()->getSize().x, m_game->getWindow()->getSize().y));
	pointInfo.setFont(*m_game->getAssets()->getFont("Arial"));
	pointInfo.setPosition(Vec2(m_game->getWindow()->getSize().x-64, 0));
	pointInfo.setOrigin(Vec2(-16, -16));
	pointInfo.setCharacterSize(25);

	heartInfo.setFont(*m_game->getAssets()->getFont("Arial"));
	heartInfo.setPosition(Vec2(32, 0));
	heartInfo.setOrigin(Vec2(-16, -16));
	heartInfo.setCharacterSize(25);
	
	goldInfo.setFont(*m_game->getAssets()->getFont("Arial"));
	goldInfo.setPosition(Vec2(32, 64));
	goldInfo.setOrigin(Vec2(-16, -16));
	goldInfo.setCharacterSize(25);
	
	bulletInfo.setFont(*m_game->getAssets()->getFont("Arial"));
	bulletInfo.setPosition(Vec2(32, 128));
	bulletInfo.setOrigin(Vec2(-16, -16));
	bulletInfo.setCharacterSize(25);
	
	mainSound.setBuffer(*m_game->getAssets()->getSound("Ambience"));
	mainSound.setLoop(true);
	mainSound.play();

	spawnPlayer();
	
	loadLevel("./Assets/Level.txt");
	createGrid();
	registerAction(sf::Keyboard::D, "Right");
	registerAction(sf::Keyboard::A, "Left");
	registerAction(sf::Keyboard::S, "Down");
	registerAction(sf::Keyboard::W, "Jump");
	registerAction(sf::Keyboard::G, "Grid");
	registerAction(sf::Keyboard::Space, "Fire");
	registerAction(sf::Keyboard::P, "Pause");
	registerAction(sf::Keyboard::R, "Replay");
	registerAction(sf::Keyboard::Escape, "Quit");
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "Right")
		{
			m_player->cState->dirRight = true;
			m_player->cInput->right = true;
			m_player->cInput->left = false;
		}
		if (action.name == "Left")
		{
			m_player->cState->dirRight = false;
			m_player->cInput->left = true;
			m_player->cInput->right = false;
		}
		if (action.name == "Grid" && !stillDrawGrid)
		{
			std::cout << "\nGRIDIDID\n";
			m_drawGrid = !m_drawGrid;
			stillDrawGrid = true;
		}
		if (action.name == "Jump" && m_player->cTransform->speed.y == 0)
		{
			m_player->cInput->jump = true;
		}
		if (action.name == "Fire" && !m_player->cInput->fire && m_bulletNum > 0)
		{
			m_player->cInput->fire = true;
			spawnFire();
			sound.setBuffer(*m_game->getAssets()->getSound("Fire"));
			sound.play();
		}
		if (action.name == "Pause" && !stillPaused)
		{
			m_paused = !m_paused;
			stillPaused = true;
		}
		if (action.name == "Replay")
		{
			std::cout << "\n" << m_game->isReplay() << "\n";
			m_game->setReplay(!m_game->isReplay());
			std::cout << "\n" << m_game->isReplay() << "\n";
			m_game->changeScene("Replay");
		}
		if (action.name == "Quit")
		{
			m_game->changeScene("Menu");
		}
	}
	if (action.type == "END")
	{
		if (action.name == "Right")
		{
			m_player->cInput->right = false;
		}
		if (action.name == "Left")
		{
			m_player->cInput->left = false;
		}
		if (action.name == "Jump")
		{
			m_player->cInput->jump = false;
		}
		if (action.name == "Fire")
		{
			m_player->cInput->fire = false;
		}
		if (action.name == "Pause")
		{
			stillPaused = false;
		}
		if (action.name == "Grid")
		{
			stillDrawGrid = false;
		}

	}
	if (!m_game->isReplay()) {
		writeActiontoFile(action, "Replay.txt");
	}
}
void Scene_Play::writeActiontoFile(const Action& action, const std::string& filename)
{
	std::ofstream f;
	f.open(filename, std::ios_base::app);
	f << m_scenePlayFrame << " " << action.type << " " << action.name << "\n";
	f.close();
}
void Scene_Play::loadLevel(const std::string& filename)
{
	std::ifstream f(filename);
	std::string entityName;
	std::string animName;
	float vecSizeX;
	float vecSizeY;
	float x;
	float y;
	while (f >> entityName >> animName >>vecSizeX >> vecSizeY  >> x >> y)
	{
		turnPixelsToSFML(x,y);
		if (entityName == "Enemy")
		{
			sEnemySpawner(x, y);
		}
		else
		{
			Entity* e = m_eM.addEntity(entityName);
			e->cTransform = new CTransform(Vec2(x, y), Vec2(0, 0), Vec2(0, 0), -5);
			e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation(animName));
			e->cState = new CState(animName, x == 1);
			if (entityName != "Decor" && entityName != "UI")
				e->cBoundingBox = new CBoundingBox(Vec2(vecSizeX, vecSizeY));
		}
		
	}
	f.close();
}
void Scene_Play::turnPixelsToSFML(float& x, float& y)
{
	y *= 64;
	x *= 64;
	y += 32;
	x += 32;
	y = m_game->getWindow()->getSize().y - y;
	
}	


void Scene_Play::update()
{
	if (m_heartNum == 0)
	{
		gameOver();
	}
	if (m_player->cTransform->position.x > 768)
		completed();
	/*
	if (m_game->isReplay())
	{
		m_game->resetGameForReplay();
		readReplay("Replay.txt");
		if (replay.find(m_scenePlayFrame) != replay.end())
		{
			sDoAction(replay[m_scenePlayFrame]);
			std::cout << "\n" << replay[m_scenePlayFrame].name << "\n";
		}
		else {
			std::cout << "\nTest\n";
			m_game->setReplay(false);
		}
	}
	*/
	if (!m_paused)
	{
		if (!m_player->isActive())
		{
			m_eM.update();
			spawnPlayer();
			m_eM.update();
		}
		else
		{
			m_eM.update();
		}
		sAnimation();
		sMovement();
		sCollision();
		++m_currentFrame;
		++m_scenePlayFrame;
	}

	//view.setCenter(m_player->cTransform->position);
	view.setCenter(m_player->cTransform->position.x,m_game->getWindow()->getSize().y/2);
	sRender();
}
void Scene_Play::readReplay(const std::string& filename)
{
	std::ifstream f(filename);
	int frameNum;
	std::string aType;
	std::string aName;
	int index = 0;
	while (f >> frameNum >> aType >> aName)
	{
		Action a(aName, aType);
		replay[frameNum] = a;
	}
	f.close();
}
void Scene_Play::sAnimation()
{
	if (m_player->cInput->fire)
	{
		if (m_player->cState->dirRight)
		{
			m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("FireRight");
		}
		else
		{
			m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("FireLeft");
		}
	}
	else if (m_player->cTransform->speed.y != 0)
	{
		if (m_player->cState->dirRight)
		{
			if (m_player->cState->name != "JumpRight")
			{
				m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("JumpRight");
				m_player->cState->name = "JumpRight";
			}
		}
		else
		{
			if (m_player->cState->name != "JumpLeft")
			{
				m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("JumpLeft");
				m_player->cState->name = "JumpLeft";
			}
		}
		
	}
	else
	{
		if (m_player->cInput->right)
		{
			if (m_player->cState->name != "RunRight")
			{
				m_player->cAnimation->animations[0] = *m_game->getAssets()->getAnimation("RunRight");
				m_player->cState->name = "RunRight";
			}
		}
		else if (m_player->cInput->left)
		{
			if (m_player->cState->name != "RunLeft")
			{
				m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("RunLeft");
				m_player->cState->name = "RunLeft";
			}
		}
		else
		{
			if (m_player->cState->dirRight)
			{
				if (m_player->cState->name != "StandRight")
				{
					m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("StandRight");
					m_player->cState->name = "StandRight";
				}
			}
			else
			{
				if (m_player->cState->name != "StandLeft")
				{
					m_player->cAnimation->animations[0] = m_game->getAssets()->getAnimation("StandLeft");
					m_player->cState->name = "StandLeft";
				}
			}
		}
	}
	for (auto& e : m_eM.getEntities())
	{
		int index = 0;
		for (auto& a : e->cAnimation->animations)
		{
			if (e->getTag() == "Enemy" && a.hasEnded() && e->isActive())
			{
				;
			}
			if (e->getTag() == "Player" && a.hasEnded() && (a.getName() == "FireRight" || a.getName() == "FireLeft"))
			{
				e->cAnimation->animations[0] = m_game->getAssets()->getAnimation(e->cState->name);
			}
			if (e->getTag() == "Enemy")
			{
				if (e->cState->dirRight && e->cState->name == "RunLeftE")
				{
					e->cState->name = "RunRightE";
					e->cAnimation->animations[0] = m_game->getAssets()->getAnimation("RunRightE");
				}
				else if(!e->cState->dirRight && e->cState->name == "RunRightE")
				{
					e->cState->name = "RunLeftE";
					e->cAnimation->animations[0] = m_game->getAssets()->getAnimation("RunLeftE");
				}
			}
			a.update();
			++index;
		}
		e->cAnimation->destroyFinishedAnim();
	}
}
void Scene_Play::sMovement()
{
	/*
	for (auto& e : m_eM.getEntities("Player"))
	{
		m_player->cTransform->speed.x = 0;
	} check
	*/
	if (m_player->cInput->jump)
	{
		m_player->cTransform->speed.y = -8;
		m_player->cInput->jump = false;
	}
	else if (m_player->cInput->right)
	{
		if (m_player->cTransform->speed.x <= 0)
		{
			m_player->cTransform->speed.x = 2;
		}
		if (m_player->cTransform->speed.x < 5)
		{
			m_player->cTransform->speed.x+=0.1;
		}
	}
	else if (m_player->cInput->left)
	{
		if (m_player->cTransform->speed.x >= 0)
		{
			m_player->cTransform->speed.x = -2;
		}
		if (m_player->cTransform->speed.x > -5)
		{
			m_player->cTransform->speed.x -= 0.1;
		}
	}
	else
	{
		m_player->cTransform->speed.x = 0;
	}
	for (auto& e : m_eM.getEntities("Player"))
	{
		e->cTransform->speed.y += e->cGravity->gravity;
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{

			if(a.getName() == "Hit")
			{
				std::cout << "\nHÝYYY\n";
				a.getSprite().setPosition(e->cTransform->position + Vec2(0,-90));
				if(a.hasEnded())
				{
					a.setDeleted(true);
				}
			}
			/*
			if (a.getName() == "RobeStand" || a.getName() == "RobeRight" || a.getName() == "RobeLeft")
			{
				a.getSprite().setPosition(e->cTransform->position);
			}
			*/
			//implement the right animations.
		}
		if (e->cTransform->position.y > m_game->getWindow()->getSize().y)
		{
			e->destroy();
			--m_heartNum;
		}
	}
	handleMovementOtherEntities();
}
void Scene_Play::handleMovementOtherEntities()
{
	for (auto& e : m_eM.getEntities("Enemy"))
	{
		e->cTransform->speed.y += e->cGravity->gravity;
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
		if (e->cTransform->position.y > m_game->getWindow()->getSize().y)
		{
			e->destroy();
		}
	}
	for (auto& e : m_eM.getEntities("Fire"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Tile"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			if (a.getName() == "StandCoin")
			{
				Vec2 pos = a.getSprite().getPosition();
				pos.y -= 10;
				a.getSprite().setPosition(pos);
			}
			//implement the right animations..
		}
	}
	for (auto& e : m_eM.getEntities("Decor"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Heart"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Coin"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("GoldBox"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("BombBox"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("UI"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			//implement the right animations.
		}
	}

}
void Scene_Play::sRender()
{
	//m_game->getWindow()->clear(sf::Color(21,5,159));
	m_game->getWindow()->clear();

	m_game->getWindow()->setView(uiView);
	for (auto& e : m_eM.getEntities("UI"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	pointInfo.setString(std::to_string(m_game->getPoint()));
	m_game->getWindow()->draw(pointInfo);

	goldInfo.setString("x" + std::to_string(m_goldNum));
	m_game->getWindow()->draw(goldInfo);

	bulletInfo.setString("x" + std::to_string(m_bulletNum));
	m_game->getWindow()->draw(bulletInfo);

	heartInfo.setString("x" + std::to_string(m_heartNum));
	m_game->getWindow()->draw(heartInfo);

	m_game->getWindow()->setView(view);

	for (auto& e : m_eM.getEntities("Decor"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Tile"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Enemy"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Fire"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Heart"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Coin"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("GoldBox"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("BombBox"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	for (auto& e : m_eM.getEntities("Player"))
	{
		if (e->cLifespan != nullptr && e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			if (e->cLifespan != nullptr)
			{
				e->cLifespan->remaining -= 1;
			}
			for (auto& a : e->cAnimation->animations)
			{
				m_game->getWindow()->draw(a.getSprite());
			}
		}
	}
	if (m_drawGrid)
	{
		drawGrid();
	}
	m_game->getWindow()->setView(uiView);
	m_game->getWindow()->display();

}
void Scene_Play::sCollision()
{
	Physics p;
	for (auto& e1 : m_eM.getEntities())
	{
		for (auto& e2 : m_eM.getEntities())
		{
			if (e1->getId() != e2->getId() && e1->cBoundingBox != nullptr && e2->cBoundingBox != nullptr)
			{
				if (p.isCollision(e1, e2))
				{
					resolve(e1, e2);
				}
			}
		}
	}
	
}


void Scene_Play::resolve(Entity* e1, Entity* e2)
{
	std::string n1 = e1->getTag();
	std::string n2 = e2->getTag();
	float preX = e1->cBoundingBox->preOverlapX;
	float preY = e1->cBoundingBox->preOverlapY;
	float x = e1->cBoundingBox->overlapX;
	float y = e1->cBoundingBox->overlapY;
	if (n1 == "Fire" && n2 != "Player" && n2 != "Coin" && n2 != "Heart")
	{
		e1->destroy();
		if (e2->getTag() == "Enemy")
		{
			m_game->addPoint(10);
			delete e2->cBoundingBox;
			e2->cBoundingBox = nullptr;
			e2->cTransform->speed = { 0,0 };
			e2->cGravity->gravity = 0;
			if (e2->cState->dirRight)
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieRightE");
			else
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieLeftE");
			e2->cState->name = "DieE";
			e2->cLifespan = new CLifespan(180);
		}
	}
	else if (n1 == "Player" && n2 == "Coin")
	{
		sound.setBuffer(*m_game->getAssets()->getSound("CoinPickUp"));
		sound.play();
		++m_goldNum;
		e2->destroy();
	}
	else if (n1 == "Player" && n2 == "Heart")
	{
		++m_heartNum;
		e2->destroy();
	}
	else if (n1 == "Player" && n2 == "Enemy")
	{
		if (preX > 0)
		{
			m_game->addPoint(10);
			std::cout << "\nDETECTED\n";
			m_player->cInput->jump = true;
			delete e2->cBoundingBox;
			e2->cBoundingBox = nullptr;
			e2->cTransform->speed = { 0,0 };
			e2->cGravity->gravity = 0;
			if(e2->cState->dirRight)
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieRightE");
			else
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieLeftE");
			e2->cState->name = "DieE";
			e2->cLifespan = new CLifespan(180);
		}
		else if (preY > 0)
		{
			std::cout << "\nDETECTED2\n";
			m_player->cInput->jump = true;
			--m_heartNum;
			Animation a = *m_game->getAssets()->getAnimation("Hit");
			e1->cAnimation->animations.push_back(a);
			delete e2->cBoundingBox;
			e2->cBoundingBox = nullptr;
			e2->cTransform->speed = { 0,0 };
			e2->cGravity->gravity = 0;
			if (e2->cState->dirRight)
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieRightE");
			else
				e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DieLeftE");
			e2->cState->name = "DieE";
			e2->cLifespan = new CLifespan(180);
		}
	}
	else if (n1 == "Player" && n2 != "Fire" || n1 == "Enemy" && n2 != "Player" && n2 != "Coin"  && n2 != "Heart"  && n2 != "Enemy")
	{
		if (preX > 0)
		{
			if (e1->cTransform->position.y - e1->cTransform->prevPosition.y < 0)
			{
				e1->cTransform->position.y += y;
				e1->cTransform->speed.y = 0;
				if (n1 == "Player" && n2 == "GoldBox")
				{
					sound.setBuffer(*m_game->getAssets()->getSound("CoinPickUp"));
					sound.play();
					++m_goldNum;
					hitGoldBox(e2);
				}
				if (n1 == "Player" && n2 == "BombBox")
				{
					sound.setBuffer(*m_game->getAssets()->getSound("Explosion"));
					sound.play();
					--m_heartNum;
					hitBombBox(e2);
				}
			}
			else if (e1->cTransform->position.y - e1->cTransform->prevPosition.y >= 0)
			{
				e1->cTransform->position.y -= y;
				e1->cTransform->speed.y = 0;
			}
		}
		else if (preY > 0)
		{
			if (e1->cTransform->position.x - e1->cTransform->prevPosition.x < 0)
			{
				e1->cTransform->position.x += x;
				if (n1 == "Enemy")
				{
					e1->cTransform->speed.y = -e1->cTransform->speed.y;
					e1->cTransform->speed.x = -e1->cTransform->speed.x;
					e1->cState->dirRight = !e1->cState->dirRight;
				}
			}
			else if ((e1->cTransform->position.x - e1->cTransform->prevPosition.x > 0))
			{
				e1->cTransform->position.x -= x;
				if (n1 == "Enemy")
				{
					e1->cTransform->speed.y = -e1->cTransform->speed.y;
					e1->cTransform->speed.x = -e1->cTransform->speed.x;
					e1->cState->dirRight = !e1->cState->dirRight;
				}
			}
		}
	}

	
}
void Scene_Play::drawGrid()const
{
	for (auto& s : m_gridShape)
	{
		m_game->getWindow()->draw(*s);
	}
	for (auto& s : m_gridText)
	{
		m_game->getWindow()->draw(*s);
	}
}

void Scene_Play::createGrid()
{
	int width = m_game->getWindow()->getSize().x/64*4;
	int height = m_game->getWindow()->getSize().y/64;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			float x = j;
			float y = i;
			turnPixelsToSFML(x, y);
			sf::RectangleShape* s = new sf::RectangleShape(Vec2(62, 62));
			s->setFillColor(sf::Color(0, 0, 0, 0));
			s->setOutlineThickness(2);
			s->setOutlineColor(sf::Color(255, 0, 0));
			s->setOrigin(32, 32);
			s->setPosition(Vec2(x, y));
			m_gridShape.push_back(s);

			sf::Text* t = new sf::Text();
			t->setFont(*m_game->getAssets()->getFont("Arial"));
			t->setCharacterSize(20);
			t->setFillColor(sf::Color::Red);
			std::string text = std::to_string(j) + "," + std::to_string(i);
			t->setString(text);
			t->setOrigin(10, 10);
			t->setPosition(x, y);
			m_gridText.push_back(t);
		}
	}
}

void Scene_Play::hitGoldBox(Entity* e)
{
	Entity* e2 = m_eM.addEntity("Tile");
	e2->cTransform = new CTransform(e->cTransform);
	e2->cBoundingBox = new CBoundingBox(Vec2(64,64));
	e2->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandGoldBoxDone"));
	e->destroy();

	Animation a = *m_game->getAssets()->getAnimation("StandCoin");
	a.setLifespan(2);
	a.getSprite().setPosition(e->cTransform->position);
	e2->cAnimation->animations.push_back(a);
}
void Scene_Play::hitBombBox(Entity* e)
{
	Entity* e2 = m_eM.addEntity("Tile");
	e2->cTransform = new CTransform(e->cTransform);
	e2->cBoundingBox = new CBoundingBox(Vec2(64, 64));
	e2->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandBombBoxDone"));
	e->destroy();

	Animation a = *m_game->getAssets()->getAnimation("DestroyEnemy");
	a.setLifespan(13);
	a.getSprite().setPosition(e->cTransform->position+Vec2(0,-45));
	e2->cAnimation->animations.push_back(a);

	Animation a2 = *m_game->getAssets()->getAnimation("Hit");
	m_player->cAnimation->animations.push_back(a2);
	/*
	Entity* e2 = m_eM.addEntity("DestroyEnemy");
	e2->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("DestroyEnemy"));
	e2->cTransform = new CTransform(e->cTransform->position, Vec2(0, 0), Vec2(1, 1), -5);
	e2->cLifespan = new CLifespan(600);

	Entity* e3 = m_eM.addEntity("Tile");
	e3->cTransform = new CTransform(e->cTransform->position, Vec2(0, 0), Vec2(0, 0), -5);
	e3->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandBombBoxDone"));
	e3->cState = new CState("StandBombBoxDone", 1);
	e3->cBoundingBox = new CBoundingBox(Vec2(64, 64));
	e->destroy();
	*/
}

void Scene_Play::gameOver()
{
	m_game->changeScene("GameOver");
}
void Scene_Play::completed()
{
	m_game->changeScene("LevelComplete");
}
Entity* Scene_Play::getPlayer() {
	return m_player;
}

void Scene_Play:: resetForReplay() {
}
