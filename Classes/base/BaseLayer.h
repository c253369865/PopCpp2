
#ifndef _BASE_LAYER_H_
#define _BASE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public cocos2d::Layer
{
public:
	virtual ~BaseLayer();

	virtual bool init();

protected:
	BaseLayer();
};

#endif // _BASE_LAYER_H_