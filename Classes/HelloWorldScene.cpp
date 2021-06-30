/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Scene::init()) {
		return false;
	}

	srand((unsigned)time(NULL));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0) {
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else {
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	bubbles = new Bubble**[10];
	for (int i = 0; i < 10; i++) {
		bubbles[i] = new Bubble*[10];
		for (int j = 0; j < 10; j++) {
			int color = (rand_0_1() * 4 + 1);
			switch (color) {
			case 1:
				bubbles[i][j] = Bubble::create("BubbleBlue.png");
				bubbles[i][j]->color = 1;
				break;
			case 2:
				bubbles[i][j] = Bubble::create("BubbleGreen.png");
				bubbles[i][j]->color = 2;
				break;
			case 3:
				bubbles[i][j] = Bubble::create("BubbleSalad.png");
				bubbles[i][j]->color = 3;
				break;
			case 4:
				bubbles[i][j] = Bubble::create("BubbleYellow.png");
				bubbles[i][j]->color = 4;
				break;
			}
			bubbles[i][j]->setPosition(Vec2(bubbles[i][j]->getContentSize().width * i + bubbles[i][j]->getContentSize().width / 2, bubbles[i][j]->getContentSize().height * j + bubbles[i][j]->getContentSize().height / 2));
			this->addChild(bubbles[i][j], 0);
		}
	}

	textField = TextField::create("Coords", "Arial", 30);

	//  —оздание "одиночного" слушател€ событий касани€
	// (обрабатываетс€ одно касание за раз)
	listener1 = EventListenerTouchOneByOne::create();

	// срабатывает при нажатии
	listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::ontouchBegin, this);
	;
	// ƒобавл€ем слушатель
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	textField->setPosition(Vec2(800, 300));

	this->addChild(textField, 10);


	return true;
}

bool HelloWorld::ontouchBegin(Touch* touch, Event* event) {
	if ((touch->getLocation().x < bubbles[0][0]->getContentSize().width * 10) && (touch->getLocation().y < bubbles[0][0]->getContentSize().height * 10)) {
		int x = (int)touch->getLocation().x / (int)bubbles[0][0]->getContentSize().width;
		int y = (int)touch->getLocation().y / (int)bubbles[0][0]->getContentSize().height;
		textField->setText(to_string(x) + " " + to_string(y));
		changeImage(x, y);
	}
	else
		textField->setText("11 11");
	return true; // ≈сли вы его прин€ли
}

void HelloWorld::changeImage(int i, int j) {
	int color = (rand_0_1() * 4 + 1);
	if (bubbles[i][j]->color == color) {
		changeImage(i, j);
		return;
	}
	switch (color) {
	case 1:
		bubbles[i][j]->setTexture("BubbleBlue.png");
		bubbles[i][j]->color = 1;
		break;
	case 2:
		bubbles[i][j]->setTexture("BubbleGreen.png");
		bubbles[i][j]->color = 2;
		break;
	case 3:
		bubbles[i][j]->setTexture("BubbleSalad.png");
		bubbles[i][j]->color = 3;
		break;
	case 4:
		bubbles[i][j]->setTexture("BubbleYellow.png");
		bubbles[i][j]->color = 4;
		break;
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
