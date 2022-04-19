#include "TitleScene.h"
#include "Input.h"
#include "DebugText.h"
#include "GamePlayScene.h"
#include "SceneManager.h"

TitleScene::TitleScene(SceneManager* sceneManager)
    :BaseScene(sceneManager)
{
}

void TitleScene::Initialize()
{
#pragma region �V�[������������

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.jpg");

    // �X�v���C�g�̐���
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void TitleScene::Finalize()
{
    // �X�v���C�g�ʉ��
    delete sprite;
}

void TitleScene::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // �X�v���C�g�X�V
    sprite->Update();

    Input* input = Input::GetInstance();

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    if (input->TriggerKey(DIK_RETURN)){
        //�V�[���؂�ւ�
        BaseScene* scene = new GamePlayScene(sceneManager_);
        sceneManager_->SetNextScene(scene);
    }

    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void TitleScene::Draw()
{
    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
    // �X�v���C�g�`��
    sprite->Draw();
}