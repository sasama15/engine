#include "Operation.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void Operation::Initialize()
{
#pragma region シーン初期化処理

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/operation.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/clearCondition.png");

    // スプライトの生成
    sprite1 = Sprite::Create(1, { 0,0 }, false, false);
    sprite2 = Sprite::Create(2, { 0,0 }, false, false);

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void Operation::Finalize()
{
    // スプライト個別解放
    delete sprite1;
    delete sprite2;
}

void Operation::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // スプライト更新
    sprite1->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        clearConditionFrag = true;
    }
    if (clearConditionFrag == true) {
        nextTimer++;
    }
    if (clearConditionFrag == true && nextTimer > 60) {
        if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
            //シーン切り替え
            SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
        }
    }
   
    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void Operation::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite1->Draw();
    if (clearConditionFrag == true) {
        sprite2->Draw();
    }
}
