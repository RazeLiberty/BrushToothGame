//
//  AchievementDataBase.h
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#ifndef __ToothBrushGame__AchievementDataBase__
#define __ToothBrushGame__AchievementDataBase__
#include <cocos2d.h>
#include "common.h"
USING_NS_CC;
//実績解除種類
enum ACHIEVEMENT_KIND
{
    ACHIEVE_TYPE_NONE = 0,//実績タイプ
    ACHIEVE_TYPE_TURN_ON,//起動回数
    ACHIEVE_TYPE_GAME_PLAY,//プレイ回数
    ACHIEVEMENT_TYPE_ENEMY_DOWN,//倒した敵の総数
    ACHIEVEMENT_TYPE_ENEMY_NORMAL_ONE_DOWN,//普通の種類の敵の倒した数
    ACHIEVEMENT_TYPE_ENEMY_NORMAL_TWO_DOWN,
    ACHIEVEMENT_TYPE_ENEMY_NORMAL_TREE_DOWN,
    ACHIEVEMENT_TYPE_ENEMY_LAIR_ONE_DOWN,//レア種類の敵を倒した数
    ACHIEVEMENT_TYPE_ENEMY_LAIR_TWO_DOWN,
    ACHIEVEMENT_TYPE_ENEMY_LAIR_TREE_DOWN,
    ACHIEVEMENT_TYPE_USE_UGAI,//うがいを使用した回数
    ACHIEVEMENT_TYPE_USE_TOOTHPOWDER,//歯磨きボムを使用した回数
    ACHIEVEMENT_TYPE_USE_TOUP,//タップした回数
    ACHIEVEMENT_TYPE_GAME_TOP_SCORE,//１ゲームのトップスコア
    ACHIEVEMENT_TYPE_GAME_TOP_ENEMY_DOWN,//１ゲームの敵の最高で倒した数
    ACHIEVEMENT_TYPE_GAME_TOP_ENEMY_DOWN_BOM,//１ゲームでボムで倒した敵の数
    ACHIEVEMENT_TYPE_GAME_MIN_USE_BOM,//１ゲームでボムを使用した最も少ない回数
    ACHIEVEMENT_TYPE_GAME_MAX_USE_BOM,//１ゲームでボムを使用した最も多い回数
    ACHIEVEMENT_TYPE_GAME_USE_UGAI,//うがいを使用した回数
    ACHIEVEMENT_TYPE_GAME_MAX_USE_ENEMY_DOWN_BOM,//１ゲームでボム使用で倒した敵で最も多い回数
    ACHIEVEMENT_TYPE_GAME_TIME,//ゲームにかかった最短タイム
    ACHIEVEMENT_TYPE_GAME_ENEMY_NOT_DOWN,//うがいしなかった敵の数
    ACHIEVEMENT_TYPE_TAP_GIRL_TITLE,//タイトルの女の子のタップ回数
    ACHIEVEMENT_TYPE_SWIPE_GIRL_TITLE,//タイトルの女の子のスワイプ回数
    ACHIEVEMENT_TYPE_TAP_GIRL_GAMESTATUS,//ステータスの女の子のタップ回数
    ACHIEVEMENT_TYPE_SWIPE_GIRL_GAMESTATUS,//ステータスの女の子スワイプ回数
    ACHIEVEMENT_MAX//
};

class AchieveLayer;
class AchievementDataBaseList{
public:

    //実績解除条件のデータ構造隊
    struct ACHIEVE_STATUS
    {
        char* name;//保存時の名前
        char* boolname;//保存時のbool名
        ACHIEVEMENT_KIND achieveFlagKind;
        int unlockNum;//解除に必要な数
        std::string title;//実績名
        std::string message;//実績内容
    };

public:
    AchievementDataBaseList(){}
    ~AchievementDataBaseList(){SAFE_DELETE_ARRAY(m_pAchievemntDate);SAFE_DELETE_ARRAY(m_pAchievemntFlag);SAFE_DELETE(m_pAchieveLayer);}
    //初期化
    static void init();
    //実績情報の数
    static int getAchievementMax(void){return m_nAchivementSize;}
    //ゲームデータ入手
    static int getAchieveInfo(int achieve){return m_nAchievementCont[achieve];}
    //実績判定取得
    static bool getAchieveBool(int achieve){return m_pAchievemntFlag[achieve];}
    //実績日付取得
    static std::string getAchieveDate(int achieve){return m_pAchievemntDate[achieve];}
    //実績ゲット
    static ACHIEVE_STATUS getAchievement(int achieveInfo);
    //実績名ゲット
    static std::string getAchievementName(int achieveInfo);

    //実績情報に加算
    static void addAchievement(ACHIEVEMENT_KIND achievement,bool bSave = false);//回数カウント
    //実績情報に挿入
    static void setAchievementMin(ACHIEVEMENT_KIND achievement,int nNum,bool bSave = false);//回数カウント
    static void setAchievementMax(ACHIEVEMENT_KIND achievement,int nNum,bool bSave = false);//回数カウント

    //実績画面表示
    static void dispAchievement(int nUnlcok);
    //保存
    static void saveAchievement(void);
    //ロード
    static void loadAchievement(void);
    //実績条件チェック
    static void chkAchievement(ACHIEVEMENT_KIND achieve);

    static void resetAchievement();

private:
    static int m_nAchivementSize;//解除実績数
    static int m_nAchievementCont[ACHIEVEMENT_MAX];
    static bool* m_pAchievemntFlag;
    static std::string* m_pAchievemntDate;
    static AchieveLayer* m_pAchieveLayer;


};





//実績解除条件

#endif /* defined(__ToothBrushGame__AchievementDataBase__) */