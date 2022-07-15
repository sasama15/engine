#include "GamePlayScene.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

void GamePlayScene::Initialize()
{
    Input* input = Input::GetInstance();
#pragma region �V�[������������
    // ���f�������w�肵�ăt�@�C���ǂݍ���
    //FbxLoader::GetInstance()->LoadModelFromFile("cube");
    //FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("cube");
    fbxModel2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

    // �O���t�B�b�N�X�p�C�v���C������
    FbxObject3d::CreateGraphicsPipeline();

    // 3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
    fbxObject1 = new FbxObject3d;
    fbxObject1->Initialize();
    fbxObject1->SetModel(fbxModel1);
    fbxObject2 = new FbxObject3d;
    fbxObject2->Initialize();
    fbxObject2->SetModel(fbxModel2);

    // OBJ���烂�f���f�[�^��ǂݍ���
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");

    // �I�u�W�F�N�g�}�l�[�W������
    objectManager_ = std::make_unique<ObjectManager>();

    // 3D�I�u�W�F�N�g����
   /* object3d_1 = Object3d::Create();
    object3d_2 = Object3d::Create();
    object3d_3 = Object3d::Create();*/
    // �Â�����
    /*object3d_1.reset(Object3d::Create());
    object3d_2.reset(Object3d::Create());
    object3d_3.reset(Object3d::Create());*/

    // weak_ptr�g���Ƃ��̎c�[
    //std::shared_ptr<Object3d> object3d_1 = Object3d::Create();
    //std::shared_ptr<Object3d> object3d_2 = Object3d::Create();
    //std::shared_ptr<Object3d> object3d_3 = Object3d::Create();

    // weak_ptr�g���ꍇ
    /*object3d_1 = objectManager_->AddObject(Object3d::Create(model_1.get()));
    object3d_2 = objectManager_->AddObject(Object3d::Create(model_2.get()));
    object3d_3 = objectManager_->AddObject(Object3d::Create(model_3.get()));*/

    // shared_ptr�g���ꍇ
    std::weak_ptr<Object3d> objectWp1 = objectManager_->AddObject(Object3d::Create(model_1.get()));
    std::weak_ptr<Object3d> objectWp2 = objectManager_->AddObject(Object3d::Create(model_2.get()));
    std::weak_ptr<Object3d> objectWp3 = objectManager_->AddObject(Object3d::Create(model_3.get()));
    // �I�u�W�F�N�g�̎Q�ƃJ�E���g�𑝉�
    object3d_1 = objectWp1.lock();
    object3d_2 = objectWp2.lock();
    object3d_3 = objectWp3.lock();

    //C++11�ȍ~�̕��@    new��u��������ꍇ�̂ݎg�p�\
    //object3d_1 = std::make_unique<Object3d>();

    // �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
    /*object3d_1->SetModel(model_1.get());
    object3d_2->SetModel(model_2.get());
    object3d_3->SetModel(model_2.get());*/

    // 3D�I�u�W�F�N�g�̈ʒu���w��
    /*object3d_2->SetPosition({ -5, 0, -5 });
    object3d_3->SetPosition({ +5, 0, +5 });*/

    // weak_ptr�g���ꍇ
   /* if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
        DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
        object3d_2Sp->SetPosition({ -5, 0, -5 });
    }
    if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
        DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
        object3d_3Sp->SetPosition({ +5, 0, +5 });
    }*/

    // shared_ptr�g���ꍇ
    DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
    object3d_2->SetPosition({ -5, 0, -5 });
    DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
    object3d_3->SetPosition({ +5, 0, +5 });

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gamePlay.jpg");
    
    // �X�v���C�g�̐���
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    // �����ǂݍ���
    soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

    // �J�������Z�b�g
    FbxObject3d::SetCamera(camera);

    // �J���������_���Z�b�g
    camera->SetTarget({ 0, 20, 10 });
    camera->SetDistance(10.0f);
}

void GamePlayScene::Finalize()
{
    // �X�v���C�g�ʉ��
    //delete sprite;

     // 3D���f�����
    /*delete model_1;
    delete model_2;
    delete model_3;*/
    // 3D�I�u�W�F�N�g���
    /*delete object3d_1;
    delete object3d_2;
    delete object3d_3;*/

    // FBX�I�u�W�F�N�g�A���f�����
    delete fbxObject1;
    delete fbxObject2;
    delete fbxModel1;
    delete fbxModel2;
    delete camera;
}

void GamePlayScene::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������

    // 3D�I�u�W�F�N�g�X�V
    /*object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();*/
    objectManager_->Update();

    // �X�v���C�g�X�V
    sprite->Update();

    // FBX�I�u�W�F�N�g�X�V
    fbxObject1->Update();
    fbxObject2->Update();

    camera->SetTarget(fbxObject2->GetPosition());
    camera->Update();

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_0)) // ������0�L�[��������Ă�����
    {
        OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
    }

    if (input->TriggerKey(DIK_SPACE)) {
        //�V�[���؂�ւ�
        SceneManager::GetInstance()->ChangeScene("TITLE");
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    if (input->PushKey(DIK_X)) {
        /*object3d_2->SetModel(model_3.get());
        object3d_3->SetModel(model_3.get());*/

        // weak_ptr����share_ptr�����o�� weak_ptr�g���ꍇ
       /* if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
            DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
            object3d_2Sp->SetModel(model_3.get());
        }
        if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
            DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
            object3d_3Sp->SetModel(model_3.get());
        }*/

        // shared_ptr�g���ꍇ
        DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
        object3d_2->SetModel(model_3.get());
        DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
        object3d_3->SetModel(model_3.get());
    }
    else {
       /* object3d_2->SetModel(model_2.get());
        object3d_3->SetModel(model_2.get());*/

        // weak_ptr�g���ꍇ
        /*if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
            DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
            object3d_2Sp->SetModel(model_2.get());
        }
        if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
            DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
            object3d_3Sp->SetModel(model_2.get());
        }*/

        //shared_ptr�g���ꍇ
        DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
        object3d_2->SetModel(model_2.get());
        DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
        object3d_3->SetModel(model_2.get());
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
    /*object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();*/
    //objectManager_->Draw();

#pragma region 3D�`��
    DirectXcommon* dxCommon = DirectXcommon::GetInstance();
    // 3D�I�u�W�F�N�g�̕`��
    //fbxObject1->Draw(dxCommon->GetCmdList());
    fbxObject2->Draw(dxCommon->GetCmdList());

    // �p�[�e�B�N���̕`��
    //particleMan->Draw(dxCommon->GetCmdList());
#pragma endregion

    // 3D�I�u�W�F�N�g�`��㏈��
    Object3d::PostDraw();

    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
}
