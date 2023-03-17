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
    input->ControllerInitialize(0);

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

    particleMan->StaticInitialize(dxCommon->GetDev(), 1280, 720, L"Resources/effect3.png");
    particleMan = ParticleManager::Create();
    for (int i = 0; i < 100; i++)
    {
        //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
        const float rnd_pos = 1.0f;
        XMFLOAT3 pos{};
        pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        //X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
        const float rnd_vel = 0.1f;
        XMFLOAT3 vel{};
        vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        //�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
        XMFLOAT3 acc{};
        const float rnd_acc = 0.001f;
        acc.y = -(float)rand() / RAND_MAX * rnd_acc;

        //�ǉ�
        particleMan->Add(60, pos, vel, acc);
    }
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

    delete particleMan;

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
    input->ControllerUpdate(0);

    // �V�[���̍X�V
    SceneManager::GetInstance()->Update();
    for (int i = 0; i < 100; i++)
    {
        //X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
        const float rnd_pos = 10.0f;
        XMFLOAT3 pos{};
        pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
        //X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
        const float rnd_vel = 0.1f;
        XMFLOAT3 vel{};
        vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
        //�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
        XMFLOAT3 acc{};
        const float rnd_acc = 0.001f;
        acc.y = -(float)rand() / RAND_MAX * rnd_acc;

        //�ǉ�
        particleMan->Add(60, pos, vel, acc);
        break;
    }
    particleMan->Update();
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


    //ParticleManager::PreDraw(ID3D12GraphicsCommandList * cmdList);
    //PreDraw(dxCommon->GetCmdList());

    dxCommon->PreDraw();

    /*postEffect3->PreDrawScene(dxCommon->GetCmdList());*/
    SceneManager::GetInstance()->Draw();
    /*postEffect3->PostDrawScene(dxCommon->GetCmdList());*/
    
    // �`��O����
    //dxCommon->PreDraw();
    // �|�X�g�G�t�F�N�g�̕`��
    //postEffect->Draw(dxCommon->GetCmdList());
    //postEffect2->Draw(dxCommon->GetCmdList());
    //postEffect3->Draw(dxCommon->GetCmdList());

    // �V�[���`��
    //SceneManager::GetInstance()->Draw();

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();

    // �`��㏈��
    particleMan->PreDraw(dxCommon->GetCmdList());
    particleMan->Draw();
    particleMan->PostDraw();
    dxCommon->PostDraw();
}
