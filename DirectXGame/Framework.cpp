#include "Framework.h"

void Framework::Run()
{
    // �Q�[���̏�����
    Initialize();

    while (true)  // �Q�[�����[�v
    {
        // ���t���[���X�V
        Update();

        // �I�����N�G�X�g�������甲����
        if (IsEndRequst()) {
            break;
        }

        // �`��
        Draw();

    }
    // �Q�[���̏I��
    Finalize();
}

void Framework::Initialize()
{
    // WindowsAPI�̏�����
    winApp = new WinApp();
    winApp->Initialize();

    // DirectX�̏�����
    dxCommon = new DirectXcommon();
    dxCommon->Initialize(winApp);

    // �X�v���C�g���ʕ����̏�����
    spriteCommon = SpriteCommon::GetInstance();
    spriteCommon->Initialize(dxCommon->devGeter().Get(), dxCommon->cmdListGeter().Get(), winApp->window_width, winApp->window_height);

    // �f�o�b�O�e�L�X�g
    debugText = DebugText::GetInstance();

    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
    const int debugTextTexNumber = 0;
    // �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // �f�o�b�O�e�L�X�g������
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    // ���͂̏�����
    //Input* input = new Input();
    input = Input::GetInstance();
    input->Initialize(winApp);

    // �T�E���h
    Audio::Initialize();

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 3D�I�u�W�F�N�g�ÓI������
    Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);

    // �V�[���}�l�[�W���[�̐���
    sceneManager_ = new SceneManager;
}

void Framework::Finalize()
{
    // �V�[���}�l�[�W���[���
    delete sceneManager_;

    // �����f�[�^���
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

    // DirectX���
    delete dxCommon;

    // WindowsAPI�̏I������
    winApp->Finalize();
    // WindowsAPI���
    delete winApp;
}

void Framework::Update()
{
#pragma region �E�B���h�E���b�Z�[�W����
    // Windows�̃��b�Z�[�W����
    if (winApp->ProcessMessage()) {
        // �Q�[�����[�v�𔲂���
        endRequst_ = true;
        return;
    }
#pragma endregion �E�B���h�E���b�Z�[�W����

    // ���͂̍X�V
    input->Update();

    // �V�[���̍X�V
    sceneManager_->Update();
}

void Framework::Draw()
{
    // �`��O����
    dxCommon->PreDraw();

    // �V�[���`��
    sceneManager_->Draw();

    // �f�o�b�O�e�L�X�g�`��
    debugText->DrawAll();

    // �`��㏈��
    dxCommon->PostDraw();
}
