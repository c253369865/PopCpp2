

#include "StarComNode.h"
#include "util/LogUtil.h"

#define random(x) (rand()%x)

StarComNode::StarComNode()
: is_check(false)
, is_slected(false)
, is_enable(true)
, type_idx(0)
, clickPos(-1, -1)
{
	init();
}

StarComNode::~StarComNode()
{
	//_showSprite->release();
}

bool StarComNode::init()
{
	/*if (!Node::init())
	{
	return false;
	}*/

	char fileName[255];
	type_idx = random(5) + 1;
	sprintf_s(fileName, "star/star_%d.png", type_idx);
	//LogUtil::d(fileName);

	_showSprite = Sprite::create(fileName);
	//_showSprite->retain();

	return true;
}

void StarComNode::startDisappear(float beginTime, float durationTime)
{
	_showSprite->setVisible(false);
	is_enable = false;
}