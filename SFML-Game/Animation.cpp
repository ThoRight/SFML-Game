#include "Animation.h"
void Animation::update()
{
	if (m_limit % m_speed == 0)
	{
		sf::IntRect rect(m_FW*m_currentFrameanim+m_startX, m_startY, m_FW, m_size.y);
		m_sprite.setTextureRect(rect);
		m_limit = 0;
		if (!m_end && (m_isRepeated || m_currentFrameanim != m_frameCount - 1))
		{
			m_currentFrameanim++;
			m_currentFrameanim %= m_frameCount;
		}
		else if(m_currentFrameanim == m_frameCount - 1)
		{
			m_end = true;
		}
	}
	if (m_lifespan != -1 && m_limit % 60 == 0)
	{
		--m_lifespan;
	}
	if (m_lifespan != -1 && m_lifespan <= 0)
	{
		m_delete = true;
	}
	if ((m_name == "RunRight" || m_name == "RunLeft") && m_speed > 6)
	{
		--m_speed;
	}
	m_limit++;
}
/*
Animation& Animation:: operator=(const Animation& r)
{
	m_sprite = r.m_sprite;
	m_startPoint = r.m_startPoint;
	m_name = r.m_name;
	m_frameCount = r.m_frameCount;
	m_size = r.m_size;
	m_speed = r.m_speed;
	m_FW = r.m_FW;
	m_currentFrame = r.m_currentFrame;
	m_limit = r.m_limit;
	return *this;
}
*/

Animation& Animation:: operator=(const Animation* r)
{
	*this = *r;
	return *this;
}
Animation& Animation:: operator*(const Animation* r)
{
	return *this;
}