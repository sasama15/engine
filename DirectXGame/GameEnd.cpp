#include "GameEnd.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"

void GameEnd::Initialize()
{
#pragma region �V�[������������

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gameend.png");

    // �X�v���C�g�̐���
    sprite1 = Sprite::Create(1, { 0,0 }, false, false);

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void GameEnd::Finalize()
{
    // �X�v���C�g�ʉ��
    delete sprite1;
}

void GameEnd::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // �X�v���C�g�X�V
    sprite1->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    if (input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //�V�[���؂�ւ�
        SceneManager::GetInstance()->ChangeScene("TITLE");
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
}
