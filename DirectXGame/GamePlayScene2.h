#pragma once

#include "BaseScene.h"
#include "Sprite.h"
//#include "Object3d.h"
#include "Audio.h"
//#include "ObjectManager.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "ParticleManager.h"

#include <memory>
#include <math.h>

class GamePlayScene2 : public BaseScene
{ 
public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// 終了
    /// </summary>
    void Finalize() override;

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    void Update() override;

    /// <summary>
    /// 当たり判定
    /// </summary>
    /// <param name="playerCircle">プレイヤー範囲</param>
    /// <param name="enemyCircle">エネミー範囲</param>
    /// <param name="playerR">プレイヤー半径</param>
    /// <param name="enemyR">エネミー半径</param>
    /// <returns></returns>
    bool OnCollisionCircle(FbxObject3d* playerCircle, FbxObject3d* enemyCircle, float playerR, float enemyR);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

private:
    // 各UI
    Sprite* title = nullptr;
    Sprite* hp = nullptr;
    Sprite* hp2 = nullptr;
    Sprite* hp3 = nullptr;
    Sprite* end = nullptr;

    // BGM
    Audio::SoundData soundData1;

    // プレイヤー
    FbxModel* playerFbxModel = nullptr;
    // イエティ
    FbxModel* yetiFbxModel = nullptr;
    // 弾
    FbxModel* bulletFbxModel = nullptr;
    FbxModel* universeFbxModel = nullptr;

    // プレイヤー
    FbxObject3d* playerFbxObject = nullptr;
    // イエティ
    FbxObject3d* yetiFbxObject = nullptr;
    // 弾
    //FbxObject3d* bulletFbxObject = nullptr;

    // 弾
    FbxObject3d* bulletFbxObject[5];
    FbxObject3d* universeFbxObject;

    // パーティクル
    //std::unique_ptr<Model> model_particle;
    // shared_ptr使う場合
    /*std::shared_ptr<ParticleManager> object_particle;
    std::unique_ptr<ParticleObjectManager> particleObjectManager_;*/
    ParticleManager* particleMan = nullptr;
    ParticleManager* particleSmoke = nullptr;
    ParticleManager* particleGone = nullptr;
    ParticleManager* particleSnow = nullptr;
    ParticleManager* particleBlood = nullptr;

    // プレイヤーローテーション
    XMFLOAT3 PlayerRotation;

    // プレイヤーポジション
    XMFLOAT3 PlayerPos;
    // イエティポジション
    XMFLOAT3 YetiPos;
    // 弾
    //XMFLOAT3 BulletPos;
    // プレイヤーポジション(プレイヤーが居た場所)
    XMFLOAT3 oldPlayerPos[5];
    XMFLOAT3 oldPlayerPos2;
    // 弾
    XMFLOAT3 BulletPos[5];
    XMFLOAT3 UniversePos;

    // 弾の最大数
    const int iceMax = 5;

    // プレイヤーフラグ
    bool playerFlag = false;
    // イエティフラグ
    bool yetiFlag = false;
    // クリアフラグ
    bool clearFlag = false;
    // エンドフラグ
    bool endFlag = false;
    // 弾フラグ
    /*bool bulletFlag = false;
    bool bulletFlag2 = false;
    bool bulletFlag3 = false;
    bool bulletFlag4 = false;
    bool bulletFlag5 = false;*/

    bool bulletFlag[5];
    // 弾撃つ
    bool shootFlag = false;
    /*bool shootFlag2 = false;
    bool shootFlag3 = false;
    bool shootFlag4 = false;
    bool shootFlag5 = false;*/

    // アニメーションフラグ
    bool walkAnimationFlag = false;
    bool attackAnimationFlag = false;

    // 突撃
    //bool onrushFlag = false;
    //敵転がる
    bool rollingFlag = false;

    // 時間止めてる時の画像描画フラグ
    bool stopFlag = false;
    bool stopFlag2 = false;

    // パーティクルフラグ
    bool particleFlag = false;

    // 弾をジャンプ
    bool BulletJump;
    bool BulletJump2;
    bool BulletJump3;
    bool BulletJump4;
    bool BulletJump5;

    // 弾のスピード
    int bulletSpeed;

    // 弾の時
    int iceBulletTimer;

    // 転がる時間
    int rollingTimer;
    int rollingNum;

    // 時間止める
    int stopTimer;
    int clearStopTimer;

    float BulletGravity[5];
    float BulletJampPower;

    DebugCamera* camera;
};

