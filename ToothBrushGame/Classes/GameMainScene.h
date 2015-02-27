//
//  GameMainScene.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/17.
//
//

#ifndef __ToothBrushGame__GameMainScene__
#define __ToothBrushGame__GameMainScene__
#include "cocos2d.h"
#include "GameDifficult.h"
#include "NADView.h"

using namespace cocos2d;

#define GAME_TIME_MAX (60)

class ToothManager;
class EnemyManager;
class PlaqueManager;
class HitChecker;
class UIManager;
class LifeBar;
class EffectManager;
class CountDown;
class ToothPowder;
class VirusToothManager;
class UgaiEffect;

class GameMainScene : public cocos2d::Layer
{
public:
    typedef enum
    {
        SWIPE_DIRECTION_NONE = 0,
        SWIPE_DIRECTION_UP,
        SWIPE_DIRECTION_DOWN,
        SWIPE_DIRECTION_LEFT,
        SWIPE_DIRECTION_RIGHT,
        SWIPE_DIRECTION_MAX,
    }SWIPE_DIRECTION;
    
    GameMainScene(){};
    ~GameMainScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float fTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMainScene);

    void createCountDown(float fTime);
    
private:
    static const int GAME_END_TIME = 5;
    //メンバ関数
    void setResultScene(bool bGameOverFlag = false);
    
    //ゲームのフェーズ更新
    void updateGamePhase(void);
    //現在のフェーズチェック
    void chkGamePhase(void);
    
    bool onTouchBegin(Touch* pTouch,Event* pEvent);
    void onTouchMoved(Touch* pTouch,Event* pEvent);
    void onTouchCancelled(Touch* pTouch,Event* pEvent);
    void onTouchEnded(Touch* pTouch,Event* pEvent);
    void onAcceleration(Acceleration*acc, Event *unused_event);
    static const int SWIPE_PERMISSION_DISTANCE = (3);
    SWIPE_DIRECTION calcSwipeDirection(float fAngle);
    static const int UGAI_DELAY = 60;
    //メンバ変数
    Point m_touchPos;
    Point m_oldTouchPos;
    Vec3 m_acc;
    Vec3 m_oldAcc;
    SWIPE_DIRECTION m_swipeDirection;
    SWIPE_DIRECTION m_oldSwipeDirection;
    EventListenerTouchOneByOne* m_pTouchEventOneByOne;
    ToothManager* m_pToothManager;
    EnemyManager* m_pEnemyManager;
    PlaqueManager* m_pPlaqueManager;
    HitChecker* m_pHitChecker;
    UIManager* m_pUIManager;
    EffectManager* m_EffectManager;
    VirusToothManager* m_pVirusToothManager;
    UgaiEffect* m_pUgaiEffect;
    
    Sprite* m_pBubbleSprite;
    Vec2 m_bubblePos;
    
    int m_nTimer;
    int m_nShakeCnt;
    
    bool m_bMove;
    
    bool m_bHit;

    Layer* m_pCountDown;
    bool m_bCountDownEnd;
    int m_nUgaiCounter;
    
    int m_nGamePhase;//フェーズ数
    int m_nGameTime;//ゲーム終了までのタイム
    
    int m_nGameEndtTime;//ゲーム終了時にカウント

};
#endif /* defined(__ToothBrushGame__GameMainScene__) */
