#pragma once

/// <summary>
/// シーンインターフェイス
/// </summary>
class IScene
{
public:

    /// <summary>
    /// 初期化
    /// </summary>
    virtual void Initialize() = 0;  // virtualと0をつけることによって純粋仮想関数になる

    /// <summary>
    /// 終了
    /// </summary>
    virtual void Finalize() = 0;

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() = 0;
};

