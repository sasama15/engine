#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "Easing.h"

/// <summary>
/// ゲームクリアシーン
/// </summary>
class GameEnd : public BaseScene
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
    Sprite* blackIn = nullptr;

    // blackアウトさせる
    bool blackInFlag = false;

    // フェイドイン用
    double fadeInSize;
    double fadeInTime;

    //Audio::SoundData soundData1;
};


