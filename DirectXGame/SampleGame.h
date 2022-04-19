#pragma once

#include "Framework.h"

//#include "IScene.h"

//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXcommon.h"
//#include "Object3d.h"
//#include "Model.h"
//#include "Sprite.h"
//#include "Audio.h"
//#include "DebugText.h"

#include <vector>

//class GamePlayScene;
//class TitleScene;

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
    /// HPバーなどの表示物
    /// </summary>
    //void DrawUI();

private:
    // シーン
    //GamePlayScene* scene_ = nullptr;
    //TitleScene* scene_ = nullptr;
    //IScene* scene_ = nullptr;
};

