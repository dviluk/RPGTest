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
    CCSprite* pSpritesCharacter[12]; // スプライトの数
    const int WIDTH_SIZE  = 96;     // 一つのスプライトの幅
    const int HEIGHT_SIZE = 64;     // 一つのスプライトの高さ
    
    //「character.png」からスプライトフレームへの切り出し
    int i=0;
    for (int y=0;y<4; y++) {
        for (int x=0;x<3; x++) {
            CCRect rect(float(x * WIDTH_SIZE),  // X座標
                        float(y * HEIGHT_SIZE), // Y座標
                        float(WIDTH_SIZE),      // 幅
                        float(HEIGHT_SIZE));    // 高さ
            pSpritesCharacter[i++] = CCSprite::create("character.png", rect);
        }
    }
    
     // 座標を確定して、シーンに追加
     for (int i=0; i<12; i++)
     {
         int x = 50;
         int y = 50;
         pSpritesCharacter[i]->setPosition(ccp(x + (i * 50), y + (i * 50)));
         this->addChild(pSpritesCharacter[i]);
     }
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}