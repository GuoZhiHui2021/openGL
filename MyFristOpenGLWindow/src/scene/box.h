#pragma once
#include "entity.h"
#include <string>
class Box:public Entity
{
public:
	Box();
	virtual std::string getInstanceType()
	{
		return "Box";
	}
};

