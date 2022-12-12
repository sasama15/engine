#include "TitleScene.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void TitleScene::Initialize()
{
#pragma region シーン初期化処理

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title1.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/title2.png");
    SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/title3.png");
    SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/title4.png");
    SpriteCommon::GetInstance()->LoadTexture(5, L"Resources/title5.png");
    SpriteCommon::GetInstance()->LoadTexture(6, L"Resources/title6.png");
    SpriteCommon::GetInstance()->LoadTexture(7, L"Resources/title7.png");
    SpriteCommon::GetInstance()->LoadTexture(8, L"Resources/title8.png");
    SpriteCommon::GetInstance()->LoadTexture(9, L"Resources/title9.png");
    SpriteCommon::GetInstance()->LoadTexture(10, L"Resources/title10.png");
    SpriteCommon::GetInstance()->LoadTexture(11, L"Resources/title11.png");
    SpriteCommon::GetInstance()->LoadTexture(12, L"Resources/title12.png");
    SpriteCommon::GetInstance()->LoadTexture(13, L"Resources/title13.png");
    SpriteCommon::GetInstance()->LoadTexture(14, L"Resources/title14.png");
    SpriteCommon::GetInstance()->LoadTexture(15, L"Resources/title15.png");

    // スプライトの生成
    sprite1 = Sprite::Create(1, { 0,0 }, false, false);
    sprite2 = Sprite::Create(2, { 0,0 }, false, false);
    sprite3 = Sprite::Create(3, { 0,0 }, false, false);
    sprite4 = Sprite::Create(4, { 0,0 }, false, false);
    sprite5 = Sprite::Create(5, { 0,0 }, false, false);
    sprite6 = Sprite::Create(6, { 0,0 }, false, false);
    sprite7 = Sprite::Create(7, { 0,0 }, false, false);
    sprite8 = Sprite::Create(8, { 0,0 }, false, false);
    sprite9 = Sprite::Create(9, { 0,0 }, false, false);
    sprite10 = Sprite::Create(10, { 0,0 }, false, false);
    sprite11 = Sprite::Create(11, { 0,0 }, false, false);
    sprite12 = Sprite::Create(12, { 0,0 }, false, false);
    sprite13 = Sprite::Create(13, { 0,0 }, false, false);
    sprite14 = Sprite::Create(14, { 0,0 }, false, false);
    sprite15 = Sprite::Create(15, { 0,0 }, false, false);

    Timer = 0;
    FlashingTimer = 0;

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void TitleScene::Finalize()
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
    delete sprite9;
    delete sprite10;
    delete sprite11;
    delete sprite12;
    delete sprite13;
    delete sprite14;
    delete sprite15;
}

void TitleScene::Update()
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
    sprite9->Update();
    sprite10->Update();
    sprite11->Update();
    sprite12->Update();
    sprite13->Update();
    sprite14->Update();
    sprite15->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))){
        //シーン切り替え
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    }

    Timer++;
    if (Timer >= Speed * 13) {
        Timer = Speed * 13;
        FlashingTimer++;
    }
    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void TitleScene::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite1->Draw();
    if (Timer >= Speed * 0) {
        sprite2->Draw();
    }
    if (Timer >= Speed * 1) {
        sprite3->Draw();
    }
    if (Timer >= Speed * 2) {
        sprite4->Draw();
    }
    if (Timer >= Speed * 3) {
        sprite5->Draw();
    }
    if (Timer >= Speed * 4) {
        sprite6->Draw();
    }
    if (Timer >= Speed * 5) {
        sprite7->Draw();
    }
    if (Timer >= Speed * 6) {
        sprite8->Draw();
    }
    if (Timer >= Speed * 7) {
        sprite9->Draw();
    }
    if (Timer >= Speed * 8) {
        sprite10->Draw();
    }
    if (Timer >= Speed * 9) {
        sprite11->Draw();
    }
    if (Timer >= Speed * 10) {
        sprite12->Draw();
    }
    if (Timer >= Speed * 11) {
        sprite13->Draw();
    }
    if (Timer >= Speed * 12) {
        sprite14->Draw();
    }
    if (Timer >= Speed * 13) {
        if (FlashingTimer % 80 >= 40) return;
        sprite15->Draw();
    }
}