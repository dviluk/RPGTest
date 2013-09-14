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

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    // マップチップ表示
    CCTMXTiledMap* pTileMap = CCTMXTiledMap::create("desert.tmx");
    this->addChild(pTileMap);
    pTileMap->setPosition(ccp(0, 0));
    
    // キャラクタ表示
    CCSpriteFrame* pSpritesCharacter[12]; // スプライトフレームの数
    const int WIDTH_SIZE  = 96;      	  // 一つのスプライトの幅
    const int HEIGHT_SIZE = 64;      	  // 一つのスプライトの高さ
    
    //「character.png」からスプライトフレームへの切り出し
    int i=0;
    for (int y=0;y<4; y++) {
        for (int x=0;x<3; x++) {
            CCRect rect(float(x * WIDTH_SIZE),  // X座標
                        float(y * HEIGHT_SIZE), // Y座標
                        float(WIDTH_SIZE),      // 幅
                        float(HEIGHT_SIZE));    // 高さ
            pSpritesCharacter[i++] = CCSpriteFrame::create("character.png", rect);
        }
    }
    
    CCAnimation *pAnimationFront = CCAnimation::create();
    CCAnimation *pAnimationBack  = CCAnimation::create();
    CCAnimation *pAnimationLeft  = CCAnimation::create();
    CCAnimation *pAnimationRight = CCAnimation::create();
    
    pAnimationFront->addSpriteFrame(pSpritesCharacter[1]);
    pAnimationFront->addSpriteFrame(pSpritesCharacter[2]);
    
    pAnimationBack->addSpriteFrame(pSpritesCharacter[7]);
    pAnimationBack->addSpriteFrame(pSpritesCharacter[8]);
    
    pAnimationLeft->addSpriteFrame(pSpritesCharacter[10]);
    pAnimationLeft->addSpriteFrame(pSpritesCharacter[11]);
    
    pAnimationRight->addSpriteFrame(pSpritesCharacter[4]);
    pAnimationRight->addSpriteFrame(pSpritesCharacter[5]);
    
    pAnimationFront->setDelayPerUnit(0.5f);
    pAnimationBack->setDelayPerUnit(0.5f);
    pAnimationLeft->setDelayPerUnit(0.5f);
    pAnimationRight->setDelayPerUnit(0.5f);
    
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    pAnimationCache->addAnimation( pAnimationFront, "FRONT" );
    pAnimationCache->addAnimation( pAnimationBack,  "BACK" );
    pAnimationCache->addAnimation( pAnimationLeft,  "LEFT" );
    pAnimationCache->addAnimation( pAnimationRight, "RIGHT" );
    
    CCAnimation *pAnimation = pAnimationCache->animationByName("FRONT");
    
    // フレームアニメーションを繰り返す
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation) );
    
    // add "HelloWorld" splash screen"
    CCSprite* pPlayer= CCSprite::create();
    
    // 主人公は常に中心
    pPlayer->setPosition( ccp(size.width/2, size.height/2));
    
    // add the sprite as a child to this layer
    this->addChild(pPlayer, 0);
    
    // アニメーションを実行
    pPlayer->runAction(pAction);

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
}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchMoved");
}

void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchCancelled");
}

void HelloWorld::update(float delta)
{
    CCLOG("upcate");
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
