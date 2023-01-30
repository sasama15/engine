#include "GamePlayScene.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
//#include "../LightGroup.h"

void GamePlayScene::Initialize()
{
    Input* input = Input::GetInstance();
#pragma region �V�[������������
    // ���f�������w�肵�ăt�@�C���ǂݍ���
    //FbxLoader::GetInstance()->LoadModelFromFile("cube");
    //FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    nucleusFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �G�j����
    playerFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �v���C���[
    enemyFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // �m�[�}���G

    // �O���t�B�b�N�X�p�C�v���C������
    FbxObject3d::CreateGraphicsPipeline();

    // 3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
    nucleusFbxObject = new FbxObject3d;
    nucleusFbxObject->Initialize();
    nucleusFbxObject->SetModel(nucleusFbxModel);
    playerFbxObject = new FbxObject3d;
    playerFbxObject->Initialize();
    playerFbxObject->SetModel(playerFbxModel);
    enemyFbxObject = new FbxObject3d;
    enemyFbxObject->Initialize();
    enemyFbxObject->SetModel(enemyFbxModel);
    enemyFbxObject2 = new FbxObject3d;
    enemyFbxObject2->Initialize();
    enemyFbxObject2->SetModel(enemyFbxModel);

    // OBJ���烂�f���f�[�^��ǂݍ���
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");
    model_universe = Model::LoadFromOBJ("universe");

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
    std::weak_ptr<Object3d> objectUniverse = objectManager_->AddObject(Object3d::Create(model_universe.get()));
    // �I�u�W�F�N�g�̎Q�ƃJ�E���g�𑝉�
    object3d_1 = objectWp1.lock();
    object3d_2 = objectWp2.lock();
    object3d_3 = objectWp3.lock();
    object3d_universe = objectUniverse.lock();

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
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/gameend.png");
    
    // �X�v���C�g�̐���
    sprite = Sprite::Create(1, { 0,0 }, false, false);
    end = Sprite::Create(2, { 0, 0 }, false, false);

    endFlag = false;

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
    playerFbxObject->SetRotation({ 0, 90, 0 });

    playerFbxObject->PlayAnimation();

    PlayerPos = { 0,0,50 };
    NucleusPos = { 10, 0, 53 };
    EnemyPos = { 5, 1, 60 };
    EnemyPos2 = { 100, 2, 40 };
    EnemyJump = true;
    EnemyJump2 = true;
    playerFbxObject->SetPosition({ PlayerPos });
    nucleusFbxObject->SetPosition({ NucleusPos });
    enemyFbxObject->SetPosition({ EnemyPos });
    enemyFbxObject2->SetPosition({ EnemyPos2 });

    object3d_universe->SetScale({ 30, 30, 30 });

    // �_����
    /*lightGroup->SetDirLightActive(0, false);
    lightGroup->SetDirLightActive(1, false);
    lightGroup->SetDirLightActive(2, false);
    lightGroup->SetPointLightActive(0, true);
    pointLightPos[0] = 0.5f;
    pointLightPos[1] = 1.0f;
    pointLightPos[2] = 0.0f;*/

    enemyFlag = true;
    enemyFlag2 = true;
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
    delete nucleusFbxObject;
    delete playerFbxObject;
    delete enemyFbxObject;
    delete enemyFbxObject2;
    delete nucleusFbxModel;
    delete playerFbxModel;
    delete enemyFbxModel;
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

    if ((input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK))) && endFlag == true) {
        //�V�[���؂�ւ�
        SceneManager::GetInstance()->ChangeScene("TITLE");
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

    // �_����
    /*ligthGroup->SetPointLightPos(0, XMFLOAT3(pointLightPos));
    lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
    lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));*/

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

    // shared_ptr�g���ꍇ
    DirectX::XMFLOAT3 pos = object3d_universe->GetPosition();
    object3d_universe->SetModel(model_universe.get());

    // �v���C���[�ړ�
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
        input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
        input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
        if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z++; }
        if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z--; }
        if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x++; }
        if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x--; }
        playerFbxObject->SetPosition(PlayerPos);
    }

    // �G1����
    if (nucleusFlag == false)
    {
        //�ړ�
        if (playerFbxObject->GetPosition().x <= NucleusPos.x) {
            NucleusPos.x = NucleusPos.x - 0.01;
        }
        if (playerFbxObject->GetPosition().x >= NucleusPos.x) {
            NucleusPos.x = NucleusPos.x + 0.01;
        }
        if (playerFbxObject->GetPosition().z <= NucleusPos.z) {
            NucleusPos.z = NucleusPos.z - 0.01;
        }
        if (playerFbxObject->GetPosition().z >= NucleusPos.z) {
            NucleusPos.z = NucleusPos.z + 0.01;
        }

        //�W�����v
        NucleusPos.y -= NucleusGravity;
        nucleusFbxObject->SetPosition({ NucleusPos });
        if (NucleusPos.y <= 20 && NucleusJump == true) {
            NucleusPos.y += 0.2;
            NucleusGravity += 0.005f;
            nucleusFbxObject->SetPosition({ NucleusPos });
        }
        if (NucleusPos.y >= 20) {
            NucleusJump = false;
        }
        if (NucleusPos.y <= 0) {
            NucleusGravity = 0.1f;
            NucleusPos.y = 0;
            NucleusJump = true;
            nucleusFbxObject->SetPosition({ NucleusPos });
        }
    }

    //�G2����
    if (enemyFlag == false)
    {
        // �ړ�
        if (playerFbxObject->GetPosition().x <= EnemyPos.x) {
            EnemyPos.x = EnemyPos.x - 0.03;
        }
        if (playerFbxObject->GetPosition().x >= EnemyPos.x) {
            EnemyPos.x = EnemyPos.x + 0.03;
        }
        if (playerFbxObject->GetPosition().z <= EnemyPos.z) {
            EnemyPos.z = EnemyPos.z - 0.03;
        }
        if (playerFbxObject->GetPosition().z >= EnemyPos.z) {
            EnemyPos.z = EnemyPos.z + 0.03;
        }

        // �W�����v
        EnemyPos.y -= EnemyGravity;
        enemyFbxObject->SetPosition({ EnemyPos });
        if (EnemyPos.y <= 20 && EnemyJump == true) {
            EnemyPos.y += 0.2;
            EnemyGravity += 0.005f;
            enemyFbxObject->SetPosition({ EnemyPos });
        }
        if (EnemyPos.y >= 20) {
            EnemyJump = false;
        }
        if (EnemyPos.y <= 0) {
            EnemyGravity = 0.1f;
            EnemyPos.y = 0;
            EnemyJump = true;
            enemyFbxObject->SetPosition({ EnemyPos });
        }
    }

    //�G3����
    if (enemyFlag2 == false)
    {
        // �ړ�
        if (playerFbxObject->GetPosition().x <= EnemyPos2.x) {
            EnemyPos2.x = EnemyPos2.x - 0.08;
        }
        if (playerFbxObject->GetPosition().x >= EnemyPos2.x) {
            EnemyPos2.x = EnemyPos2.x + 0.08;
        }
        if (playerFbxObject->GetPosition().z <= EnemyPos2.z) {
            EnemyPos2.z = EnemyPos2.z - 0.08;
        }
        if (playerFbxObject->GetPosition().z >= EnemyPos2.z) {
            EnemyPos2.z = EnemyPos2.z + 0.08;
        }

        // �W�����v
        EnemyPos2.y -= EnemyGravity2;
        enemyFbxObject2->SetPosition({ EnemyPos2 });
        if (EnemyPos2.y <= 20 && EnemyJump2 == true) {
            EnemyPos2.y += 0.2;
            EnemyGravity2 += 0.005f;
            enemyFbxObject2->SetPosition({ EnemyPos2 });
        }
        if (EnemyPos2.y >= 20) {
            EnemyJump2 = false;
        }
        if (EnemyPos2.y <= 0) {
            EnemyGravity2 = 0.1f;
            EnemyPos2.y = 0;
            EnemyJump2 = true;
            enemyFbxObject2->SetPosition({ EnemyPos2 });
        }
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

    // �G1���U��������G2���`�悳���
    if (OnCollisionCircle(playerFbxObject, nucleusFbxObject, 2, 2) == true) {
        if (input->PushKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G
            enemyFlag = false;
        }
    }
    if (OnCollisionCircle(playerFbxObject, enemyFbxObject, 2, 2) == true) {
        if (input->PushKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            enemyFlag2 = false;
        }
    }
    if (OnCollisionCircle(playerFbxObject, enemyFbxObject2, 2, 2) == true) {
        if (input->PushKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            //�V�[���؂�ւ�
            SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
        }
    }
    if (OnCollisionCircle(playerFbxObject, nucleusFbxObject, 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, enemyFbxObject, 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, enemyFbxObject2, 0.2, 0.2) == true) {
        playerFlag = true;
        endFlag = true;
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

    camera->SetTarget(playerFbxObject->GetPosition());
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
    end->Update();

    // FBX�I�u�W�F�N�g�X�V
    nucleusFbxObject->Update();
    playerFbxObject->Update();
    enemyFbxObject->Update();
    enemyFbxObject2->Update();

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
    //object3d_universe->Draw();
   
#pragma region 3D�`��
    DirectXcommon* dxCommon = DirectXcommon::GetInstance();
    // 3D�I�u�W�F�N�g�̕`��
    
    // �v���C���[�̃t���O�������ĂȂ�������`��
    if (playerFlag == false) {
        playerFbxObject->Draw(dxCommon->GetCmdList());
    }
    // �G1�̃t���O�������ĂȂ�������`��
    if (nucleusFlag == false) {
        //objectManager_->Draw();
        nucleusFbxObject->Draw(dxCommon->GetCmdList());
    }
    // �G2�̃t���O�������ĂȂ�������`��
    if (enemyFlag == false) {
        enemyFbxObject->Draw(dxCommon->GetCmdList());
    }
    // �G3�̃t���O�������ĂȂ�������`��
    if (enemyFlag2 == false) {
        enemyFbxObject2->Draw(dxCommon->GetCmdList());
    }


    // �p�[�e�B�N���̕`��
    //particleMan->Draw(dxCommon->GetCmdList());
#pragma endregion

    // 3D�I�u�W�F�N�g�`��㏈��
    Object3d::PostDraw();

    // �X�v���C�g���ʃR�}���h
    SpriteCommon::GetInstance()->PreDrow();

    if (endFlag == true) {
        end->Draw();
    }
}
