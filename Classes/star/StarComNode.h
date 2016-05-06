


#ifndef _STAR_COM_NODE_H
#define _STAR_COM_NODE_H

#include "cocos2d.h"

USING_NS_CC;

enum class StarType {
	
	
};

typedef struct _clickPos
{
	int x;
	int y;

	_clickPos(int i, int j)
	{
		this->x = i;
		this->y = j;
	}
}ClickPos;

class StarComNode
{
public:
	StarComNode();
	virtual ~StarComNode();

	virtual bool init();
	

public:
	Sprite* getSprite() { return _showSprite; };
	void startDisappear(float beginTime, float durationTime);

public:
	// �Ƿ�ѡ��
	bool is_slected;
	// �Ƿ��Ѿ�������
	bool is_check;
	// �Ƿ��Ѿ����������ʧ��
	bool is_enable;
	// ��������
	int type_idx;
	// �ڽ����λ��
	Vec2 location;
	ClickPos clickPos;
private:
	Sprite* _showSprite;
};

#endif // _STAR_COM_NODE_H