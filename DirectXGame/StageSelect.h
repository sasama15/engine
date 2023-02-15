#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

#pragma once

/// <summary>
/// ステージセレクト
/// </summary>
class StageSelect : public BaseScene
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
    Sprite* sprite3 = nullptr;
    Sprite* sprite4 = nullptr;
    Sprite* sprite5 = nullptr;
    Sprite* sprite6 = nullptr;
    Sprite* sprite7 = nullptr;
    Sprite* sprite8 = nullptr;

    bool miniOperationFrag;
    bool select1Frag;
    bool select2Frag;
    bool select3Frag;
    bool clear1Frag;
    bool clear2Frag;
    bool clear3Frag;

    //Audio::SoundData soundData1;
};

