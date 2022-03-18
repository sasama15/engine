#include "SampleGame.h"

void SampleGame::Initialize()
{
    // ���N���X�̏���������
    Framework::Initialize();

#pragma region WindowsAPI������
    MSG msg{};  // ���b�Z�[�W

#pragma region DirectX����������
    // DirectX�����������@��������
#ifdef _DEBUG
    //�f�o�b�O���C���[���I����
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }
#endif

    HRESULT result;

    // DirectX�����������@�����܂�
#pragma endregion DirectX����������

#pragma region �`�揉��������
    //// 3D�I�u�W�F�N�g�ÓI������
    
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
    spriteCommon->LoadTexture(1, L"Resources/texture.png");
    spriteCommon->LoadTexture(2, L"Resources/house.png");

    // �X�v���C�g�̐���
    for (int i = 0; i < 20; i++)
    {
        int texNumber = 1;
        Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

        // �X�v���C�g�̍��W�ύX
        sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });

        sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });

        // ���_�o�b�t�@�ɔ��f
        sprite->TransferVertexBuffer();

        sprites.push_back(sprite);
    }

#pragma endregion �`�揉��������
}

void SampleGame::Finalize()
{
    // �X�v���C�g�ʉ��
    for (auto& sprite : sprites) {
        delete sprite;
    }
    sprites.clear();

    // 3D���f�����
    delete model_1;
    delete model_2;
    delete model_3;
    // 3D�I�u�W�F�N�g���
    delete object3d_1;
    delete object3d_2;
    delete object3d_3;

    // ���N���X�̏I������
    Framework::Finalize();
}

void SampleGame::Update()
{
    // ���N���X�̍X�V����
    Framework::Update();

#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // 3D�I�u�W�F�N�g�X�V
    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    // �X�v���C�g�X�V
    for (auto& sprite : sprites) {
        sprite->Update();
    }

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
    debugText->Print("Hello,DirectX!!", 200, 100);
    // X���W,Y���W,�k�ڂ��w�肵�ĕ\��
    debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void SampleGame::Draw()
{
#pragma region �O���t�B�b�N�X�R�}���h
    // �`��O����
    dxCommon->PreDraw();

    // 3D�I�u�W�F�N�g�`��O����
    Object3d::PreDraw(dxCommon->GetCmdList());

    // 3D�I�u�W�F�N�g�̕`��
    object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();


    // 3D�I�u�W�F�N�g�`��㏈��
    Object3d::PostDraw();

    // �X�v���C�g���ʃR�}���h
    spriteCommon->PreDrow();
    // �X�v���C�g�`��
    for (auto& sprite : sprites) {
        sprite->Draw();
    }

    // �f�o�b�O�e�L�X�g�`��
    debugText->DrawAll();

    // �`��㏈��
    dxCommon->PostDraw();
    // �S�D�`��R�}���h�����܂�
}
