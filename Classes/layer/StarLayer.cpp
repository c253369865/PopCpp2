
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
	
	// һ��һ�еĳ�ʼ��
	// ��������, ��������
	for (int j = 0; j < COW; j++)
	{
		y = j * width + width / 2 + beginY;
		for (int i = 0;i < COW;i++)
		{
			x = i * width + width / 2;

			StarComNode* starNode = addNodeAtPos(Vec2(x, y), scale);
			starNode->clickPos = ClickPos(i, j);

			// Ϊʲô������������sprite????
			// ������ create������autorelease()�����ͷ��˶��������
			_stars[i][j] = starNode;
			sprintf_s(output, "x=%.0f, y=%.0f, scale=%.2f, i=%d,j=%d, typeIdx=%d", x, y, scale, i, j, starNode->type_idx);
			LogUtil::d(output);
		}
	}

	// ��ӵ��
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
	// Ϊʲô��Ҫ���ô�С?
	// ���ǲ�Ҫ,�����ô���,��С��45,����72
	sprite->setScale(scale);
	addChild(sprite);

	return node;
}

void StarLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	// �ڶ�����ɺ�����,��ʱ��������
	// todo �����б��ʼ��????
	// ���ʴ��������� create������autorelease()�����ͷ��˶��������
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
			// �Ȱѱ�ǻ�ԭ
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
		// ���� ��������
		if (starNode)
		{
			int idx1 = starNode->type_idx;
			ClickPos clickPos = starNode->clickPos;
			// ��
			if (clickPos.x > 0)
			{
				StarComNode* leftStar = _stars[clickPos.x - 1][clickPos.y];
				setOneStar(starNode, leftStar);
			}

			// ��
			if (clickPos.y < COW - 1)
			{
				StarComNode* upStar = _stars[clickPos.x][clickPos.y+1];
				setOneStar(starNode, upStar);
			}

			// ��
			if (clickPos.x < COW - 1)
			{
				StarComNode* rightStar = _stars[clickPos.x + 1][clickPos.y];
				setOneStar(starNode, rightStar);
			}

			// ��
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

	// ����������ж���
	// ���ϵ���,������
	/*
	1. ���е���ʧ,����������
		��ʧ��star���,��������
		��������Ч,����Ư�ƹ���starlayer����,star��������λ��,
		star��ʧ˳����starlayer����
	2. �����������,�ұߵ�����
		������ʱ��,����ʧ��star,������Ҫ���Ƶ�star,����Ч,�����ȵĶ���ʱ���ź�,�����Ͳ���������ƶ�����,
		�رյ��-->��ʧ+����-->Ȼ������-->����Ƿ���-->����Ƿ��п��Ե����-->�жϴ򿪵��(�������,����״̬���ٴ�)
	3. ���������޷������starlayer����
	4. starlayer����̫���߼�����,�����ǳ�ʼ��,�жϵ��,���Ŷ����ȣ����Կ�������߼�������������
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

						//// ������������������䣨�˷�ʽ��������������������У�1.û�е��еģ�2.�Ѿ����������ʧ���ģ�
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
						//		// ����һλ����¼���ƿ�ʼʱ�䣬����λ����
						//		Sprite* curSprite = nextNode->getSprite();
						//		curSprite->stopAllActions();
						//		nextNode->getSprite()->runAction(MoveTo::create(0.5, curNode->getSprite()->getPosition()));

						//		// �л�������������
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

// star1 : ���Աȵ�
void StarLayer::setOneStar(StarComNode* star1, StarComNode* star2)
{
	if (star1 && star2)
	{	
		if (!star2->is_check && star2->is_enable) {
			if (star1->type_idx == star2->type_idx)
			{
				// �ҵ�����ͬ,���ñ��,��ӵ����Ҷ�����
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