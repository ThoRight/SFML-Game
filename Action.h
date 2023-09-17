#ifndef ACTION_H
#define ACTION_H

#include "Assets.h"
class Action
{
public:
	std::string name = "";
	std::string type = "";
	Action(std::string n, std::string t)
	{
		name = n;
		type = t;
	}
	Action(Action& a)
	{
		name = a.name;
		type = a.type;
	}
};

#endif

