#include "GameEnd.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void GameEnd::Initialize()
{
#pragma region �V�[������������

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gameend.png");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/blackOut.png");

    // �X�v���C�g�̐���
    sprite1 = Sprite::Create(1, { 0, 0 }, false, false);
    blackIn = Sprite::Create(2, { 0, 0 }, false, false);

    // �t�F�C�h�C���p
    fadeInSize = 1280;
    fadeInTime = 0;

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void GameEnd::Finalize()
{
    // �X�v���C�g�ʉ��
    delete sprite1;
    delete blackIn;
}

void GameEnd::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // �X�v���C�g�X�V
    sprite1->Update();
    blackIn->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    // �t�F�C�h�A�E�g
    fadeInTime += 0.008;
    blackIn->SetSize({ (float)fadeInSize,(float)fadeInSize });
    // ��������
    blackIn->SetPosition({ 1280 / 2.0f - (float)fadeInSize / 2,
        720 / 2.0f - (float)fadeInSize / 2, 0 });
    easing::Update(fadeInSize, 0, 10, fadeInTime);

    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //�V�[���؂�ւ�
        //SceneManager::GetInstance()->ChangeScene("TITLE");
        SceneManager::GetInstance()->ChangeScene("STAGESELECT");
    }
    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void GameEnd::Draw()
{
    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
    // �X�v���C�g�`��
    sprite1->Draw();

    blackIn->Draw();
}
