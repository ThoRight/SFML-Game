#include "Scene_LevelComplete.h"

void Scene_LevelComplete::init()
{
	registerAction(sf::Keyboard::Enter, "Selected");
	registerAction(sf::Keyboard::Down, "Next");
	registerAction(sf::Keyboard::Up, "Previous");

	Entity* e = m_eM.addEntity("Menu");
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("SelectedMenuNewGame"));
	Vec2 pos = Vec2(m_game->getWindow()->getSize().x / 2, m_game->getWindow()->getSize().y / 2);
	e->cTransform = new CTransform(pos, Vec2(0, 0), Vec2(0, 0), 1);
	e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
	e->cState = new CState("NewGame", 1);
	doneMenu = e;

	pointInfo.setFont(*m_game->getAssets()->getFont("Arial"));
	pointInfo.setPosition(Vec2(pos.x / 2, pos.y / 4));
	pointInfo.setOrigin(Vec2(-16, -16));
	pointInfo.setCharacterSize(60);

	buildDoneMenu("NewGame");
}
void Scene_LevelComplete::update()
{
	sAnimation();
	m_eM.update();
	sRender();
}
void Scene_LevelComplete::buildDoneMenu(const std::string& s)
{
	Vec2 pos = doneMenu->cTransform->position;
	doneMenu->cAnimation->animations.clear();
	if (s == "NewGame")
	{
		Animation a1 = *m_game->getAssets()->getAnimation("SelectedMenuNewGame");
		a1.getSprite().setPosition(pos);

		Animation a2 = *m_game->getAssets()->getAnimation("MenuQuit");
		a2.getSprite().setPosition(pos.x, pos.y + 200);

		doneMenu->cAnimation->animations.push_back(a1);
		doneMenu->cAnimation->animations.push_back(a2);
	}
	else if (s == "Quit")
	{
		Animation a1 = *m_game->getAssets()->getAnimation("MenuNewGame");
		a1.getSprite().setPosition(pos);

		Animation a2 = *m_game->getAssets()->getAnimation("SelectedMenuQuit");
		a2.getSprite().setPosition(pos.x, pos.y + 200);

		doneMenu->cAnimation->animations.push_back(a1);
		doneMenu->cAnimation->animations.push_back(a2);
	}
}
void Scene_LevelComplete::sRender()
{
	m_game->getWindow()->clear();
	for (auto& e : m_eM.getEntities("Menu"))
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
	pointInfo.setString("Level Completed\nScore: " + std::to_string(m_game->getPoint()));
	m_game->getWindow()->draw(pointInfo);
	m_game->getWindow()->display();
}
void Scene_LevelComplete::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "Next")
		{
			currentStateIndex = (currentStateIndex + 1) % 2;
			std::string currentState = doneMenuStates[currentStateIndex];
			buildDoneMenu(currentState);
		}
		if (action.name == "Previous")
		{
			if (currentStateIndex == 0)
			{
				currentStateIndex = 1;
			}
			else
			{
				--currentStateIndex;
			}
			std::string currentState = doneMenuStates[currentStateIndex];
			buildDoneMenu(currentState);
		}
		if (action.name == "Selected")
		{
			std::string currentState = doneMenuStates[currentStateIndex];
			if (currentState == "NewGame")
			{
				m_game->changeScene("Play");
			}
			else if (currentState == "Quit")
			{
				m_game->changeScene("Menu");
			}

		}
	}
	/*
	if (action.type == "END")
	{
		if (action.name == "Right")
		{
			m_player->cInput->right = false;
		}
	}
	*/
}
void Scene_LevelComplete::registerAction(int code, const std::string& s)
{
	getActionMap()[code] = s;
}
void Scene_LevelComplete::sAnimation()
{
	for (auto& e : m_eM.getEntities())
	{
		int index = 0;
		for (auto& a : e->cAnimation->animations)
		{
			a.update();
			++index;
		}
		e->cAnimation->destroyFinishedAnim();
	}
}