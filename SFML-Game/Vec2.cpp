#include "Vec2.h"
Vec2 Vec2:: operator +(const Vec2& rhs)
{
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 Vec2:: operator /(const Vec2& rhs)
{
	return Vec2(x / rhs.x, y / rhs.y);
}
Vec2 Vec2:: operator /(const int rhs)
{
	return Vec2(x / rhs, y / rhs);
}
void Vec2:: operator +=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}
void Vec2:: operator *=(const Vec2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}
void Vec2:: operator -=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}
bool Vec2:: operator !=(const Vec2& rhs)const
{
	return this->x != rhs.x || this->y != rhs.y;
}

Vec2& Vec2:: operator =(const Vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}
bool Vec2:: operator ==(const Vec2& rhs)const
{
	return(x == rhs.x && y == rhs.y);
}
Vec2:: operator sf::Vector2f() const {
	return sf::Vector2f(x, y);
}
float Vec2::getDistance(const Vec2& rhs)const
{
	return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
}
