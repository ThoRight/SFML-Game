#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Animation.h"
class Component
{
public:
	bool exist = false;
};
class CTransform : public Component
{
public:
	Vec2 position = {0,0};
	Vec2 prevPosition = { 0,0 };
	Vec2 speed = {0.0,0.0};
	Vec2 scale = {0.0,0.0};
	float angle = 0;
	CTransform(Vec2 pos, Vec2 sp, Vec2 scl, float ang)
	{
		position = pos;
		speed = sp;
		scale = scl;
		angle = ang;
		exist = true;
	}
};
class CScore : public Component
{
public:
	int score = 0;
	CScore(int scr)
	{
		score = scr;
		exist = true;
	}
};
class CBoundingBox : public Component
{
public:
	Vec2 size;
	float overlapX = 0;
	float overlapY = 0;
	float preOverlapX = 0;
	float preOverlapY = 0;
	CBoundingBox(const Vec2& v)
	{
		size = v;
		overlapX = v.x;
		overlapY = v.y;
		exist = true;
	}
};
class CLifespan : public Component
{
public:
	int remaining = 0;
	int total = 0;
	CLifespan(const int total)
	{
		this->total = total;
		this->remaining = total;
		exist = true;
	}
};
class CInput : public Component
{
public:
	bool left = false;
	bool right = false;
	bool jump = false;
	bool fire = false;
	CInput()
	{
		exist = true;
	}
};
class CAnimation : public Component
{
public:
	std::vector<Animation> animations;
	CAnimation(const Animation& anim)
	{
		animations.push_back(anim);
		exist = true;
	}
	void destroyFinishedAnim()
	{
		std::vector<Animation> tempAnimations;
		int index = 0;
		for (int i=0;i<animations.size();++i)
		{
			//std::cout << "\nLOOP: " << index << "\n";
			if (animations[i].hasEnded() && i != 0)
			{
				std::cout << "\nDELETED COMP " << i << "\n";
			}
			else
			{
				tempAnimations.push_back(animations[i]);
			}
			++index;
		}
		animations = tempAnimations;
	}
};
class CState : public Component
{
public:
	std::string name;
	bool dirRight;
	CState(const std::string& name, const bool dir)
	{
		this->name = name;
		dirRight = dir;
		exist = true;
	}
};
class CGravity : public Component
{
public:
	float gravity = 1;
	CGravity(const float gravity)
	{
		this->gravity = gravity;
		exist = true;
	}
};

#endif



