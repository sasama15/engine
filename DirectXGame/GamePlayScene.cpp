#include "GamePlayScene.h"
#include "Input.h"
#include "DebugText.h"

GamePlayScene::GamePlayScene(SceneManager* sceneManager)
    :BaseScene(sceneManager)
{
}

void GamePlayScene::Initialize()
{
#pragma region �V�[������������

    // OBJ���烂�f���f�[�^��ǂݍ���
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");

    // 3D�I�u�W�F�N�g����
    object3d_1 = Object3d::Create();
    object3d_2 = Object3d::Create();
    object3d_3 = Object3d::Create();

    // �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
    object3d_1->SetModel(model_1);
    object3d_2->SetModel(model_2);
    object3d_3->SetModel(model_2);

    // 3D�I�u�W�F�N�g�̈ʒu���w��
    object3d_2->SetPosition({ -5, 0, -5 });
    object3d_3->SetPosition({ +5, 0, +5 });

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gamePlay.jpg");
    
    // �X�v���C�g�̐���
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    // �����ǂݍ���
    soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void GamePlayScene::Finalize()
{
    // �X�v���C�g�ʉ��
    delete sprite;

     // 3D���f�����
    delete model_1;
    delete model_2;
    delete model_3;
    // 3D�I�u�W�F�N�g���
    delete object3d_1;
    delete object3d_2;
    delete object3d_3;
}

void GamePlayScene::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // 3D�I�u�W�F�N�g�X�V
    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    // �X�v���C�g�X�V
    sprite->Update();

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_0)) // ������0�L�[��������Ă�����
    {
        OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    if (input->PushKey(DIK_SPACE)) {
        object3d_2->SetModel(model_3);
        object3d_3->SetModel(model_3);
    }
    else {
        object3d_2->SetModel(model_2);
        object3d_3->SetModel(model_2);
    }

    if (input->TriggerKey(DIK_P)) {
        // �����Đ�
        Audio::SoundPlayWave(soundData1);
    }

    // �J�����ړ�
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {
        if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
        else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
        if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
        else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
    }

    // �e�I�u�W�F�N�g�̔��a
    const float radius1 = 3.0f;
    const float radisu2 = 3.0f;

    // X���W,Y���W���w�肵�ĕ\��
    DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    // X���W,Y���W,�k�ڂ��w�肵�ĕ\��
    DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void GamePlayScene::Draw()
{
    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
    // �X�v���C�g�`��
    sprite->Draw();

    // 3D�I�u�W�F�N�g�`��O����
    Object3d::PreDraw();

    // 3D�I�u�W�F�N�g�̕`��
    object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();


    // 3D�I�u�W�F�N�g�`��㏈��
    Object3d::PostDraw();

    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
}