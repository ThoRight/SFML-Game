#ifndef VEC2_H
#define VEC2_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
class Vec2
{
public:
	float x=0;
	float y=0;
	Vec2(float x, float y): x(x), y(y){}
	Vec2(){}
	Vec2(const sf::Vector2f& v)
	{
		x = v.x;
		y = v.y;
	}
	Vec2 operator +(const Vec2& rhs);
	Vec2 operator /(const Vec2& rhs);
	Vec2 operator /(const int rhs);
	void operator +=(const Vec2& rhs);
	void operator *=(const Vec2& rhs);
	void operator -=(const Vec2& rhs);
	Vec2& operator =(const Vec2& rhs);
	bool operator ==(const Vec2& rhs)const;
	bool operator !=(const Vec2& rhs)const;
    operator sf::Vector2f() const;
	float getDistance(const Vec2& rhs)const;
	
};

#endif

