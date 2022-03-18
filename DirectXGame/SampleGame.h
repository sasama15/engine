#pragma once

#include "Framework.h"

//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXcommon.h"
//#include "Object3d.h"
//#include "Model.h"
//#include "Sprite.h"
//#include "Audio.h"
//#include "DebugText.h"

#include <vector>

/// <summary>
/// ゲーム固有のクラス(ここは作るゲームの名前を入れ、毎回作る)
/// </summary>
class SampleGame : public Framework
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

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    //bool IsEndRequst() { return endRequst_; }

private:
   /* bool endRequst_ = false;

    WinApp* winApp = nullptr;
    DirectXcommon* dxCommon = nullptr;
    Input* input = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;*/

    std::vector<Sprite*> sprites;

    Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;

    Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;

   /* Audio::SoundData soundData1;*/
};

