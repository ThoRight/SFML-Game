#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <map>
#include "Entity.h"
class EntityManager
{
	std::vector<Entity*> m_entities;
	std::map<std::string, std::vector<Entity*>> m_entityMap;
	std::vector<Entity*> m_toAdd;
	size_t m_totalEntities=1;
public:
	void update();
	Entity* addEntity(const std::string& tag);
	std::vector<Entity*>& getEntities();
	std::vector<Entity*>& getEntities(const std::string& tag);
};

#endif

