#include "Scene_Menu.h"
void Scene_Menu::init()
{
	registerAction(sf::Keyboard::Enter, "Selected");
	registerAction(sf::Keyboard::Down, "Next");
	registerAction(sf::Keyboard::Up, "Previous");

	Entity* e = m_eM.addEntity("Menu");
	e->cAnimation = new CAnimation(*m_game->getAssets()->getAnimation("SelectedMenuPlay"));
	Vec2 pos = Vec2(m_game->getWindow()->getSize().x/2, m_game->getWindow()->getSize().y/2);
	e->cTransform = new CTransform(pos, Vec2(0, 0), Vec2(0, 0), 1);
	e->cAnimation->animations[0].getSprite().setPosition(e->cTransform->position);
	e->cState = new CState("Play", 1);
	menu = e;
	buildMenu("Play");
}
void Scene_Menu::update()
{
	sAnimation();
	m_eM.update();
	sRender();
}
void Scene_Menu::buildMenu(const std::string& s)
{
	Vec2 pos = menu->cTransform->position;
	std::cout << "\n" << pos.x << " " << pos.y << "\n";
	menu->cAnimation->animations.clear();
	if (s == "Play")
	{
		Animation a1 = *m_game->getAssets()->getAnimation("SelectedMenuPlay");
		a1.getSprite().setPosition(pos);

		Animation a2 = *m_game->getAssets()->getAnimation("MenuExit");
		a2.getSprite().setPosition(pos.x, pos.y + 200);

		menu->cAnimation->animations.push_back(a1);
		menu->cAnimation->animations.push_back(a2);
	}
	else if (s == "Exit")
	{
		Animation a1 = *m_game->getAssets()->getAnimation("MenuPlay");
		a1.getSprite().setPosition(pos);

		Animation a2 = *m_game->getAssets()->getAnimation("SelectedMenuExit");
		a2.getSprite().setPosition(pos.x, pos.y + 200);

		menu->cAnimation->animations.push_back(a1);
		menu->cAnimation->animations.push_back(a2);
	}
}
void Scene_Menu::sRender()
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
	m_game->getWindow()->display();
}
void Scene_Menu::sDoAction(const Action& action)
{
	if (action.type == "START")
	{
		if (action.name == "Next")
		{
			currentStateIndex = (currentStateIndex + 1) % 2;
			std::string currentState = menuStates[currentStateIndex];
			buildMenu(currentState);
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
			std::string currentState = menuStates[currentStateIndex];
			buildMenu(currentState);
		}
		if (action.name == "Selected")
		{
			std::string currentState = menuStates[currentStateIndex];
			if (currentState == "Play")
			{
				m_game->changeScene("Play");
			}
			else if (currentState == "Exit")
			{
				//m_game->changeScene("Replay");
				m_game->close();
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
void Scene_Menu::registerAction(int code, const std::string& s)
{
	getActionMap()[code] = s;
}
void Scene_Menu::sAnimation()
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
