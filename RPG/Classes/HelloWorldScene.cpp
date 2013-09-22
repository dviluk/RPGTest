#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
    pHero = Human::create("char_hero.png");
    pHero->setPosition(ccp(size.width/2, size.height/2));
    pHero->addParent(this);
    
    // NPCA表示
    pNpcA = Human::create("char_boss.png");
    pNpcA->setPosition(ccp(size.width/2 + 100, size.height/2));
    pNpcA->addParent(this);
    
    // NPCBを表示
    pNpcB = Human::create("char_henchman.png");
    pNpcB->addParent(this);
    pNpcB->setPosition(ccp(size.width/2 - 100, size.height/2));
    
    // タッチイベント有効
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);

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
    this->unschedule(schedule_selector(HelloWorld::update));
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
    CCLOG("update %f",delta);
#if 0
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(TAG_MAP);
        
    CCPoint newTilemapPoint;
    newTilemapPoint = pTileMap->getPosition();
    
    switch (PlayerDirectcion) {
        case 2:
            newTilemapPoint.y -= 32;
            break;
        case 1:
            newTilemapPoint.y += 32;
            break;
        case 3:
            newTilemapPoint.x += 32;
            break;
        case 4:
            newTilemapPoint.x -= 32;
            break;
        default:
            break;
    }
    
    CCMoveTo* actionMove = CCMoveTo::create(0.1f, newTilemapPoint);
    pTileMap->stopAllActions();
    pTileMap->runAction(actionMove);
#endif
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
