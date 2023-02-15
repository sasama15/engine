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

    // プレイヤー
    FbxObject3d* playerFbxObject = nullptr;
    // イエティ
    FbxObject3d* yetiFbxObject = nullptr;

    // プレイヤーポジション
    XMFLOAT3 PlayerPos;
    // イエティポジション
    XMFLOAT3 YetiPos;

    // プレイヤーフラグ
    bool playerFlag = false;
    // イエティフラグ
    bool yetiFlag = false;
    // エンドフラグ
    bool endFlag = false;

    DebugCamera* camera;
};

