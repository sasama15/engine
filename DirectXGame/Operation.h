#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

#pragma once

/// <summary>
/// 説明文
/// </summary>
class Operation : public BaseScene
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
    /// 描画
    /// </summary>
    void Draw() override;

private:
    Sprite* sprite1 = nullptr;
    Sprite* sprite2 = nullptr;

    bool clearConditionFrag;

    int nextTimer;
    //Audio::SoundData soundData1;
};

