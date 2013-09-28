//
//  Human.h
//  RPG
//
//  Created by keizi on 2013/09/16.
//
//

#ifndef __RPG__Human__
#define __RPG__Human__

#include "cocos2d.h"

class Human
{
public:
    // 生成メソッド
    static Human* create(const char *pFileName);

    // 初期化メソッド(cretaメソッド経由でコールする)
    bool initWithFile(const char *pFileName);
    
    // 親ノードにaddCheilする
    void addParent(cocos2d::CCNode *pParent, int iTag);
    
    // 座標指定
    void setPosition(const cocos2d::CCPoint& pos);
    
    // 歩き回る
    void walkAround(cocos2d::CCNode* parent, bool flag);
    
    void walkRamdom(void);
    
private:
    // プレイヤー向き
    const int PLAYER_FRONT = 1;
    const int PLAYER_BACK  = 2;
    const int PLAYER_LEFT  = 3;
    const int PLAYER_RIGHT = 4;
    
     // ピースの横幅/縦幅
    const int X_SIZE = 96;
    const int Y_SIZE = 64;
        
    // プレイヤーの向き管理
    int PlayerDirectcion = PLAYER_FRONT;
    
    // テクスチャ(前後左右の歩きパターン)
    cocos2d::CCSprite* pSprite;
    
    cocos2d::CCLayer* pLayer;
    
    int tag;
    
    // 前後左右のアニメーション格納する
    cocos2d::CCAnimation* pAnimationFront;
    cocos2d::CCAnimation* pAnimationBack;
    cocos2d::CCAnimation* pAnimationLeft;
    cocos2d::CCAnimation* pAnimationRight;
    
    // スプライトフレーム格納用
    cocos2d::CCArray* pSpriteFrameArray;
    
    // キャラクタの座標
    cocos2d::CCPoint Point;

    // 前に移動する
    void walkFront(int step);
    
    // 後ろに移動する
    void walkBack(int step);
    
    // 左に移動する
    void walkLeft(int step);
    
    // 右に移動する
    void walkRight(int step);
};

#endif /* defined(__RPG__Human__) */
