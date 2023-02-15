#include "StageSelect.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void StageSelect::Initialize()
{
#pragma region シーン初期化処理

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/stageSelect.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/miniOperation.png");
    SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/select1.png");
    SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/select2.png");
    SpriteCommon::GetInstance()->LoadTexture(5, L"Resources/select3.png");
    SpriteCommon::GetInstance()->LoadTexture(6, L"Resources/select1clear.png");
    SpriteCommon::GetInstance()->LoadTexture(7, L"Resources/select2clear.png");
    SpriteCommon::GetInstance()->LoadTexture(8, L"Resources/select3clear.png");

    // スプライトの生成
    sprite1 = Sprite::Create(1, { 0,0 }, false, false);
    sprite2 = Sprite::Create(2, { 0,0 }, false, false);
    sprite3 = Sprite::Create(3, { 0,0 }, false, false);
    sprite4 = Sprite::Create(4, { 0,0 }, false, false);
    sprite5 = Sprite::Create(5, { 0,0 }, false, false);
    sprite6 = Sprite::Create(6, { 0,0 }, false, false);
    sprite7 = Sprite::Create(7, { 0,0 }, false, false);
    sprite8 = Sprite::Create(8, { 0,0 }, false, false);

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 大きさ
    sprite2->SetSize({ 50, 50 });
}

void StageSelect::Finalize()
{
    // スプライト個別解放
    delete sprite1;
    delete sprite2;
    delete sprite3;
    delete sprite4;
    delete sprite5;
    delete sprite6;
    delete sprite7;
    delete sprite8;
}

void StageSelect::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // スプライト更新
    sprite1->Update();
    sprite2->Update();
    sprite3->Update();
    sprite4->Update();
    sprite5->Update();
    sprite6->Update();
    sprite7->Update();
    sprite8->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    //if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
    //    //シーン切り替え
    //    SceneManager::GetInstance()->ChangeScene("OPERATION");
    //}
    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //シーン切り替え
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    }
    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void StageSelect::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite1->Draw();
    sprite2->Draw();
    sprite3->Draw();
    /*sprite4->Draw();
    sprite5->Draw();
    sprite6->Draw();
    sprite7->Draw();
    sprite8->Draw();*/
}
