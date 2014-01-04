#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SneakyJoystickSkinnedBase.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // マップチップ表示
    CCTMXTiledMap* pTileMap = CCTMXTiledMap::create("desert.tmx");
    this->addChild(pTileMap);
    pTileMap->setTag(TAG_MAP);

    // 主人公表示
    
    CCLOG("[%p]HelloWorld::init",this);
    pHero = Human::create("char_hero.png", "HERO");
    pHero->setPosition(ccp(size.width/2, size.height/2));
    pHero->addParent(this,100);
    pHero->walkCycli(1.1);
    this->addChild(pHero);
    
    // NPCA表示
    pNpcA = Human::create("char_boss.png", "NPCA");
    pNpcA->setPosition(ccp(size.width/2 - 100, size.height/2));
    pNpcA->addParent(this,101);
    pNpcA->walkCycli(0.9);
    this->addChild(pNpcA);
    
    // NPCBを表示
    pNpcB = Human::create("char_henchman.png", "NPCB");
    pNpcB->setPosition(ccp(size.width/2 + 100, size.height/2));
    pNpcB->addParent(this,102);
    pNpcB->walkCycli(1.2);
    this->addChild(pNpcB);

    // NPCCを表示
    pNpcC = Human::create("char_henchman.png", "NPCC");
    pNpcC->setPosition(ccp(size.width/2, size.height/2 + 100) );
    pNpcC->addParent(this,102);
    pNpcC->walkCycli(1.5);
    this->addChild(pNpcC);

    // NPCDを表示
    pNpcD = Human::create("char_henchman.png", "NPCD");
    pNpcD->setPosition(ccp(size.width/2 + 100, size.height/2 + 100));
    pNpcD->addParent(this,102);
    pNpcD->walkCycli(0.6);
    this->addChild(pNpcD);

    // NPCEを表示
    pNpcE = Human::create("char_henchman.png", "NPCE");
    pNpcE->setPosition(ccp(size.width/2 - 100, size.height/2 + 100) );
    pNpcE->addParent(this,102);
    pNpcE->walkCycli(0.87);
    this->addChild(pNpcE);

    // NPCFを表示
    pNpcF = Human::create("char_henchman.png", "NPCF");
    pNpcF->setPosition(ccp(size.width/2 , size.height/2 - 100) );
    pNpcF->addParent(this,102);
    pNpcF->walkCycli(1.87);
    this->addChild(pNpcF);
    
    // NPCGを表示
    pNpcG = Human::create("char_henchman.png", "NPCG");
    pNpcG->setPosition(ccp(size.width/2 + 100, size.height/2  - 100));
    pNpcG->addParent(this,102);
    pNpcG->walkCycli(0.97);
    this->addChild(pNpcG);
    
    // NPCHを表示
    pNpcH = Human::create("char_henchman.png", "NPCH");
    pNpcH->setPosition(ccp(size.width/2 - 100, size.height/2 - 100) );
    pNpcH->addParent(this,102);
    pNpcH->walkCycli(1.27);
    this->addChild(pNpcH);
    
    pHero->walkAround(this, true);
    pNpcA->walkAround(this, true);
    pNpcB->walkAround(this, true);

    pNpcC->walkAround(this, true);
    pNpcD->walkAround(this, true);
    pNpcE->walkAround(this, true);
    
    pNpcF->walkAround(this, true);
    pNpcG->walkAround(this, true);
    pNpcH->walkAround(this, true);
    
    // ジョイスティック設定
    joystickbase = new SneakyJoystick();
    joystickbase->initWithRect(CCRectMake(0, 0, 100.0f, 100.0f));
    joystickbase->autorelease();
    
    skinjoystick = SneakyJoystickSkinnedBase::create();
    skinjoystick->setBackgroundSprite(CCSprite::create("jyostric1.png"));  //ジョイスティックの背景
    skinjoystick->setThumbSprite(CCSprite::create("jyostric2.png"));
    skinjoystick->setJoystick(joystickbase);
    skinjoystick->setPosition(ccp(150,150));
    
    //ヘッダーで    SneakyJoystick *joystickと定義をしてます。
    joystick = skinjoystick->getJoystick();
    joystick->setAutoCenter(true);
    joystick->setHasDeadzone(true);
    
    //このようにデッドスペースの半径を設定します。
    joystick->setDeadRadius(20.0f);
 
    this->addChild(skinjoystick,9999);
 
    this->scheduleUpdate();
    
    return true;
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchBegan");
    return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchEnded");
}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("ccTouchMoved");
}

void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchCancelled");
}

void HelloWorld::update(float delta)
{
    
    
    CCPoint moveingPoint = joystick->getVelocity();

    CCLOG("moveingPoint %f,%f",moveingPoint.x, moveingPoint.y);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
