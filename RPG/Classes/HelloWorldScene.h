#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    /*================================================
                            定数
    ================================================*/
    // マップのタグ
    const int TAG_MAP = 10;
    
    // プレイヤー向き
    const int PLAYER_FRONT = 1;
    const int PLAYER_BACK  = 2;
    const int PLAYER_LEFT  = 3;
    const int PLAYER_RIGHT = 4;

    /*================================================
                            変数
    ================================================*/
    // プレイヤーの向き管理
    int PlayerDirectcion = PLAYER_FRONT;

    // プレイヤーのスプライト管理
    cocos2d::CCSprite *pPlayer;
    
    // プレイヤーのアニメーション管理
    cocos2d::CCAnimation *pAnimation;

    // 座標管理
    cocos2d::CCPoint m_StartPoint;
    cocos2d::CCPoint m_Delta;
    
    /*================================================
                          メソッド
    ================================================*/
    
    // タッチイベントメソッド
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // 更新処理
    void update(float delta);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
