#include "SampleGame.h"

void SampleGame::Initialize()
{
#pragma region WindowsAPI������
    // WindowsAPI�̏�����
    //WinApp* winApp = new WinApp();
    winApp = new WinApp();
    winApp->Initialize();

    // DirectX�̏�����
    //DirectXcommon* dxCommon = new DirectXcommon();
    dxCommon = new DirectXcommon();
    dxCommon->Initialize(winApp);

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

    // �X�v���C�g���ʕ����̏�����
    //SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->devGeter().Get(), dxCommon->cmdListGeter().Get(), winApp->window_width, winApp->window_height);

    // �T�E���h
    Audio::Initialize();

    // �����ǂݍ���
    //Audio::SoundData soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
    soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // ���͂̏�����
    //Input* input = new Input();
    input = new Input();
    input->Initialize(winApp);

    // DirectX�����������@�����܂�
#pragma endregion DirectX����������

#pragma region �`�揉��������
    // 3D�I�u�W�F�N�g�ÓI������
    Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

    // OBJ���烂�f���f�[�^��ǂݍ���
    /*Model* model_1 = Model::LoadFromOBJ("ground");
    Model* model_2 = Model::LoadFromOBJ("triangle_mat");
    Model* model_3 = Model::LoadFromOBJ("sphere");*/
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");

    // 3D�I�u�W�F�N�g����
    /*Object3d* object3d_1 = Object3d::Create();
    Object3d* object3d_2 = Object3d::Create();
    Object3d* object3d_3 = Object3d::Create();*/
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
    /*spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");*/
    spriteCommon->LoadTexture(1, L"Resources/texture.png");
    spriteCommon->LoadTexture(2, L"Resources/house.png");

    //std::vector<Sprite*> sprites;

    // �X�v���C�g�̐���
    for (int i = 0; i < 20; i++)
    {
        //int texNumber = rand() % 2;
        int texNumber = 1;
        Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

        // �X�v���C�g�̍��W�ύX
        sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });

        sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });

        // ���_�o�b�t�@�ɔ��f
        sprite->TransferVertexBuffer();

        sprites.push_back(sprite);
    }

    // �f�o�b�O�e�L�X�g
    //DebugText* debugText = new DebugText();
    debugText = new DebugText();

    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
    //const int debugTextTexNumber = 2;
    const int debugTextTexNumber = 0;
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // �f�o�b�O�e�L�X�g������
    debugText->Initialize(spriteCommon, debugTextTexNumber);

#pragma endregion �`�揉��������

    //int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[
}

void SampleGame::Finalize()
{
    // �����f�[�^���
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

#pragma region WindowsAPI��n��
    // WindowsAPI�̏I������
    winApp->Finalize();

#pragma endregion WindowsAPI��n��
#pragma endregion WindowsAPI������

    // �f�o�b�O�e�L�X�g���
    delete debugText;

    // �X�v���C�g�ʉ��
    for (auto& sprite : sprites) {
        delete sprite;
    }
    sprites.clear();
    // �X�v���C�g���ʕ������
    delete spriteCommon;

    // 3D���f�����
    delete model_1;
    delete model_2;
    delete model_3;
    // 3D�I�u�W�F�N�g���
    delete object3d_1;
    delete object3d_2;
    delete object3d_3;

    // DirectX���
    delete dxCommon;
    // ���͉��
    delete input;
    // WindowsAPI���
    delete winApp;
}

void SampleGame::Update()
{
#pragma region �E�B���h�E���b�Z�[�W����
    // Windows�̃��b�Z�[�W����
    if (winApp->ProcessMessage()) {
        // �Q�[�����[�v�𔲂���
        endRequst_ = true;
        return;
    }

#pragma endregion �E�B���h�E���b�Z�[�W����

#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // ���͂̍X�V
    input->Update();

    // 3D�I�u�W�F�N�g�X�V
    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    // �X�v���C�g�X�V
    for (auto& sprite : sprites) {
        sprite->Update();
    }

    //const int cycle = 540; // �J��Ԃ��̎���
    //counter++;
    //counter %= cycle; // �����𒴂�����0�ɖ߂�
    //float scale = (float)counter / cycle; // [0,1]�̐��l

    //scale *= 360.0f;

    //float offset = sinf(XM_2PI * (float)counter / cycle);
    //offset *= 10.0f;

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
