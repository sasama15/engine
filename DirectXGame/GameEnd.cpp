#include "GameEnd.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void GameEnd::Initialize()
{
#pragma region シーン初期化処理

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gameend.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/blackOut.png");

    // スプライトの生成
    sprite1 = Sprite::Create(1, { 0, 0 }, false, false);
    blackIn = Sprite::Create(2, { 0, 0 }, false, false);

    // フェイドイン用
    fadeInSize = 1280;
    fadeInTime = 0;

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void GameEnd::Finalize()
{
    // スプライト個別解放
    delete sprite1;
    delete blackIn;
}

void GameEnd::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // スプライト更新
    sprite1->Update();
    blackIn->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    // フェイドアウト
    fadeInTime += 0.008;
    blackIn->SetSize({ (float)fadeInSize,(float)fadeInSize });
    // 中央から
    blackIn->SetPosition({ 1280 / 2.0f - (float)fadeInSize / 2,
        720 / 2.0f - (float)fadeInSize / 2, 0 });
    easing::Update(fadeInSize, 0, 10, fadeInTime);

    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //シーン切り替え
        //SceneManager::GetInstance()->ChangeScene("TITLE");
        SceneManager::GetInstance()->ChangeScene("STAGESELECT");
    }
    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void GameEnd::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite1->Draw();

    blackIn->Draw();
}
