#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vec2.h"
class Animation
{
	sf::Sprite m_sprite;
	int m_frameCount=0;
	int m_currentFrameanim=0;
	int m_limit = 0;
	int m_speed = 0;
	float m_FW = 0;
	float m_startX = 0;
	float m_startY = 0;
	Vec2 m_size;
	std::string m_name;
	bool m_isRepeated = true;
	bool m_end = false;
	int m_lifespan = -1;
public:

	void update();
	bool hasEnded()
	{
		return m_end;
	}
	Vec2& getSize()
	{
		return m_size;
	}
	//Animation& operator =(const Animation& r);
	Animation& operator=(const Animation* r);
	Animation& operator*(const Animation* r);
	void setEnd(bool b)
	{
		m_end = b;
	}
	std::string& getName()
	{
		return m_name;
	}
	sf::Sprite& getSprite()
	{
		return m_sprite;
	}
	int getLifespan()
	{
		return m_lifespan;
	}
	void setLifespan(const int l)
	{
		m_lifespan = l;
	}
	Animation(const std::string name, sf::Texture* texture, const Vec2& size,
		 const int frameCount, const float startX, const float startY, const int speed, const Vec2& scale, const int isEnd, const int lifespan)
	{
		m_startX = startX;
		m_startY = startY;
		m_name = name;
		m_frameCount = frameCount;
		m_size = size;
		m_speed = speed;
		m_FW = size.x / m_frameCount;
		m_sprite = sf::Sprite(*texture);
		sf::IntRect rect(m_startX, m_startY, m_FW, m_size.y);
		m_sprite.setTextureRect(rect);
		m_sprite.setOrigin(m_FW/2, m_size.y/2);
		m_sprite.setScale(scale);
		if (isEnd == 1)
		{
			m_isRepeated = true;
		}
		else
		{
			m_isRepeated = false;
		}
		m_lifespan = lifespan;
		
	}
	Animation(const Animation& r)
	{
		m_sprite = r.m_sprite;
		m_startX = r.m_startX;
		m_startY = r.m_startY;
		m_name = r.m_name;
		m_frameCount = r.m_frameCount;
		m_size = r.m_size;
		m_speed = r.m_speed;
		m_FW = r.m_FW;
		m_currentFrameanim = r.m_currentFrameanim;
		m_limit = r.m_limit;
		m_isRepeated = r.m_isRepeated;
		m_lifespan = r.m_lifespan;
		m_end = r.m_end;
	}
	Animation()
	{

	}


};

#endif


