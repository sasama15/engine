#include "StageSelect.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void StageSelect::Initialize()
{
#pragma region �V�[������������

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/stageSelect.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/miniOperation.png");
    SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/select1.png");
    SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/select2.png");
    SpriteCommon::GetInstance()->LoadTexture(5, L"Resources/select3.png");
    SpriteCommon::GetInstance()->LoadTexture(6, L"Resources/select1clear.png");
    SpriteCommon::GetInstance()->LoadTexture(7, L"Resources/select2clear.png");
    SpriteCommon::GetInstance()->LoadTexture(8, L"Resources/select3clear.png");
    SpriteCommon::GetInstance()->LoadTexture(9, L"Resources/frame.png");

    // �X�v���C�g�̐���
    sprite1 = Sprite::Create(1, { 0, 0 }, false, false);
    sprite2 = Sprite::Create(2, { 0, 0 }, false, false);
    sprite3 = Sprite::Create(3, { 0, 0 }, false, false);
    sprite4 = Sprite::Create(4, { 0, 0 }, false, false);
    sprite5 = Sprite::Create(5, { 0, 0 }, false, false);
    sprite6 = Sprite::Create(6, { 0, 0 }, false, false);
    sprite7 = Sprite::Create(7, { 0, 0 }, false, false);
    sprite8 = Sprite::Create(8, { 0, 0 }, false, false);
    sprite9 = Sprite::Create(9, { 0, 0 }, false, false);

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // �傫��
    sprite2->SetSize({ 100, 100 });
    sprite3->SetSize({ 85, 85 });
    sprite4->SetSize({ 70, 70 });
    sprite5->SetSize({ 55, 55 });
    /*sprite6->SetSize({ 40, 40 });
    sprite7->SetSize({ 25, 25 });
    sprite8->SetSize({ 10, 10 });*/
    sprite6->SetSize({ 85, 85 });
    sprite7->SetSize({ 70, 70 });
    sprite8->SetSize({ 55, 55 });
    sprite9->SetSize({ 100, 100 });

    // �ꏊ
    SelectPos = { 400, 200, 0 };
    SelectPos2 = { 500, 550, 0 };
    SelectPos3 = { 550, 400, 0 };

    sprite2->SetPosition({ 750, 500, 0 });
    sprite3->SetPosition({ SelectPos });
    sprite4->SetPosition({ SelectPos2 });
    sprite5->SetPosition({ SelectPos3 });
    /*sprite6->SetPosition({ 600, 375, 0 });
    sprite7->SetPosition({ 650, 350, 0 });
    sprite8->SetPosition({ 700, 250, 0 });*/
    sprite6->SetPosition({ 400, 200, 0 });
    sprite7->SetPosition({ 500, 550, 0 });
    sprite8->SetPosition({ 550, 400, 0 });
    sprite9->SetPosition({ 750, 500, 0 });
}

void StageSelect::Finalize()
{
    // �X�v���C�g�ʉ��
    delete sprite1;
    delete sprite2;
    delete sprite3;
    delete sprite4;
    delete sprite5;
    delete sprite6;
    delete sprite7;
    delete sprite8;
    delete sprite9;
}

void StageSelect::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
        input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
        input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
        if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { SelectPos.y++; }
        if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { SelectPos.y--; }
        if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { SelectPos.x++; }
        if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { SelectPos.x--; }
        //playerFbxObject->SetPosition(PlayerPos);
    }

    // �X�v���C�g�X�V
    sprite1->Update();
    sprite2->Update();
    sprite3->Update();
    sprite4->Update();
    sprite5->Update();
    sprite6->Update();
    sprite7->Update();
    sprite8->Update();
    sprite9->Update();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    //if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
    //    //�V�[���؂�ւ�
    //    SceneManager::GetInstance()->ChangeScene("OPERATION");
    //}
    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //�V�[���؂�ւ�
        SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
    }
    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void StageSelect::Draw()
{
    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
    // �X�v���C�g�`��
    sprite1->Draw();
    sprite2->Draw();
    sprite3->Draw();
    sprite4->Draw();
    sprite5->Draw();
    sprite6->Draw();
    sprite7->Draw();
    sprite8->Draw();
    sprite9->Draw();
}
