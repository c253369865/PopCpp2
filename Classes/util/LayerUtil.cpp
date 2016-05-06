
#include "LayerUtil.h"

Scene* LayerUtil::getSceneWithLayer(Layer *layer)
{
	Scene *scene = Scene::create();

	scene->addChild(layer);

	return scene;
}