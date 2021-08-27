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
	this->setVisible(true);
	switch (tmp) {
	case 0:
		this->setVisible(false);
		break;
	case 1:
		this->setTexture("BubbleBlue.png");
		break;
	case 2:
		this->setTexture("BubbleGreen.png");
		break;
	case 3:
		this->setTexture("BubbleSalad.png");
		break;
	case 4:
		this->setTexture("BubbleYellow.png");
		break;
	}
}

int Bubble::getColor() {
	return color;
}