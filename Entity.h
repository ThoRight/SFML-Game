#ifndef  ENTITY_H
#define ENTITY_H


#include <string>
#include "Action.h"


class Entity
{
	friend class entityManager;
	std::string m_tag;
	size_t m_id;
	bool m_active;

public:
	CTransform* cTransform = nullptr;
	CBoundingBox* cBoundingBox = nullptr;
	CInput* cInput = nullptr;
	CScore* cScore = nullptr;
	CLifespan* cLifespan = nullptr;
	CAnimation* cAnimation = nullptr;
	CGravity* cGravity = nullptr;
	CState* cState = nullptr;
	Entity(const std::string& tag, size_t id)
	{
		m_tag = tag;
		m_id = id;
		m_active = true;
	}
	void destroy();
	bool isActive()
	{
		return m_active;
	}
	std::string& getTag()
	{
		return m_tag;
	}
	void setTag(const std::string& s)
	{
		m_tag = s;
	}
	size_t getId()
	{
		return m_id;
	}
	~Entity()
	{
		std::cout << "\nDESTROY ENTITY\n";
		if (cTransform != nullptr)
		{
			delete cTransform;
			cTransform = nullptr;
		}
		if (cBoundingBox!= nullptr)
		{
			delete cBoundingBox;
			cBoundingBox= nullptr;
		}
		if (cInput != nullptr)
		{
			delete cInput;
			cInput = nullptr;
		}
		if (cScore != nullptr)
		{
			delete cScore;
			cScore = nullptr;
		}
		if (cLifespan != nullptr)
		{
			delete cLifespan;
			cLifespan = nullptr;
		} 
		if (cAnimation != nullptr)
		{
			delete cAnimation;
			cAnimation = nullptr;
		}
		if (cGravity != nullptr)
		{
			delete cGravity;
			cGravity = nullptr;
		}
		if (cState != nullptr)
		{
			delete cState;
			cState = nullptr;
		}
	}
};

#endif