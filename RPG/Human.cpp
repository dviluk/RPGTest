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
        pHuman->autorelease();
        pHuman->retain();
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
    
    return true;
}

// 親ノードにaddCheildする
void Human::addParent(cocos2d::CCNode *pParent)
{
    // キャラクターアニメーション設定
    CCAnimationCache *pAnimationCache = CCAnimationCache::sharedAnimationCache();
    
    // add the sprite as a child to this layer
    pParent->addChild(pSprite, 0);
    
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
}

