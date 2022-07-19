#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"

#include <memory>

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GamePlayScene : public BaseScene
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
    Sprite* sprite = nullptr;
    //std::unique_ptr<Sprite> sprite;

   /* Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;*/

    std::unique_ptr<Model> model_1;
    std::unique_ptr<Model> model_2;
    std::unique_ptr<Model> model_3;

    /*Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;*/

    //ユニークポインタ(一つだけのため)
    // nullptrは勝手に入るため必要ない
    /*std::unique_ptr<Object3d> object3d_1;
    std::unique_ptr<Object3d> object3d_2;
    std::unique_ptr<Object3d> object3d_3;*/

    // shared_ptr使う場合
    std::shared_ptr<Object3d> object3d_1;
    std::shared_ptr<Object3d> object3d_2;
    std::shared_ptr<Object3d> object3d_3;

    // weak_ptr使う場合
    /*std::weak_ptr<Object3d> object3d_1;
    std::weak_ptr<Object3d> object3d_2;
    std::weak_ptr<Object3d> object3d_3;*/

    // shared_ptr(共有するときに使う)
    // weak_ptr(追尾弾に使う)

    Audio::SoundData soundData1;

    std::unique_ptr<ObjectManager> objectManager_;

    FbxModel* fbxModel1 = nullptr;
    FbxModel* fbxModel2 = nullptr;
    FbxObject3d* fbxObject1 = nullptr;
    FbxObject3d* fbxObject2 = nullptr;

    DebugCamera* camera;
};

