#include "TitleScene.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

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

    if (input->TriggerKey(DIK_RETURN) || input->TriggerButton(static_cast<int>(Button::BACK))){
        //シーン切り替え
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
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