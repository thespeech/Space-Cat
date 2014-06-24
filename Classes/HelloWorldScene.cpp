#include "HelloWorldScene.h"

USING_NS_CC;

#define FIX_POS(_pos, _min, _max) \
	if(_pos < _min) \
		_pos = _min; \
else if(_pos > _max) \
	_pos = _max; \

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //Set up accelerometer
	_ball = Sprite::create("Icon.png");
		_ball->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
		addChild(_ball);

		_ball->retain();
    return true;
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event)
{
	if (_ball == nullptr)
	{
		return; //Apparently for Nexus S?
	}

	auto ballsize = _ball->getContentSize();
	auto pos = _ball->getPosition();

	pos.x += acc->x * 9.81f;
	pos.y += acc->y * 9.81f;

	FIX_POS(pos.x, (VisibleRect::left().x+ballsize.width / 2.0), (VisibleRect::right().x - ballsize.width / 2.0));
	FIX_POS(pos.y, (VisibleRect::bottom().y+ballsize.height / 2.0), (VisibleRect::top().y - ballsize.height / 2.0));
	_ball->setPosition(pos);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
