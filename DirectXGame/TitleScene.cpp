#include "TitleScene.h"
#include "Input.h"
#include "DebugText.h"
#include "GamePlayScene.h"
#include "SceneManager.h"

TitleScene::TitleScene(SceneManager* sceneManager)
    :BaseScene(sceneManager)
{
}

void TitleScene::Initialize()
{
#pragma region シーン初期化処理

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.jpg");

    // スプライトの生成
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void TitleScene::Finalize()
{
    // スプライト個別解放
    delete sprite;
}

void TitleScene::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // スプライト更新
    sprite->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->TriggerKey(DIK_RETURN)){
        //シーン切り替え
        BaseScene* scene = new GamePlayScene(sceneManager_);
        sceneManager_->SetNextScene(scene);
    }

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void TitleScene::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite->Draw();
}