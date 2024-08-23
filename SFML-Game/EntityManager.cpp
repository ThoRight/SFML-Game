#include "EntityManager.h"
/*
void EntityManager::update()
{
	std::vector<Entity*> toDelete;
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	m_toAdd.clear();
	for (auto& e : m_entities)
	{
		if (!e->isActive())
		{
			toDelete.push_back(e);
		}
	}

	for (auto& m : m_entityMap)
	{
			m.second.erase(std::remove_if(m.second.begin(), m.second.end(),
				[](Entity* e) { return !e->isActive(); }), m.second.end());
	}

	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
		[](Entity* e) { return!e->isActive(); }), m_entities.end());
	std::cout << "size: " << toDelete.size() << "\n";
	for (auto& e : toDelete)
	{
		if (e != nullptr)
		{
			delete e;
			e = nullptr;
		}
	}
	

}
*/
void EntityManager::update()
{
	std::vector<Entity*> toDelete;

	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	m_toAdd.clear();

	for (auto& e : m_entities)
	{
		if (!e->isActive())
		{
			toDelete.push_back(e);
		}
	}

	for (auto& m : m_entityMap)
	{
		m.second.erase(std::remove_if(m.second.begin(), m.second.end(),
			[](Entity* e) { return !e->isActive(); }), m.second.end());
	}

	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
		[](Entity* e) { return !e->isActive(); }), m_entities.end());


	for (auto& e : toDelete)
	{
		if (e != nullptr)
		{
			delete e;
			e = nullptr; // Nullify the pointer after deletion
		}
	}
}
Entity* EntityManager::addEntity(const std::string& tag)
{
	Entity* e = new Entity(tag, m_totalEntities++);
	m_toAdd.push_back(e);
	return e;
}
std::vector<Entity*>& EntityManager::getEntities()
{
	return m_entities;
}
std::vector<Entity*>& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}