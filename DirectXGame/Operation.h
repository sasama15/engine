#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

#pragma once

/// <summary>
/// à–¾•¶
/// </summary>
class Operation : public BaseScene
{
public:
    /// <summary>
    /// ‰Šú‰»
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// I—¹
    /// </summary>
    void Finalize() override;

    /// <summary>
    /// –ˆƒtƒŒ[ƒ€ˆ—
    /// </summary>
    void Update() override;

    /// <summary>
    /// •`‰æ
    /// </summary>
    void Draw() override;

private:
    Sprite* sprite1 = nullptr;
    Sprite* sprite2 = nullptr;

    bool clearConditionFrag;

    int nextTimer;
    //Audio::SoundData soundData1;
};

