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
    
    // キャラクターアニメーション設定
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCSpriteFrame* pSpritesCharacter[12];     // 12個分のスプライトの配列を用意する
    const int X_SIZE = 96;// ピースの横幅
    const int Y_SIZE = 64;// ピースの縦幅
    
    int ix=0;
    for (int y=0;y<4; y++) {
        for (int x=0;x<3; x++) {
            CCRect rect(float(x*X_SIZE), // X座標
                        float(y*Y_SIZE), // Y座標
                        float(X_SIZE),   // 幅
                        float(Y_SIZE));  // 高さ
            pSpritesCharacter[ix] = CCSpriteFrame::create("character.png", rect);
            ix++;
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
    
    // 全フレーム表示後は１フレームに戻る
    pAnimationFront->setRestoreOriginalFrame(true);
    pAnimationBack->setRestoreOriginalFrame(true);
    pAnimationLeft->setRestoreOriginalFrame(true);
    pAnimationRight->setRestoreOriginalFrame(true);
    
    pAnimationCache->addAnimation( pAnimationFront, "FRONT" );
    pAnimationCache->addAnimation( pAnimationBack,  "BACK" );
    pAnimationCache->addAnimation( pAnimationLeft,  "LEFT" );
    pAnimationCache->addAnimation( pAnimationRight, "RIGHT" );
    
    CCAnimation *pAnimation = pAnimationCache->animationByName("FRONT");
    
    // フレームアニメーションを繰り返す
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation) );
    
    // add "HelloWorld" splash screen"
    pPlayer= CCSprite::create();
    
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
    
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(TAG_MAP);
    
    CCPoint charePoint;
    CCPoint abPoint;
    CCPoint tileLocation = pTileMap->getPosition();
    CCPoint point = pTouch->getLocationInView();
    CCLOG("タッチ座標(画面のピクセル) %f,%f",point.x, point.y);
    CCLOG("タイルロケーション(タイルマップの左下位置) %f,%f",tileLocation.x, tileLocation.y);
    
    CCSize screensize = CCDirector::sharedDirector()->getWinSize();
    CCPoint touchPoint = ccp(point.x, screensize.height - point.y);
    
    abPoint.x =  - tileLocation.x  + touchPoint.x;
    abPoint.y =  - tileLocation.y  + touchPoint.y;
    
    CCSize tileSize = pTileMap->getTileSize();
    
    int unit_x = (int)(abPoint.x/tileSize.width);
    int unit_y = (int)(abPoint.y/tileSize.height);
    
    CCLOG("タイル位置(タッチしたタイルマップの位置) %d,%d",unit_x, unit_y);
    CCLOG("タイルサイズ(1タイル分) %f,%f",tileSize.width, tileSize.height);
    
    // どの方向に移動するか
    // 中心座標から、タッチ座標の距離を算出
    charePoint.x = screensize.width/2;
    charePoint.y = screensize.height/2;
    
    int xdiff = touchPoint.x - charePoint.x;
    int ydiff = touchPoint.y - charePoint.y;
    
    int abs_x = abs(xdiff);
    int abx_y = abs(ydiff);
    
    if (xdiff < 0)
    {
        if (ydiff < 0)
        {
            if (abx_y < abs_x)
            {
                CCLOG("左向き");
                pAnimation = pAnimationCache->animationByName("LEFT");
                PlayerDirectcion = PLAYER_LEFT;
            }
            else
            {
                CCLOG("下向き");
                pAnimation = pAnimationCache->animationByName("FRONT");
                PlayerDirectcion = PLAYER_FRONT;
            }
            
        }
        else
        {
            if (abx_y < abs_x)
            {
                CCLOG("左向き");
                pAnimation = pAnimationCache->animationByName("LEFT");
                PlayerDirectcion = PLAYER_LEFT;
                
            }
            else
            {
                CCLOG("上向き");
                pAnimation = pAnimationCache->animationByName("BACK");
                PlayerDirectcion = PLAYER_BACK;
            }
        }
        
    }
    else
    {
        if (ydiff < 0)
        {
            if (abx_y < abs_x)
            {
                CCLOG("右向き");
                pAnimation = pAnimationCache->animationByName("RIGHT");
                PlayerDirectcion = PLAYER_RIGHT;
                
            }
            else
            {
                CCLOG("下向き");
                pAnimation = pAnimationCache->animationByName("FRONT");
                PlayerDirectcion = PLAYER_FRONT;
            }
            
        }
        else
        {
            if (abx_y < abs_x)
            {
                CCLOG("右向き");
                pAnimation = pAnimationCache->animationByName("RIGHT");
                PlayerDirectcion = PLAYER_RIGHT;
            }
            else
            {
                CCLOG("上向き");
                pAnimation = pAnimationCache->animationByName("BACK");
                PlayerDirectcion = PLAYER_BACK;
            }
        }
    }
    
    // アニメーションを実行
    pPlayer->stopAllActions();
    this->schedule(schedule_selector(HelloWorld::update), 0.11f);
    
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));
    pPlayer->runAction(pAction);
    
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
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(TAG_MAP);
    
    CCSize screensize = CCDirector::sharedDirector()->getWinSize();
    
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
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
