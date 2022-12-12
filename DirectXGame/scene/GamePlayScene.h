#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"

#include <memory>

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GamePlayScene : public BaseScene
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
    Sprite* sprite = nullptr;
    //std::unique_ptr<Sprite> sprite;

   /* Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;*/

    std::unique_ptr<Model> model_1;
    std::unique_ptr<Model> model_2;
    std::unique_ptr<Model> model_3;

    /*Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;*/

    //ユニークポインタ(一つだけのため)
    // nullptrは勝手に入るため必要ない
    /*std::unique_ptr<Object3d> object3d_1;
    std::unique_ptr<Object3d> object3d_2;
    std::unique_ptr<Object3d> object3d_3;*/

    // shared_ptr使う場合
    std::shared_ptr<Object3d> object3d_1;
    std::shared_ptr<Object3d> object3d_2;
    std::shared_ptr<Object3d> object3d_3;

    // weak_ptr使う場合
    /*std::weak_ptr<Object3d> object3d_1;
    std::weak_ptr<Object3d> object3d_2;
    std::weak_ptr<Object3d> object3d_3;*/

    // shared_ptr(共有するときに使う)
    // weak_ptr(追尾弾に使う)

    Audio::SoundData soundData1;

    std::unique_ptr<ObjectManager> objectManager_;

    FbxModel* fbxModel1 = nullptr;
    FbxModel* fbxModel2 = nullptr;
    FbxModel* fbxModel3 = nullptr;
    FbxObject3d* fbxObject1 = nullptr;
    FbxObject3d* fbxObject2 = nullptr;
    FbxObject3d* fbxObject3 = nullptr;
    FbxObject3d* fbxObject4 = nullptr;

    DebugCamera* camera;

    XMFLOAT3 PlayerPos;
    XMFLOAT3 EnemyPos;
    XMFLOAT3 EnemyPos2;
    XMFLOAT3 EnemyPos3;

    XMFLOAT3 OldEnemyPos;
    XMFLOAT3 OldEnemyPos2;
    XMFLOAT3 OldEnemyPos3;

    // 敵1
    bool EnemyJump;
    float Gravity;
    float Angle;
    float Ax;
    float Az;

    // 敵2
    bool EnemyJump2;
    float Gravity2;
    float Angle2;
    float Ax2;
    float Az2;

    // 敵3
    bool EnemyJump3;
    float Gravity3;
    float Angle3;
    float Ax3;
    float Az3;

    // 当たり判定
    //Sphere spherePlayer;
    //Sphere sphereEnemy;
    bool flag;
    bool flag2;
    bool flag3;
};

