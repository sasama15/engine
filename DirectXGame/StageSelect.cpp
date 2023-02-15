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

    // �X�v���C�g�̐���
    sprite1 = Sprite::Create(1, { 0,0 }, false, false);
    sprite2 = Sprite::Create(2, { 0,0 }, false, false);
    sprite3 = Sprite::Create(3, { 0,0 }, false, false);
    sprite4 = Sprite::Create(4, { 0,0 }, false, false);
    sprite5 = Sprite::Create(5, { 0,0 }, false, false);
    sprite6 = Sprite::Create(6, { 0,0 }, false, false);
    sprite7 = Sprite::Create(7, { 0,0 }, false, false);
    sprite8 = Sprite::Create(8, { 0,0 }, false, false);

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // �傫��
    sprite2->SetSize({ 50, 50 });
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
}

void StageSelect::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // �X�v���C�g�X�V
    sprite1->Update();
    sprite2->Update();
    sprite3->Update();
    sprite4->Update();
    sprite5->Update();
    sprite6->Update();
    sprite7->Update();
    sprite8->Update();

    Input* input = Input::GetInstance();

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
    /*sprite4->Draw();
    sprite5->Draw();
    sprite6->Draw();
    sprite7->Draw();
    sprite8->Draw();*/
}
