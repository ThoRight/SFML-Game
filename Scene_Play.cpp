#include "Scene_Play.h"
#include <iostream>

void Scene_Play::spawnPlayer()
{
	Entity* e = m_eM.addEntity("Player");
	e->cTransform = new CTransform(Vec2(50, 110), Vec2(0, 0), Vec2(0, 0), -5);
	e->cInput = new CInput();
	e->cGravity = new CGravity(0.2);
	e->cBoundingBox = new CBoundingBox(Vec2(60, 60));
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandRight"));
	e->cState = new CState("StandRight",true);
	m_player = e;
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
}

void Scene_Play::sEnemySpawner(int x)
{
	Entity* e = m_eM.addEntity("Enemy");
	e->cTransform = new CTransform(Vec2(x, 100), Vec2(0, 0), Vec2(0, 0), -5);
	e->cBoundingBox = new CBoundingBox(Vec2(30, 50));
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandRightE"));
	e->cGravity = new CGravity(0.2);
}

void Scene_Play::registerAction(int code, const std::string& s)
{
	getActionMap()[code] = s;
}

void Scene_Play::init()
{
	sEnemySpawner(150);
	spawnPlayer();
	sEnemySpawner(300);
	sEnemySpawner(400);
	loadLevel("./Assets/Level.txt");
	createGrid();
	registerAction(sf::Keyboard::D, "Right");
	registerAction(sf::Keyboard::A, "Left");
	registerAction(sf::Keyboard::S, "Down");
	registerAction(sf::Keyboard::W, "Jump");
	registerAction(sf::Keyboard::G, "Grid");
	registerAction(sf::Keyboard::Space, "Fire");
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
		if (action.name == "Grid")
		{
			m_drawGrid = !m_drawGrid;
		}
		if (action.name == "Jump" && m_player->cTransform->speed.y == 0)
		{
			m_player->cInput->jump = true;
		}
		if (action.name == "Fire" && !m_player->cInput->fire)
		{
			m_player->cInput->fire = true;
			spawnFire();
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

	}
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
		Entity* e = m_eM.addEntity(entityName);
		e->cTransform = new CTransform(Vec2(x,y), Vec2(0, 0), Vec2(0, 0), -5);
		e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation(animName));
		e->cState = new CState(animName,x==1);
		if(entityName != "Decor")
		e->cBoundingBox = new CBoundingBox(Vec2(vecSizeX,vecSizeY));
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
	sRender();
	++m_currentFrame;
	
}
void Scene_Play::sAnimation()
{
	
	if (m_player->cTransform->speed.y != 0)
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
		for (auto& a : e->cAnimation->animations)
		{
			if (e->getTag() == "Enemy" && a.hasEnded())
			{
				e->cAnimation->animations[0] = m_game->getAssets()->getAnimation("StandRightE");
			}
			a.update();
		}
		e->cAnimation->destroyFinishedAnim();
	}
}
void Scene_Play::sMovement()
{
	for (auto& e : m_eM.getEntities("Player"))
	{
		e->cTransform->speed.y += e->cGravity->gravity;
		m_player->cTransform->speed.x = 0;
	}
	if (m_player->cInput->jump)
	{
		m_player->cTransform->speed.y = -5;
		m_player->cInput->jump = false;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->speed.x = 5;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->speed.x = -5;
	}
	for (auto& e : m_eM.getEntities("Player"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			// do the right animations.
		}
		if (e->cTransform->position.y > m_game->getWindow()->getSize().y)
		{
			e->destroy();
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
			//do the right animations.
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
			// do the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Tile"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			// do the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Decor"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			// do the right animations.
		}
	}
	for (auto& e : m_eM.getEntities("Coin"))
	{
		e->cTransform->prevPosition = e->cTransform->position;
		e->cTransform->position += e->cTransform->speed;
		e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
		for (auto& a : e->cAnimation->animations)
		{
			// do the right animations.
		}
	}

}
void Scene_Play::sRender()
{
	m_game->getWindow()->clear(sf::Color(21,5,159));
	//m_game->getWindow()->clear();
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
				//std::cout << "\n print \n";
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
	goldInfo.setString("x"+std::to_string(m_goldInfo));
	m_game->getWindow()->draw(goldInfo);
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
	if (n1 == "Fire" && n2 != "Player" && n2 != "Coin")
	{
		e1->destroy();
		std::cout << "\nBANNG\n";
		if (e2->getTag() == "Enemy")
		{
			delete e2->cBoundingBox;
			e2->cBoundingBox = nullptr;
			e2->cGravity->gravity = 0;
			e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DestroyEnemy");
			e2->cLifespan = new CLifespan(60);
		}
	}
	else if (n1 == "Player" && n2 == "Coin")
	{
		std::cout << "\nCOIN TAKEN\n";
		++m_goldInfo;
		e2->destroy();
	}
	else if (n1 == "Player" && n2 == "Enemy")
	{
		if (e2->cAnimation->animations[0].getName() != "DestroyEnemy")
		{
			e2->cAnimation->animations[0] = m_game->getAssets()->getAnimation("DestroyEnemy");
			health--;
			std::cout << health;
		}
	}
	else if (n1 == "Player" && n2 != "Fire" || n1 == "Enemy" && n2 != "Player" && n2 != "Coin")
	{
		if (preX > 0)
		{
			if (e1->cTransform->position.y - e1->cTransform->prevPosition.y < 0)
			{
				e1->cTransform->position.y += y;
				e1->cTransform->speed.y = 0;
				if (n1 == "Player" && n2 == "Tile")
				{
					tileExplosion(e2);
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
			}
			else if ((e1->cTransform->position.x - e1->cTransform->prevPosition.x > 0))
			{
				e1->cTransform->position.x -= x;
				if (n1 == "Player")
					std::cout << "\nWorks\n";
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
	int width = m_game->getWindow()->getPosition().x;
	int height = m_game->getWindow()->getPosition().y;
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

void Scene_Play::tileExplosion(Entity* e)
{
	Entity* e2 = m_eM.addEntity("DestroyEnemy");
	e2->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("DestroyEnemy"));
	e2->cTransform = new CTransform(e->cTransform->position + Vec2(0, -e->cBoundingBox->size.y / 2), Vec2(0, 0), Vec2(1, 1), -5);
	e2->cLifespan = new CLifespan(60);
	
	Entity* e3 = m_eM.addEntity("Tile");
	e3->cTransform = new CTransform(e->cTransform->position, Vec2(0, 0), Vec2(0, 0), -5);
	e3->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("StandTile2"));
	e3->cState = new CState("StandTile2",1);
	e3->cBoundingBox = new CBoundingBox(Vec2(64, 64));
	e->destroy();
}
