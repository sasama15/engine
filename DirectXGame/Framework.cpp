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
    //dxCommon = new DirectXcommon();
    dxCommon = DirectXcommon::GetInstance();
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
    input = Input::GetInstance();
    input->Initialize(winApp);

    // �T�E���h
    Audio::Initialize();

    // �����ǂݍ���
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 3D�I�u�W�F�N�g�ÓI������
    Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);

    // Fbx�֌W
    FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());

    // �f�o�C�X���Z�b�g
    FbxObject3d::SetDevice(dxCommon->GetDev());
    PostSprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // �|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // �|�X�g�G�t�F�N�g�̏�����
    postEffect = new PostEffect();
    postEffect->Initialize();

    MultiRenderTarget::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // �|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // �|�X�g�G�t�F�N�g�̏�����
    postEffect2 = new MultiRenderTarget();
    postEffect2->Initialize();

    MultiTexture::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // �|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // �|�X�g�G�t�F�N�g�̏�����
    postEffect3 = new MultiTexture();
    postEffect3->Initialize();
}

void Framework::Finalize()
{
    // �V�[���t�@�N�g�����
    //delete sceneFactory_;
    //�Ӑ}�I�ɊJ���������ꍇ�͈����Ȃ��ŊJ��
    //sceneFactory_.reset();

    // �����f�[�^���
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

    // DirectX���
    //delete dxCommon;

    // Fbx�֌W
    FbxLoader::GetInstance()->Finalize();

    // PostEffect���
    delete postEffect;
    delete postEffect2;
    delete postEffect3;

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
    SceneManager::GetInstance()->Update();
}

void Framework::Draw()
{
    // �����_�[�e�N�X�`���ւ̕`��
    /*postEffect->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect->PostDrawScene(dxCommon->GetCmdList());*/

    /*postEffect2->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect2->PostDrawScene(dxCommon->GetCmdList());*/

    postEffect3->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect3->PostDrawScene(dxCommon->GetCmdList());
    
    // �`��O����
    dxCommon->PreDraw();
    // �|�X�g�G�t�F�N�g�̕`��
    //postEffect->Draw(dxCommon->GetCmdList());
    //postEffect2->Draw(dxCommon->GetCmdList());
    postEffect3->Draw(dxCommon->GetCmdList());

    // �V�[���`��
    //SceneManager::GetInstance()->Draw();

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();

    // �`��㏈��
    dxCommon->PostDraw();
}
