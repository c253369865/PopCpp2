

#ifndef _SIMPLE_STAR_H
#define _SIMPLE_STAR_H

#include "base/BaseStar.h"

class SimpleStar : public BaseStar
{
public:
	SimpleStar();
	virtual ~SimpleStar();

	virtual bool init();

	CREATE_FUNC(SimpleStar);
	
};

#endif // _SIMPLE_STAR_H