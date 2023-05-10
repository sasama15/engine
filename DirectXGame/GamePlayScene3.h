#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Audio.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "ParticleManager.h"
#include "Easing.h"

#include <memory>
#include <math.h>

class GamePlayScene3 : public BaseScene
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


};

