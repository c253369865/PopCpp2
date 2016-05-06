
#include "StarLayer.h"
#include "VisibleRect.h"
#include "star/StarComNode.h"
#include "util/LogUtil.h"
#include "Constants.h"
#include "mgr/PlayMgr.h"

StarLayer::StarLayer()
: sameStarCount(0)
{
}

StarLayer::~StarLayer()
{
	LogUtil::d("StarLayer::~StarLayer()");

	for (int i = 0; i < COW; i++)
	{
		for (int j = 0; j < COW; j++)
		{
			StarComNode* starNode = _stars[i][j];
			if (starNode)
			{
				delete starNode;
				starNode = nullptr;
			}
			_stars[i][j] = nullptr;
		}
	}

	_needCheckStarVector.clear();
}

bool StarLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	char output[255];
	sprintf_s(output, "width=%.0f, height=%.0f", visibleSize.width, visibleSize.height);
	LogUtil::d(output);

	StarComNode *node = new StarComNode();
	Sprite* spr = node->getSprite();
	float sprWidth = spr->getContentSize().width;


	float width = visibleSize.width / COW;
	float scale = width / sprWidth;
	float x = 0;
	float y = 0;
	float beginY = 100;
	
	// 一行一行的初始化
	// 从左往右, 从下往上
	for (int j = 0; j < COW; j++)
	{
		y = j * width + width / 2 + beginY;
		for (int i = 0;i < COW;i++)
		{
			x = i * width + width / 2;

			StarComNode* starNode = addNodeAtPos(Vec2(x, y), scale);
			starNode->clickPos = ClickPos(i, j);

			// 为什么在这索引不到sprite????
			// 是由于 create方法的autorelease()方法释放了对象引起的
			_stars[i][j] = starNode;
			sprintf_s(output, "x=%.0f, y=%.0f, scale=%.2f, i=%d,j=%d, typeIdx=%d", x, y, scale, i, j, starNode->type_idx);
			LogUtil::d(output);
		}
	}

	// 添加点击
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(StarLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

StarComNode* StarLayer::addNodeAtPos(Vec2 pos, float scale)
{
	//StarComNode *node = StarComNode::create();
	StarComNode *node = new StarComNode();
	Sprite *sprite = node->getSprite();
	sprite->setPosition(pos);
	// 为什么不要设置大小?
	// 不是不要,是设置错了,大小是45,不是72
	sprite->setScale(scale);
	addChild(sprite);

	return node;
}

void StarLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	// 在动画完成后设置,暂时放在这里
	// todo 对象列表初始化????
	// 访问错误是由于 create方法的autorelease()方法释放了对象引起的
	resetStarStatus();

	LogUtil::d("-------------------------------------------------");
	bool find = false;

	for (auto &touch : touches)
	{
		Vec2 location = touch->getLocation();
		char ch[255];
		sprintf_s(ch, "click x=%.2f, y=%.2f", location.x, location.y);
		LogUtil::d(ch);

		for (int j = 0; j < COW; j++)
		{
			for (int i = 0; i < COW; i++)
			{
				StarComNode* starNode = _stars[i][j];

				Sprite* sprite = starNode->getSprite();
				if (sprite)
				{
					bool isClick = sprite->getBoundingBox().containsPoint(location);
					if (isClick)
					{
						sprintf_s(ch, "click -> x=%d, y=%d", i, j);
						LogUtil::d(ch);

						starNode->is_slected = true;
						starNode->is_check = true;
						_needCheckStarVector.clear();
						_needCheckStarVector.push_back(starNode);
						sameStarCount = 1;
						checkAllStarSelected();

						find = true;
						break;
					}
				}

				if (find)
				{
					break;
				}
			}

			if (find)
			{
				break;
			}
		}
		
		if (find)
		{
			break;
		}
	}
}

void StarLayer::resetStarStatus()
{
	for (int j = 0; j < COW; j++)
	{
		for (int i = 0; i < COW; i++)
		{
			StarComNode* starNode = _stars[i][j];
			// 先把标记还原
			if (starNode)
			{
				starNode->is_slected = false;
				starNode->is_check = false;
			}
		}
	}
	sameStarCount = 0;
}

void StarLayer::checkAllStarSelected()
{
	StarComNode* starNode = nullptr;
	do 
	{
		starNode = _needCheckStarVector.at(0);
		// 搜索 左上右下
		if (starNode)
		{
			int idx1 = starNode->type_idx;
			ClickPos clickPos = starNode->clickPos;
			// 左
			if (clickPos.x > 0)
			{
				StarComNode* leftStar = _stars[clickPos.x - 1][clickPos.y];
				setOneStar(starNode, leftStar);
			}

			// 上
			if (clickPos.y < COW - 1)
			{
				StarComNode* upStar = _stars[clickPos.x][clickPos.y+1];
				setOneStar(starNode, upStar);
			}

			// 右
			if (clickPos.x < COW - 1)
			{
				StarComNode* rightStar = _stars[clickPos.x + 1][clickPos.y];
				setOneStar(starNode, rightStar);
			}

			// 下
			if (clickPos.y > 0)
			{
				StarComNode* downStar = _stars[clickPos.x][clickPos.y - 1];
				setOneStar(starNode, downStar);
			}
		}

		if (_needCheckStarVector.size() > 0)
		{
			std::vector<StarComNode*>::iterator it = _needCheckStarVector.begin();
			_needCheckStarVector.erase(it);
		}

	} while (_needCheckStarVector.size() > 0);

	// 遍历输出所有对象
	// 从上到下,从左到右
	/*
	1. 点中的消失,并产生分数
		消失由star完成,设置属性
		产生粒子效,分数漂移果由starlayer处理,star返回所在位置,
		star消失顺序由starlayer安排
	2. 上面的落下来,右边的左移
		遍历的时候,把消失的star,上面需要下移的star,粒子效,分数等的动画时序安排好,这样就不用添加下移队列了,
		关闭点击-->消失+粒子-->然后下移-->检查是否达标-->检查是否还有可以点击的-->判断打开点击(动画完成,重置状态后再打开)
	3. 动画过程无法点击由starlayer控制
	4. starlayer存在太多逻辑处理,如星星初始化,判断点击,安排动画等，可以考虑添加逻辑辅助类来处理
	*/

	float curBeginAnimTime = 0;
	int score = 0;
	if (sameStarCount >= 2)
	{
		char ch[1024];
		for (int j = COW - 1; j >= 0; j--)
		{
			sprintf_s(ch, "");

			for (int i = 0; i < COW; i++)
			{
				StarComNode* starNode = _stars[i][j];
				if (starNode)
				{
					char ch1[255];
					sprintf_s(ch1, "%d ", starNode->is_slected);
					strcat_s(ch, ch1);
					//
					if (starNode->is_slected)
					{
						//starNode->startDisappear(curBeginAnimTime, STAR_DISAPPEAR_TIME);
						PlayMgr::instance()->finishOneStar(starNode, curBeginAnimTime, score);
						curBeginAnimTime = curBeginAnimTime + STAR_ANIMATE_TIME_INTERVAL;
						score = score + 20;

						//// 此星星上面的星星下落（此方式下上面的所有星星类型有：1.没有点中的，2.已经被点过，消失掉的）
						//int k = j;
						//StarComNode* curNode;
						//StarComNode* nextNode;
						//do 
						//{
						//	k = k + 1;
						//	curNode = _stars[i][k-1];
						//	nextNode = _stars[i][k];
						//	if (curNode && nextNode)
						//	{
						//		// 下移一位（记录下移开始时间，下移位数）
						//		Sprite* curSprite = nextNode->getSprite();
						//		curSprite->stopAllActions();
						//		nextNode->getSprite()->runAction(MoveTo::create(0.5, curNode->getSprite()->getPosition()));

						//		// 切换上下两个星星
						//		_stars[i][k-1] = nextNode;
						//		nextNode->clickPos = ClickPos(i, k - 1);
						//		_stars[i][k] = curNode;
						//		curNode->clickPos = ClickPos(i, k);
						//	}
						//} while (k < COW && nextNode && nextNode->is_enable);
					}
				}
			}

			LogUtil::d(ch);
		}
	}
}

// star1 : 被对比的
void StarLayer::setOneStar(StarComNode* star1, StarComNode* star2)
{
	if (star1 && star2)
	{	
		if (!star2->is_check && star2->is_enable) {
			if (star1->type_idx == star2->type_idx)
			{
				// 找到并相同,设置标记,添加到查找队列中
				star2->is_slected = true;
				_needCheckStarVector.push_back(star2);
				
				char ch[255];
				sprintf_s(ch, " same -> x=%d, y=%d ", star2->clickPos.x, star2->clickPos.y);
				LogUtil::d(ch);

				sameStarCount = sameStarCount + 1;
			}
		}
	}

	if (star2)
	{
		star2->is_check = true;
	}
	
}