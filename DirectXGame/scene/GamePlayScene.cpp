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
    fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �G�j����
    fbxModel2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �v���C���[
    fbxModel3 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �m�[�}���G

    // �O���t�B�b�N�X�p�C�v���C������
    FbxObject3d::CreateGraphicsPipeline();

    // 3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
    fbxObject1 = new FbxObject3d;
    fbxObject1->Initialize();
    fbxObject1->SetModel(fbxModel1);
    fbxObject2 = new FbxObject3d;
    fbxObject2->Initialize();
    fbxObject2->SetModel(fbxModel2);
    fbxObject3 = new FbxObject3d;
    fbxObject3->Initialize();
    fbxObject3->SetModel(fbxModel3);
    fbxObject4 = new FbxObject3d;
    fbxObject4->Initialize();
    fbxObject4->SetModel(fbxModel3);

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
    /*camera->SetTarget({ 0, 20, 10 });
    camera->SetDistance(10.0f);*/
    camera->SetTarget({ 0, 2.5f, 10 });
    camera->SetDistance(8.0f);
    fbxObject2->SetRotation({ 0, 90, 0 });

    fbxObject2->PlayAnimation();

    PlayerPos = { 0,0,50 };
    EnemyPos = { 0.2, 0, 53 };
    EnemyPos2 = { 5, 1, 60 };
    EnemyPos3 = { 100, 2, 40 };
    EnemyJump2 = true;
    EnemyJump3 = true;
    fbxObject2->SetPosition({ PlayerPos });
    fbxObject1->SetPosition({ EnemyPos });
    fbxObject3->SetPosition({ EnemyPos2 });
    fbxObject4->SetPosition({ EnemyPos3 });
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
    delete fbxObject3;
    delete fbxObject4;
    delete fbxModel1;
    delete fbxModel2;
    delete fbxModel3;
    delete camera;
}

void GamePlayScene::Update()
{
#pragma region DirectX���t���[������
    // DirectX���t���[�������@��������


    /*OldEnemyPos = EnemyPos;
    OldEnemyPos2 = EnemyPos2;
    OldEnemyPos3 = EnemyPos3;*/

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_0)) // ������0�L�[��������Ă�����
    {
        OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
    }

    if (input->TriggerKey(DIK_RETURN) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //�V�[���؂�ւ�
        SceneManager::GetInstance()->ChangeScene("TITLE");
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    if (input->PushKey(DIK_X) || input->TriggerButton(static_cast<int>(Button::X))) {
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
    /*if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {
        if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
        else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
        if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
        else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
    }*/

    // �v���C���[�ړ�
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
        input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
        input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
        if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z++; }
        if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z--; }
        if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x++; }
        if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x--; }
        fbxObject2->SetPosition(PlayerPos);
    }

    // �G�ړ�
    if (fbxObject2->GetPosition().x <= EnemyPos.x) {
        EnemyPos.x = EnemyPos.x - 0.01;
    }
    if (fbxObject2->GetPosition().x >= EnemyPos.x) {
        EnemyPos.x = EnemyPos.x + 0.01;
    }

    if (fbxObject2->GetPosition().z <= EnemyPos.z) {
        EnemyPos.z = EnemyPos.z - 0.01;
    }
    if (fbxObject2->GetPosition().z >= EnemyPos.z) {
        EnemyPos.z = EnemyPos.z + 0.01;
    }

    EnemyPos.y -= Gravity;
    fbxObject1->SetPosition({ EnemyPos });
    if (EnemyPos.y <= 20 && EnemyJump == true) {
        EnemyPos.y += 0.2;
        Gravity += 0.005f;
        fbxObject1->SetPosition({ EnemyPos });
    }
    if (EnemyPos.y >= 20) {
        EnemyJump = false;
    }
    if (EnemyPos.y <= 0) {
        Gravity = 0.1f;
        EnemyPos.y = 0;
        EnemyJump = true;
        fbxObject1->SetPosition({ EnemyPos });
    }

    if (fbxObject2->GetPosition().x <= EnemyPos2.x) {
        EnemyPos2.x = EnemyPos2.x - 0.03;
    }
    if (fbxObject2->GetPosition().x >= EnemyPos2.x) {
        EnemyPos2.x = EnemyPos2.x + 0.03;
    }

    if (fbxObject2->GetPosition().z <= EnemyPos2.z) {
        EnemyPos2.z = EnemyPos2.z - 0.03;
    }
    if (fbxObject2->GetPosition().z >= EnemyPos2.z) {
        EnemyPos2.z = EnemyPos2.z + 0.03;
    }

    EnemyPos2.y -= Gravity2;
    fbxObject3->SetPosition({ EnemyPos2 });
    if (EnemyPos2.y <= 20 && EnemyJump2 == true) {
        EnemyPos2.y += 0.2;
        Gravity2 += 0.005f;
        fbxObject3->SetPosition({ EnemyPos2 });
    }
    if (EnemyPos2.y >= 20) {
        EnemyJump2 = false;
    }
    if (EnemyPos2.y <= 0) {
        Gravity2 = 0.1f;
        EnemyPos2.y = 0;
        EnemyJump2 = true;
        fbxObject3->SetPosition({ EnemyPos2 });
    }

    if (fbxObject2->GetPosition().x <= EnemyPos3.x) {
        EnemyPos3.x = EnemyPos3.x - 0.08;
    }
    if (fbxObject2->GetPosition().x >= EnemyPos3.x) {
        EnemyPos3.x = EnemyPos3.x + 0.08;
    }

    if (fbxObject3->GetPosition().z <= EnemyPos3.z) {
        EnemyPos3.z = EnemyPos3.z - 0.08;
    }
    if (fbxObject3->GetPosition().z >= EnemyPos3.z) {
        EnemyPos3.z = EnemyPos3.z + 0.08;
    }

    EnemyPos3.y -= Gravity3;
    fbxObject4->SetPosition({ EnemyPos3 });
    if (EnemyPos3.y <= 20 && EnemyJump3 == true) {
        EnemyPos3.y += 0.2;
        Gravity3 += 0.005f;
        fbxObject4->SetPosition({ EnemyPos3 });
    }
    if (EnemyPos3.y >= 20) {
        EnemyJump3 = false;
    }
    if (EnemyPos3.y <= 0) {
        Gravity3 = 0.1f;
        EnemyPos3.y = 0;
        EnemyJump3 = true;
        fbxObject4->SetPosition({ EnemyPos3 });
    }

    /*for (int i = 0; i < 5; i++) {

    }*/

    // �����蔻��
    //spherePlayer.center = { object3d_2->GetPosition().x, object3d_2->GetPosition().y, object3d_2->GetPosition().z, 1 };
    //sphereEnemy.center = { object3d_3->GetPosition().x, object3d_3->GetPosition().y, object3d_3->GetPosition().z, 1 };
    //spherePlayer.radius = 2;
    //sphereEnemy.radius = 2;

    //if (SphereCollision(spherePlayer, sphereEnemy) == true) {
    //    flag = true;
    //}
    
    // �v���C���[�ƓG�̋�����
    /*Ax = object3d_2->GetPosition().x - object3d_3->GetPosition().x;
    Az = object3d_2->GetPosition().z - object3d_3->GetPosition().z;
    Angle += (Ax - Az < 0.0f) ? +XM_PI / 180 * 8 : -XM_PI / 180 * 8;
    EnemyPos.x += (cosf(Angle) * 6.0f);
    EnemyPos.z += (sinf(Angle) * 6.0f);
    object3d_3->SetPosition(EnemyPos);*/

    if (OnCollisionCircle(fbxObject2, fbxObject1, 2, 2) == true) {
        if (input->PushKey(DIK_K) || input->PushButton(static_cast<int>(Button::B))) {
            flag2 = true;
        }
    }
    if (OnCollisionCircle(fbxObject2, fbxObject3, 2, 2) == true) {
        if (input->PushKey(DIK_K) || input->PushButton(static_cast<int>(Button::B))) {
            flag3 = true;
        }
    }
    // D���N�G
    //if (OnCollisionCircle(fbxObject1, fbxObject3, 1, 1) == true) {
    //   /* EnemyPos.x = OldEnemyPos.x;
    //    EnemyPos.z = OldEnemyPos.z;*/
    //    EnemyPos2.x = OldEnemyPos2.x;
    //    EnemyPos2.z = OldEnemyPos2.z;
    //}
    //if (OnCollisionCircle(fbxObject1, fbxObject4, 1, 1) == true) {
    //    /*EnemyPos.x = OldEnemyPos.x;
    //    EnemyPos.z = OldEnemyPos.z;*/
    //    EnemyPos3.x = OldEnemyPos3.x;
    //    EnemyPos3.z = OldEnemyPos3.z;
    //}
    //if (OnCollisionCircle(fbxObject3, fbxObject4, 1, 1) == true) {
    //    /*EnemyPos2.x = OldEnemyPos2.x;
    //    EnemyPos2.z = OldEnemyPos2.z;*/
    //    EnemyPos3.x = OldEnemyPos3.x;
    //    EnemyPos3.z = OldEnemyPos3.z;
    //}

    camera->SetTarget(fbxObject2->GetPosition());
    camera->SetDistance(20);

    // �e�I�u�W�F�N�g�̔��a
    const float radius1 = 3.0f;
    const float radisu2 = 3.0f;

    // X���W,Y���W���w�肵�ĕ\��
    DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    // X���W,Y���W,�k�ڂ��w�肵�ĕ\��
    DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

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
    fbxObject3->Update();
    fbxObject4->Update();

    camera->Update();

    // DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

bool GamePlayScene::OnCollisionCircle(FbxObject3d* playerCircle, FbxObject3d* enemyCircle1, float playerR1, float enemyR1)
{
    float x = playerCircle->GetPosition().x - enemyCircle1->GetPosition().x;
    float y = playerCircle->GetPosition().y - enemyCircle1->GetPosition().y;
    float z = playerCircle->GetPosition().z - enemyCircle1->GetPosition().z;

    float c = sqrt(x * x + y * y + z * z);
    float sum_radius = playerR1 + enemyR1;

    if (c <= sum_radius)
    {
        return true;
    }
    return false;
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
   
#pragma region 3D�`��
    DirectXcommon* dxCommon = DirectXcommon::GetInstance();
    // 3D�I�u�W�F�N�g�̕`��
    
    fbxObject2->Draw(dxCommon->GetCmdList());
    if (flag == false) {
        //objectManager_->Draw();
        fbxObject1->Draw(dxCommon->GetCmdList());
    }
    if (flag2 == true) {
        fbxObject3->Draw(dxCommon->GetCmdList());
    }
    if (flag3 == true) {
        fbxObject4->Draw(dxCommon->GetCmdList());
    }


    // �p�[�e�B�N���̕`��
    //particleMan->Draw(dxCommon->GetCmdList());
#pragma endregion

    // 3D�I�u�W�F�N�g�`��㏈��
    Object3d::PostDraw();

    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();
}
