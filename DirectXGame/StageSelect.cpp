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
    SpriteCommon::GetInstance()->LoadTexture(9, L"Resources/frame.png");

    // スプライトの生成
    stageSelectSprite = Sprite::Create(1, { 0, 0 }, false, false);
    miniOperationSprite = Sprite::Create(2, { 0, 0 }, false, false);
    selectSprite1 = Sprite::Create(3, { 0, 0 }, false, false);
    selectSprite2 = Sprite::Create(4, { 0, 0 }, false, false);
    selectSprite3 = Sprite::Create(5, { 0, 0 }, false, false);
    clearSprite1 = Sprite::Create(6, { 0, 0 }, false, false);
    clearSprite2 = Sprite::Create(7, { 0, 0 }, false, false);
    clearSprite3 = Sprite::Create(8, { 0, 0 }, false, false);
    frameSprite = Sprite::Create(9, { 0, 0 }, false, false);

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 大きさ
    OperationSize = { 150, 150 };

    SelectSize = { 100, 100 };
    SelectSize2 = { 50, 50 };
    SelectSize3 = { 0, 0 };

    ClearSize = { 100, 100 };
    ClearSize2 = { 50, 50 };
    ClearSize3 = { 0, 0 };



    miniOperationSprite->SetSize({ OperationSize });
    selectSprite1->SetSize({ SelectSize });
    selectSprite2->SetSize({ SelectSize2 });
    selectSprite3->SetSize({ SelectSize3 });
    /*sprite6->SetSize({ 40, 40 });
    sprite7->SetSize({ 25, 25 });
    sprite8->SetSize({ 10, 10 });*/
    clearSprite1->SetSize({ ClearSize });
    clearSprite2->SetSize({ ClearSize2 });
    clearSprite3->SetSize({ ClearSize3 });
    frameSprite->SetSize({ 150, 150 });

    // 場所
    FramePos = { 750, 200, 0 };
    OperationPos = { 750, 200, 0 };
    Select1Pos = { 400, 200, 0 };
    Select2Pos = { 500, 200, 0 };
    Select3Pos = { 600, 200, 0 };

    miniOperationSprite->SetPosition({ OperationPos });
    selectSprite1->SetPosition({ Select1Pos });
    selectSprite2->SetPosition({ Select2Pos });
    selectSprite3->SetPosition({ Select3Pos });
    /*sprite6->SetPosition({ 600, 375, 0 });
    sprite7->SetPosition({ 650, 350, 0 });
    sprite8->SetPosition({ 700, 250, 0 });*/
    clearSprite1->SetPosition({ 400, 200, 0 });
    clearSprite2->SetPosition({ 500, 200, 0 });
    clearSprite3->SetPosition({ 600, 200, 0 });
    frameSprite->SetPosition({ FramePos });

    OperationFlag = true;
    select1Flag = true;
    select2Flag = true;
    select3Flag = false;
    clear1Flag = false;
    clear2Flag = false;
    clear3Flag = false;
}

void StageSelect::Finalize()
{
    // スプライト個別解放
    delete stageSelectSprite;
    delete miniOperationSprite;
    delete selectSprite1;
    delete selectSprite2;
    delete selectSprite3;
    delete clearSprite1;
    delete clearSprite2;
    delete clearSprite3;
    delete frameSprite;
}

void StageSelect::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    Input* input = Input::GetInstance();

    //if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
    //    input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
    //    input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
    //    if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { SelectPos.y++; }
    //    if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { SelectPos.y--; }
    //    if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { SelectPos.x++; }
    //    if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { SelectPos.x--; }
    //    //playerFbxObject->SetPosition(PlayerPos);
    //}

   if (input->PushKey(DIK_W)) {
        OperationSize.x++, OperationSize.y++;
        SelectSize.x++, SelectSize.y++;
        SelectSize2.x++, SelectSize2.y++;
        SelectSize3.x++, SelectSize3.y++;
   }

   if (input->PushKey(DIK_S)) {
       OperationSize.x--, OperationSize.y--;
        SelectSize.x--, SelectSize.y--;
        SelectSize2.x--, SelectSize2.y--;
        SelectSize3.x--, SelectSize3.y--;
   }

   miniOperationSprite->SetSize({ OperationSize.x, OperationSize.y });
    selectSprite1->SetSize({ SelectSize.x,SelectSize.y });
    selectSprite2->SetSize({ SelectSize2.x,SelectSize2.y });
    selectSprite3->SetSize({ SelectSize3.x,SelectSize3.y });

    if (input->PushKey(DIK_W)) {
        if (OperationSize.x > 0 && OperationSize.y > 0) {
            OperationFlag = true;
        }
        if (OperationSize.x >= 160 && OperationSize.y >= 160) {
            OperationFlag = false;
        }
    }
    if (input->PushKey(DIK_S)) {
        if (OperationSize.x <= 160 && OperationSize.y <= 160) {
            OperationFlag = true;
        }
        if (OperationSize.x <= 0 && OperationSize.y <= 0) {
            OperationFlag = false;
        }
    }

    if (input->PushKey(DIK_W)) {
        if (SelectSize.x > 0 && SelectSize.y > 0) {
            select1Flag = true;
        }
        if (SelectSize.x >= 160 && SelectSize.y >= 160) {
            select1Flag = false;
        }
    }
    if (input->PushKey(DIK_S)) {
        if (SelectSize.x <= 160 && SelectSize.y <= 160) {
            select1Flag = true;
        }
        if (SelectSize.x <= 0 && SelectSize.y <= 0) {
            select1Flag = false;
        }
    }

    if (input->PushKey(DIK_W)) {
        if (SelectSize2.x > 0 && SelectSize2.y > 0) {
            select2Flag = true;
        }
        if (SelectSize2.x > 160 && SelectSize2.y > 160) {
            select2Flag = false;
        }
    }
    if (input->PushKey(DIK_S)) {
        if (SelectSize2.x <= 160 && SelectSize2.y <= 160) {
            select2Flag = true;
        }
        if (SelectSize2.x <= 0 && SelectSize2.y <= 0) {
            select2Flag = false;
        }
    }

    if (input->PushKey(DIK_W)) {
        if (SelectSize3.x > 0 && SelectSize3.y > 0) {
            select3Flag = true;
        }
        if (SelectSize3.x >= 160 && SelectSize3.y >= 160) {
            select3Flag = false;
        }
    }
    if (input->PushKey(DIK_S)) {
        if (SelectSize3.x <= 160 && SelectSize3.y <= 160) {
            select3Flag = true;
        }
        if (SelectSize3.x <= 0 && SelectSize3.y <= 0) {
            select3Flag = false;
        }
    }


    if (OperationSize.x >= 140 && OperationSize.y >= 140
        && OperationSize.x <= 160 && OperationSize.y <= 160) {
        frameSprite->SetPosition({ OperationPos });
        if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
            //シーン切り替え
            SceneManager::GetInstance()->ChangeScene("OPERATION");
        }
    }

    if (SelectSize.x >= 140 && SelectSize.y >= 140
        && SelectSize.x <= 160 && SelectSize.y <= 160) {
        frameSprite->SetPosition({ Select1Pos });
        if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
            //シーン切り替え
            SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
        }
    }
    if (SelectSize2.x >= 140 && SelectSize2.y >= 140
        && SelectSize2.x <= 160 && SelectSize2.y <= 160) {
        frameSprite->SetPosition({ Select2Pos });
        if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
            //シーン切り替え
            SceneManager::GetInstance()->ChangeScene("GAMEPLAY2");
        }
    }
    if (SelectSize3.x >= 140 && SelectSize3.y >= 140
        && SelectSize3.x <= 160 && SelectSize3.y <= 160) {
        frameSprite->SetPosition({ Select3Pos });
    }

    // スプライト更新
    stageSelectSprite->Update();
    miniOperationSprite->Update();
    selectSprite1->Update();
    selectSprite2->Update();
    selectSprite3->Update();
    clearSprite1->Update();
    clearSprite2->Update();
    clearSprite3->Update();
    frameSprite->Update();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    //if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
    //    //シーン切り替え
    //    SceneManager::GetInstance()->ChangeScene("OPERATION");
    //}
    //if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
    //    //シーン切り替え
    //    //SceneManager::GetInstance()->ChangeScene("OPERATION");
    //    //SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    //    SceneManager::GetInstance()->ChangeScene("GAMEPLAY2");
    //}

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void StageSelect::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    stageSelectSprite->Draw();

    if (OperationFlag == true) {
        miniOperationSprite->Draw();
    }

    if (select1Flag == true) {
        selectSprite1->Draw();
    }
    if (select2Flag == true) {
        selectSprite2->Draw();
    }
   /* if (select3Flag == true) {
        selectSprite3->Draw();
    }*/

    if (clear1Flag == true) {
        clearSprite1->Draw();
    }
    if (clear2Flag == true) {
        clearSprite2->Draw();
    }
    /*if (clear3Flag == true) {
        clearSprite3->Draw();
    }*/
    
    frameSprite->Draw();
}
