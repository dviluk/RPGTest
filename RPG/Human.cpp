//
//  Human.cpp
//  RPG
//
//  Created by keizi on 2013/09/16.
//
//

#include "Human.h"

using namespace cocos2d;

// 生成メソッド
Human* Human::create(const char *pszFileName)
{
    Human *pHuman = new Human();
    if (pHuman && pHuman->initWithFile(pszFileName))
    {
        return pHuman;
    }
    
    CC_SAFE_DELETE(pHuman);
    return NULL;
}


// 初期化メソッド(cretaメソッド経由でコールする)
bool Human::initWithFile(const char *pFileName)
{
    // キャラクターアニメーション設定
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    
    pSpriteFrameArray  = new CCArray();

    for (int y=0;y<4; y++) {
        for (int x=0;x<3; x++) {
            CCRect rect(float(x*X_SIZE), float(y*Y_SIZE), float(X_SIZE), float(Y_SIZE));
            pSpriteFrameArray->addObject(CCSpriteFrame::create(pFileName, rect));
        }
    }
    
    //前向き画像
    pAnimationFront = CCAnimation::create();
    pAnimationFront->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(1));
    pAnimationFront->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(2));
    
    //後ろ向き画像
    pAnimationBack = CCAnimation::create();
    pAnimationBack->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(7));
    pAnimationBack->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(8));
    
    //左向き画像
    pAnimationLeft = CCAnimation::create();
    pAnimationLeft->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(10));
    pAnimationLeft->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(11));
    
    //右向き画像
    pAnimationRight = CCAnimation::create();
    pAnimationRight->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(4));
    pAnimationRight->addSpriteFrame((CCSpriteFrame*)pSpriteFrameArray->objectAtIndex(5));
    
    // アニメーションの切り替え周期
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

    // add "HelloWorld" splash screen"
    pSprite = CCSprite::create();
    CCLOG("[%p]initWithFile %p:",this, pSprite);

    return true;
}

// 親ノードにaddCheildする
void Human::addParent(cocos2d::CCNode *pParent, int iTag)
{
    pParent = (CCLayer*)pParent;
    
    // キャラクターアニメーション設定
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    
    // add the sprite as a child to this layer
    pParent->addChild(pSprite, 0);
    CCLOG("[%p]addParent %p",this,pSprite);

    tag = iTag;
    pSprite->setTag(iTag);
    
    CCAnimation *pAnimation = pAnimationCache->animationByName("FRONT");
    
    // フレームアニメーションを繰り返す
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));
    
    // アニメーションを実行
    pSprite->runAction(pAction);
    
}

// 座標指定
void Human::setPosition(const CCPoint& pos)
{
    pSprite->setPosition(pos);
    Point = (CCPoint)pos;
    CCLOG("[%p]setPosition %p",this,pSprite);

}

// 歩き回る
void Human::walkAround(CCNode* parent,  bool flag)
{
    if (flag)
    {
        // 開始
        parent->schedule(schedule_selector(Human::walkRamdom), 3.0);
    }
    else
    {
        // 停止
        parent->unschedule(schedule_selector(Human::walkRamdom));
    }
}


void Human::walkRamdom(void)
{
    CCLOG("[%p]walkRamdom:pSprite %p",this,pSprite);
    CCLOG("[%p]walkRamdom:tag %d",this,tag);
    
    srand((unsigned int)time(NULL));
    int randNum=rand()%4;
    
    switch (randNum)
    {
        case 0:
            walkFront();
            break;
        case 1:
            walkBack();
            break;
        case 2:
            walkLeft();
            break;
        case 3:
            walkRight();
            break;
        default:
            break;
    }
    
}

// 前に移動する
void Human::walkFront(void)
{
    CCSprite* pSprite = (CCSprite*)((CCLayer*)this)->getChildByTag(12);
    CCLOG("[%p]walkFront:pSprite %p",this,pSprite);
    
    CCPoint Point = pSprite->getPosition();
    Point.y -= 32;

    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *pAnimation = pAnimationCache->animationByName("FRONT");
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));

    pSprite->stopAllActions();
    pSprite->runAction(pAction);
    
    CCMoveTo* actionMove = CCMoveTo::create(0.5f, Point);
    pSprite->runAction(actionMove);
}

// 後ろに移動する
void Human::walkBack(void)
{
    CCSprite* pSprite = (CCSprite*)((CCLayer*)this)->getChildByTag(12);
    CCLOG("[%p]walkBack:pSprite %p",this,pSprite);
    CCPoint Point = pSprite->getPosition();
    Point.y += 32;

    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *pAnimation = pAnimationCache->animationByName("BACK");
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));
    pSprite->stopAllActions();
    pSprite->runAction(pAction);
    
    CCMoveTo* actionMove = CCMoveTo::create(0.5f, Point);
    pSprite->runAction(actionMove);
}

// 左に移動する
void Human::walkLeft(void)
{
    CCSprite* pSprite = (CCSprite*)((CCLayer*)this)->getChildByTag(12);
    CCLOG("[%p]walkLeft:pSprite %p",this,pSprite);
    CCPoint Point = pSprite->getPosition();
    Point.x -= 32;

    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *pAnimation = pAnimationCache->animationByName("LEFT");
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));
    pSprite->stopAllActions();
    pSprite->runAction(pAction);
    
    CCMoveTo* actionMove = CCMoveTo::create(0.5f, Point);
    pSprite->runAction(actionMove);
}

// 右に移動する
void Human::walkRight(void)
{
    CCSprite* pSprite = (CCSprite*)((CCLayer*)this)->getChildByTag(12);
    CCLOG("[%p]walkRight:pSprite %p",this,pSprite);
    CCPoint Point = pSprite->getPosition();
    Point.x += 32;

    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *pAnimation = pAnimationCache->animationByName("RIGHT");
    CCRepeatForever *pAction = CCRepeatForever::create( CCAnimate::create(pAnimation));
    pSprite->stopAllActions();
    pSprite->runAction(pAction);
    
    CCMoveTo* actionMove = CCMoveTo::create(5.5f, Point);
    pSprite->runAction(actionMove);
}





