
#include "SimpleStar.h"

SimpleStar::SimpleStar()
{

}

SimpleStar::~SimpleStar()
{

}

bool SimpleStar::init()
{
	if (!BaseStar::init())
	{
		return false;
	}

	return true;
}