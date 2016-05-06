

#ifndef _BASE_STAR_H
#define _BASE_STAR_H

#include "BaseSprite.h"

class BaseStar : public BaseSprite
{
public:
	virtual ~BaseStar();

	virtual bool init();

protected:
	BaseStar();
};

#endif // _BASE_STAR_H