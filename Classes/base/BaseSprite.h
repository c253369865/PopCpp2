
#ifndef _BASE_SPRITE_H
#define _BASE_SPRITE_H

#include "cocos2d.h"

USING_NS_CC;

class BaseSprite : public Sprite
{
public:
	virtual ~BaseSprite();

	virtual bool init();

protected:
	BaseSprite();
};

#endif // _BASE_SPRITE_H