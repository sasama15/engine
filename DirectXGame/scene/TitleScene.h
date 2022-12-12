#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
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
    Sprite* sprite9 = nullptr;
    Sprite* sprite10 = nullptr;
    Sprite* sprite11 = nullptr;
    Sprite* sprite12 = nullptr;
    Sprite* sprite13 = nullptr;
    Sprite* sprite14 = nullptr;
    Sprite* sprite15 = nullptr;
    int Timer;
    const int Speed = 15;
    int FlashingTimer;

    //Audio::SoundData soundData1;
};

