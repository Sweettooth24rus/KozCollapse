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

void Bubble::setColor(int tmp) {
	color = tmp;
	if (color == 0)
		this->setVisible(false);
	else
		this->setVisible(true);
}

int Bubble::getColor() {
	return color;
}