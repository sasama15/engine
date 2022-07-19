#pragma once

#include "Framework.h"

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
    /// HPバーなどの表示物
    /// </summary>
    //void DrawUI();

private:
};

