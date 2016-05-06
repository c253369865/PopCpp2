
#include "PlayUILayer.h"
#include "VisibleRect.h"
#include "mgr/PlayMgr.h"

USING_NS_CC;

bool PlayUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Label *label = Label::createWithTTF("1200", "fonts/Marker Felt.ttf", 20);

	Vec2 pos(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height-40);
	label->setPosition(pos);
	addChild(label);

	// 放这有点不好
	PlayMgr::instance()->scorePos = pos;
	
	return true;
}

void PlayUILayer::flyScoreLabel(int score, Vec2 flyTo)
{
	char ch[222];
	sprintf_s(ch, "%d", score);
	Label *lab = Label::createWithTTF(ch, "fonts/Marker Felt.ttf", 10);
	lab->setPosition(flyTo);
	addChild(lab);
}