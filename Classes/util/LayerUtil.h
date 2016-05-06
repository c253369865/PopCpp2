
#ifndef _LAYER_H_
#define _LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class LayerUtil
{
public:
	static Scene* getSceneWithLayer(Layer *layer);
};

#endif // _LAYER_H_