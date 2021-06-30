#include "Bubble.h"

Bubble* Bubble::create(const std::string& filename)
{
	Sprite *bubble = new (std::nothrow) Sprite();
	if (bubble && bubble->initWithFile(filename))
	{
		bubble->autorelease();
		return (Bubble*)bubble;
	}
	CC_SAFE_DELETE(bubble);
	return nullptr;
}