#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Bubble : public cocos2d::Sprite {
public:

	int color;

	static Bubble* create(const std::string& filename);

};

#endif // __BUBBLE_H__
