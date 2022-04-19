#pragma once

// 前方宣言
class SceneManager;

/// <summary>
/// シーン基底
/// </summary>
class BaseScene
{
public:
    BaseScene(SceneManager* sceneManager);

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

//private:
protected:
    // シーンマネージャー(借りてくる)
    SceneManager* sceneManager_ = nullptr;
};

