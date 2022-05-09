#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXcommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "Audio.h"
#include "DebugText.h"
#include "SceneManager.h"

/// <summary>
/// フレームワーク
/// </summary>
class Framework
{
public:
    /// <summary>
    /// 実行
    /// </summary>
    void Run();

    /// <summary>
   /// 初期化
   /// </summary>
    virtual void Initialize();

    /// <summary>
    /// 終了
    /// </summary>
    virtual void Finalize();

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    virtual void Update();

    /// <summary>
    /// 描画
    /// </summary>
    //virtual void Draw() = 0;
    virtual void Draw();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    virtual bool IsEndRequst() { return endRequst_; }

//private:
protected:
    bool endRequst_ = false;

    WinApp* winApp = nullptr;
    DirectXcommon* dxCommon = nullptr;
    Input* input = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;
    Audio::SoundData soundData1;
};

