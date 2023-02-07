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
    nucleusFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("redMountain");   // �G�j����
    playerFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("player");         // �v���C���[
    enemyFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("blueMountain");    // �m�[�}���G
    universeFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("universe");     // �w�i

    // �O���t�B�b�N�X�p�C�v���C������
    FbxObject3d::CreateGraphicsPipeline();

    // 3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
    // �j�����G
    for (int i = 0; i < nucleusMax; i++) {
        nucleusFbxObject[i] = new FbxObject3d;
        nucleusFbxObject[i]->Initialize();
        nucleusFbxObject[i]->SetModel(nucleusFbxModel);
    }

    //// �j�����G
    //nucleusFbxObject = new FbxObject3d;
    //nucleusFbxObject->Initialize();
    //nucleusFbxObject->SetModel(nucleusFbxModel);

    //// �j�����G2
    //nucleusFbxObject2 = new FbxObject3d;
    //nucleusFbxObject2->Initialize();
    //nucleusFbxObject2->SetModel(nucleusFbxModel);

    //// �j�����G3
    //nucleusFbxObject3 = new FbxObject3d;
    //nucleusFbxObject3->Initialize();
    //nucleusFbxObject3->SetModel(nucleusFbxModel);

    // �v���C���[
    playerFbxObject = new FbxObject3d;
    playerFbxObject->Initialize();
    playerFbxObject->SetModel(playerFbxModel);

    // �G
    for (int i = 0; i < enemyMax; i++) {
        enemyFbxObject[i] = new FbxObject3d;
        enemyFbxObject[i]->Initialize();
        enemyFbxObject[i]->SetModel(enemyFbxModel);
    }

    // �w�i�F��
    universeFbxObject = new FbxObject3d;
    universeFbxObject->Initialize();
    universeFbxObject->SetModel(universeFbxModel);

    //// �G
    //enemyFbxObject = new FbxObject3d;
    //enemyFbxObject->Initialize();
    //enemyFbxObject->SetModel(enemyFbxModel);

    //// �G2
    //enemyFbxObject2 = new FbxObject3d;
    //enemyFbxObject2->Initialize();
    //enemyFbxObject2->SetModel(enemyFbxModel);

    //// �G3
    //enemyFbxObject3 = new FbxObject3d;
    //enemyFbxObject3->Initialize();
    //enemyFbxObject3->SetModel(enemyFbxModel);

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
    //SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gamePlay.jpg");
    SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/gameend.png");
    SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/wasd.png");
    SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/enter.png");
    
    // �X�v���C�g�̐���
    //sprite = Sprite::Create(1, { 0,0 }, false, false);
    end = Sprite::Create(2, { 0, 0 }, false, false);
    wasd = Sprite::Create(3, { 0, 0 }, false, false);
    enter = Sprite::Create(4, { 0, -1 }, false, false);

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
    playerFbxObject->SetRotation({ 0, 180, 0 });

    nucleusFbxObject[0]->SetRotation({ 0, 90, 0 });
    nucleusFbxObject[1]->SetRotation({ 0, 90, 0 });
    nucleusFbxObject[2]->SetRotation({ 0, 90, 0 });

    enemyFbxObject[0]->SetRotation({ 0, 90, 0 });
    enemyFbxObject[0]->SetRotation({ 0, 90, 0 });
    enemyFbxObject[0]->SetRotation({ 0, 90, 0 });

    universeFbxObject->SetRotation({ 0, 90, 0 });
    //playerFbxObject->PlayAnimation();
    playerFbxObject->SetScale({ 0.0001f, 0.0001f, 0.0001f });
    //playerFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });

    nucleusFbxObject[0]->SetScale({ 0.015f, 0.015f, 0.015f });
    nucleusFbxObject[1]->SetScale({ 0.01f, 0.01f, 0.01f });
    nucleusFbxObject[2]->SetScale({ 0.005f, 0.005f, 0.005f });

    enemyFbxObject[0]->SetScale({ 0.01f, 0.01f, 0.01f });
    enemyFbxObject[1]->SetScale({ 0.005f, 0.005f, 0.005f });
    enemyFbxObject[2]->SetScale({ 0.005f, 0.005f, 0.005f });

    universeFbxObject->SetScale({ 10.0f, 10.0f, 10.0f });

    PlayerPos = { 0,0,50 };

    NucleusPos = { 10, 0, 53 };
    NucleusPos2 = { 10, 0, 53 };
    NucleusPos3 = { 10, 0, 53 };

    EnemyPos = { 10, 0, 53 };
    EnemyPos2 = { 10, 0, 53 };
    EnemyPos3 = { 10, 0, 53 };

    UniversePos = { 0, 0, -100 };

    EnemyJump = true;
    EnemyJump2 = true;
    EnemyJump3 = true;

    playerFbxObject->SetPosition({ PlayerPos });

    nucleusFbxObject[0]->SetPosition({NucleusPos});
    nucleusFbxObject[1]->SetPosition({ NucleusPos2 });
    nucleusFbxObject[2]->SetPosition({ NucleusPos3 });

    /*nucleusFbxObject->SetPosition({ NucleusPos });
    nucleusFbxObject2->SetPosition({ NucleusPos2 });
    nucleusFbxObject3->SetPosition({ NucleusPos3 });*/

    enemyFbxObject[0]->SetPosition({EnemyPos});
    enemyFbxObject[1]->SetPosition({ EnemyPos2 });
    enemyFbxObject[2]->SetPosition({ EnemyPos3 });

    universeFbxObject->SetPosition({ UniversePos });

    /*enemyFbxObject->SetPosition({ EnemyPos });
    enemyFbxObject2->SetPosition({ EnemyPos2 });
    enemyFbxObject3->SetPosition({ EnemyPos3 });*/

    object3d_universe->SetScale({ 30, 30, 30 });

    // �_����
    /*lightGroup->SetDirLightActive(0, false);
    lightGroup->SetDirLightActive(1, false);
    lightGroup->SetDirLightActive(2, false);
    lightGroup->SetPointLightActive(0, true);
    pointLightPos[0] = 0.5f;
    pointLightPos[1] = 1.0f;
    pointLightPos[2] = 0.0f;*/

    nucleusFlag2 = true;
    nucleusFlag3 = true;
    enemyFlag = true;
    enemyFlag2 = true;
    enemyFlag3 = true;

    nucleusMoveFlag = false;
    nucleusMoveFlag2 = false;

    enemyMoveFlag = false;
    enemyMoveFlag2 = false;
    enemyMoveFlag3 = false;

    timer1 = 0;

    nucleusMoveTime = 0;
    nucleusMoveTime2 = 0;

    enemyMoveTime = 0;
    enemyMoveTime2 = 0;
    enemyMoveTime3 = 0;
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
    delete playerFbxObject;

    delete nucleusFbxObject[0];
    delete nucleusFbxObject[1];
    delete nucleusFbxObject[2];

    /*delete nucleusFbxObject;
    delete nucleusFbxObject2;
    delete nucleusFbxObject3;*/

    delete enemyFbxObject[0];
    delete enemyFbxObject[1];
    delete enemyFbxObject[2];

    delete universeFbxObject;

    /*delete enemyFbxObject;
    delete enemyFbxObject2;
    delete enemyFbxObject3;*/

    delete universeFbxModel;
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

    // ���ꂼ��̓G�̐����ꏊ
    if (nucleusFlag2 == true) {
        NucleusPos2 = { NucleusPos.x, 0, NucleusPos.z };
    }
    if (nucleusFlag3 == true) {
        NucleusPos3 = { NucleusPos2.x, 0, NucleusPos2.z };
    }
    if (enemyFlag == true) {
        EnemyPos = { NucleusPos.x, 0, NucleusPos.z };
    }
    if (enemyFlag2 == true) {
        EnemyPos2 = { NucleusPos2.x, 0, NucleusPos2.z };
    }
    if (enemyFlag3 == true) {
        EnemyPos3 = { NucleusPos2.x, 0, NucleusPos2.z };
    }

    // �j�����G����
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
        nucleusFbxObject[0]->SetPosition({NucleusPos});
        if (NucleusPos.y <= 20 && NucleusJump == true) {
            NucleusPos.y += 0.2;
            NucleusGravity += 0.005f;
            nucleusFbxObject[0]->SetPosition({NucleusPos});
        }
        if (NucleusPos.y >= 20) {
            NucleusJump = false;
        }
        if (NucleusPos.y <= 0) {
            NucleusGravity = 0.1f;
            NucleusPos.y = 0;
            NucleusJump = true;
            nucleusFbxObject[0]->SetPosition({NucleusPos});
        }

        ////�W�����v
        //NucleusPos.y -= NucleusGravity;
        //nucleusFbxObject->SetPosition({ NucleusPos });
        //if (NucleusPos.y <= 20 && NucleusJump == true) {
        //    NucleusPos.y += 0.2;
        //    NucleusGravity += 0.005f;
        //    nucleusFbxObject->SetPosition({ NucleusPos });
        //}
        //if (NucleusPos.y >= 20) {
        //    NucleusJump = false;
        //}
        //if (NucleusPos.y <= 0) {
        //    NucleusGravity = 0.1f;
        //    NucleusPos.y = 0;
        //    NucleusJump = true;
        //    nucleusFbxObject->SetPosition({ NucleusPos });
        //}
    }

    // �j�����G2����
    if (nucleusFlag2 == false){
        if (nucleusMoveFlag == false) {
            nucleusMoveTime++;
            NucleusPos2.x += 0.5;
            //NucleusPos2.z += 0.2;
            NucleusPos2.y += 0.1;
            if (nucleusMoveTime > 60) {
                nucleusMoveFlag = true;
            }
        }
        //�ړ�
        if (playerFbxObject->GetPosition().x <= NucleusPos2.x) {
            NucleusPos2.x = NucleusPos2.x - 0.01;
        }
        if (playerFbxObject->GetPosition().x >= NucleusPos2.x) {
            NucleusPos2.x = NucleusPos2.x + 0.01;
        }
        if (playerFbxObject->GetPosition().z <= NucleusPos2.z) {
            NucleusPos2.z = NucleusPos2.z - 0.01;
        }
        if (playerFbxObject->GetPosition().z >= NucleusPos2.z) {
            NucleusPos2.z = NucleusPos2.z + 0.01;
        }

        //�W�����v

        NucleusGravity2 += 0.005f;
        NucleusPos2.y -= NucleusGravity2;
        nucleusFbxObject[1]->SetPosition({ NucleusPos2 });
        if (NucleusPos2.y <= 20 && NucleusJump2 == true) {
            NucleusPos2.y += 0.2;
            nucleusFbxObject[1]->SetPosition({ NucleusPos2 });
        }
        if (NucleusPos2.y >= 20) {
            NucleusJump2 = false;
        }
        if (NucleusPos2.y <= 0) {
            NucleusGravity2 = 0.1f;
            NucleusPos2.y = 0;
            NucleusJump2 = true;
            nucleusFbxObject[1]->SetPosition({ NucleusPos2 });
        }

        ////�W�����v
        //NucleusPos2.y -= NucleusGravity2;
        //nucleusFbxObject2->SetPosition({ NucleusPos2 });
        //if (NucleusPos2.y <= 20 && NucleusJump2 == true) {
        //    NucleusPos2.y += 0.2;
        //    NucleusGravity2 += 0.005f;
        //    nucleusFbxObject2->SetPosition({ NucleusPos2 });
        //}
        //if (NucleusPos2.y >= 20) {
        //    NucleusJump2 = false;
        //}
        //if (NucleusPos2.y <= 0) {
        //    NucleusGravity2 = 0.1f;
        //    NucleusPos2.y = 0;
        //    NucleusJump2 = true;
        //    nucleusFbxObject2->SetPosition({ NucleusPos2 });
        //}
    }
    
    // �j�����G3����
    if (nucleusFlag3 == false){

        if (nucleusMoveFlag2 == false) {
            nucleusMoveTime2++;
            NucleusPos3.x -= 0.5;
            NucleusPos3.z -= 0.2;
            NucleusPos3.y += 0.1;
            if (nucleusMoveTime2 > 60) {
                nucleusMoveFlag2 = true;
            }
        }

        //�ړ�
        if (playerFbxObject->GetPosition().x <= NucleusPos3.x) {
            NucleusPos3.x = NucleusPos3.x - 0.01;
        }
        if (playerFbxObject->GetPosition().x >= NucleusPos3.x) {
            NucleusPos3.x = NucleusPos3.x + 0.01;
        }
        if (playerFbxObject->GetPosition().z <= NucleusPos3.z) {
            NucleusPos3.z = NucleusPos3.z - 0.01;
        }
        if (playerFbxObject->GetPosition().z >= NucleusPos3.z) {
            NucleusPos3.z = NucleusPos3.z + 0.01;
        }

        //�W�����v
        NucleusGravity3 += 0.005f;
        NucleusPos3.y -= NucleusGravity3;
        nucleusFbxObject[2]->SetPosition({ NucleusPos3 });
        if (NucleusPos3.y <= 20 && NucleusJump3 == true) {
            NucleusPos3.y += 0.2;
            nucleusFbxObject[2]->SetPosition({ NucleusPos3 });
        }
        if (NucleusPos3.y >= 20) {
            NucleusJump3 = false;
        }
        if (NucleusPos3.y <= 0) {
            NucleusGravity3 = 0.1f;
            NucleusPos3.y = 0;
            NucleusJump3 = true;
            nucleusFbxObject[2]->SetPosition({ NucleusPos3 });
        }

        ////�W�����v
        //NucleusPos3.y -= NucleusGravity3;
        //nucleusFbxObject3->SetPosition({ NucleusPos3 });
        //if (NucleusPos3.y <= 20 && NucleusJump3 == true) {
        //    NucleusPos3.y += 0.2;
        //    NucleusGravity3 += 0.005f;
        //    nucleusFbxObject3->SetPosition({ NucleusPos3 });
        //}
        //if (NucleusPos3.y >= 20) {
        //    NucleusJump3 = false;
        //}
        //if (NucleusPos3.y <= 0) {
        //    NucleusGravity3 = 0.1f;
        //    NucleusPos3.y = 0;
        //    NucleusJump3 = true;
        //    nucleusFbxObject3->SetPosition({ NucleusPos3 });
        //}
    }

    //�G����
    if (enemyFlag == false){
        if (enemyMoveFlag == false) {
            enemyMoveTime++;
            EnemyPos.x += 0.2;
            EnemyPos.y += 0.1;
            if (enemyMoveTime > 60) {
                enemyMoveFlag = true;
            }
        }
        
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
        enemyFbxObject[0]->SetPosition({EnemyPos});
        if (EnemyPos.y <= 20 && EnemyJump == true) {
            EnemyPos.y += 0.2;
            EnemyGravity += 0.005f;
            enemyFbxObject[0]->SetPosition({EnemyPos});
        }
        if (EnemyPos.y >= 20) {
            EnemyJump = false;
        }
        if (EnemyPos.y <= 0) {
            EnemyGravity = 0.1f;
            EnemyPos.y = 0;
            EnemyJump = true;
            enemyFbxObject[0]->SetPosition({EnemyPos});
        }

        //// �W�����v
        //EnemyPos.y -= EnemyGravity;
        //enemyFbxObject->SetPosition({ EnemyPos });
        //if (EnemyPos.y <= 20 && EnemyJump == true) {
        //    EnemyPos.y += 0.2;
        //    EnemyGravity += 0.005f;
        //    enemyFbxObject->SetPosition({ EnemyPos });
        //}
        //if (EnemyPos.y >= 20) {
        //    EnemyJump = false;
        //}
        //if (EnemyPos.y <= 0) {
        //    EnemyGravity = 0.1f;
        //    EnemyPos.y = 0;
        //    EnemyJump = true;
        //    enemyFbxObject->SetPosition({ EnemyPos });
        //}
    }

    //�G2����
    if (enemyFlag2 == false){
        if (enemyMoveFlag2 == false) {
            enemyMoveTime2++;
            EnemyPos2.x -= 0.2;
            EnemyPos2.y += 0.1;
            if (enemyMoveTime2 > 60) {
                enemyMoveFlag2 = true;
            }
        }

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
        enemyFbxObject[1]->SetPosition({ EnemyPos2 });
        if (EnemyPos2.y <= 20 && EnemyJump2 == true) {
            EnemyPos2.y += 0.2;
            EnemyGravity2 += 0.005f;
            enemyFbxObject[1]->SetPosition({ EnemyPos2 });
        }
        if (EnemyPos2.y >= 20) {
            EnemyJump2 = false;
        }
        if (EnemyPos2.y <= 0) {
            EnemyGravity2 = 0.1f;
            EnemyPos2.y = 0;
            EnemyJump2 = true;
            enemyFbxObject[1]->SetPosition({ EnemyPos2 });
        }

        //// �W�����v
        //EnemyPos2.y -= EnemyGravity2;
        //enemyFbxObject2->SetPosition({ EnemyPos2 });
        //if (EnemyPos2.y <= 20 && EnemyJump2 == true) {
        //    EnemyPos2.y += 0.2;
        //    EnemyGravity2 += 0.005f;
        //    enemyFbxObject2->SetPosition({ EnemyPos2 });
        //}
        //if (EnemyPos2.y >= 20) {
        //    EnemyJump2 = false;
        //}
        //if (EnemyPos2.y <= 0) {
        //    EnemyGravity2 = 0.1f;
        //    EnemyPos2.y = 0;
        //    EnemyJump2 = true;
        //    enemyFbxObject2->SetPosition({ EnemyPos2 });
        //}
    }

    //�G3����
    if (enemyFlag3 == false){
        if (enemyMoveFlag3 == false) {
            enemyMoveTime3++;
            EnemyPos3.x += 0.4;
            EnemyPos3.y += 0.1;
            if (enemyMoveTime3 > 60) {
                enemyMoveFlag3 = true;
            }
        }
        // �ړ�
        if (playerFbxObject->GetPosition().x <= EnemyPos3.x) {
            EnemyPos3.x = EnemyPos3.x - 0.08;
        }
        if (playerFbxObject->GetPosition().x >= EnemyPos3.x) {
            EnemyPos3.x = EnemyPos3.x + 0.08;
        }
        if (playerFbxObject->GetPosition().z <= EnemyPos3.z) {
            EnemyPos3.z = EnemyPos3.z - 0.08;
        }
        if (playerFbxObject->GetPosition().z >= EnemyPos3.z) {
            EnemyPos3.z = EnemyPos3.z + 0.08;
        }

        // �W�����v
        EnemyPos3.y -= EnemyGravity3;
        enemyFbxObject[2]->SetPosition({ EnemyPos3 });
        if (EnemyPos3.y <= 20 && EnemyJump2 == true) {
            EnemyPos3.y += 0.2;
            EnemyGravity3 += 0.005f;
            enemyFbxObject[2]->SetPosition({ EnemyPos3 });
        }
        if (EnemyPos3.y >= 20) {
            EnemyJump3 = false;
        }
        if (EnemyPos3.y <= 0) {
            EnemyGravity3 = 0.1f;
            EnemyPos3.y = 0;
            EnemyJump3 = true;
            enemyFbxObject[2]->SetPosition({ EnemyPos3 });
        }

        //// �W�����v
        //EnemyPos3.y -= EnemyGravity3;
        //enemyFbxObject3->SetPosition({ EnemyPos3 });
        //if (EnemyPos3.y <= 20 && EnemyJump2 == true) {
        //    EnemyPos3.y += 0.2;
        //    EnemyGravity3 += 0.005f;
        //    enemyFbxObject3->SetPosition({ EnemyPos3 });
        //}
        //if (EnemyPos3.y >= 20) {
        //    EnemyJump3 = false;
        //}
        //if (EnemyPos3.y <= 0) {
        //    EnemyGravity3 = 0.1f;
        //    EnemyPos3.y = 0;
        //    EnemyJump3 = true;
        //    enemyFbxObject3->SetPosition({ EnemyPos3 });
        //}
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

    if (nucleusFlag == true) {
        timer1++;
    }
    // �j�����G���U��������G�Ɗj�����G2���`�悳���
    if (OnCollisionCircle(playerFbxObject, nucleusFbxObject[0], 5, 5) == true) {
        if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G
            enemyFlag = false;
            // �j�����G2
            nucleusFlag2 = false;

            // �j�����G
            nucleusFlag = true;
        }
    }
    // �G1���U�������������
    if (OnCollisionCircle(playerFbxObject, enemyFbxObject[0], 2, 2) == true && timer1 > 60) {
        if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G
            enemyFlag = true;
        }
    }
    // �j�����G2���U��������G2�ƓG3�Ɗj�����G3���`�悳���
    if (OnCollisionCircle(playerFbxObject, nucleusFbxObject[1], 2, 2) == true && timer1 > 60) {
        if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G2
            enemyFlag2 = false;
            // �G3
            enemyFlag3 = false;
            // �j�����G3
            nucleusFlag3 = false;

            // �j�����G2
            nucleusFlag2 = true;
        }
    }
    // �G2��������
    if (OnCollisionCircle(playerFbxObject, enemyFbxObject[1], 1.5f, 1.5f) == true && timer1 > 120) {
        if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G
            enemyFlag2 = true;
        }
    }
    // �G3��������
    if (OnCollisionCircle(playerFbxObject, enemyFbxObject[2], 1.5f, 1.5f) == true && timer1 > 120) {
        if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
            // �G
            enemyFlag3 = true;
        }
    }
    // �j�����G3���U��������Q�[���N���A
        if (OnCollisionCircle(playerFbxObject, nucleusFbxObject[2], 1.5f, 1.5f) == true && timer1 > 120) {
            if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
                //�V�[���؂�ւ�
                SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
            }
        }
    if (OnCollisionCircle(playerFbxObject, nucleusFbxObject[0], 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, nucleusFbxObject[1], 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, nucleusFbxObject[2], 0.2, 0.2) == true || 
        OnCollisionCircle(playerFbxObject, enemyFbxObject[0], 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, enemyFbxObject[1], 0.2, 0.2) == true || OnCollisionCircle(playerFbxObject, enemyFbxObject[2], 0.2, 0.2) == true) {
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
    //sprite->Update();
    end->Update();
    wasd->Update();
    enter->Update();

    // FBX�I�u�W�F�N�g�X�V
    playerFbxObject->Update();

    nucleusFbxObject[0]->Update();
    nucleusFbxObject[1]->Update();
    nucleusFbxObject[2]->Update();

    /*nucleusFbxObject->Update();
    nucleusFbxObject2->Update();
    nucleusFbxObject3->Update();*/

    enemyFbxObject[0]->Update();
    enemyFbxObject[1]->Update();
    enemyFbxObject[2]->Update();

    universeFbxObject->Update();

    /*enemyFbxObject->Update();
    enemyFbxObject2->Update();
    enemyFbxObject3->Update();*/

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
    //sprite->Draw();

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
    // �j�����G�̃t���O�������ĂȂ�������`��
    if (nucleusFlag == false) {
        //objectManager_->Draw();
        nucleusFbxObject[0]->Draw(dxCommon->GetCmdList());
    }
    // �j�����G2�̃t���O�������ĂȂ�������`��
    if (nucleusFlag2 == false) {
        nucleusFbxObject[1]->Draw(dxCommon->GetCmdList());
    }
    // �j�����G3�̃t���O�������ĂȂ�������`��
    if (nucleusFlag3 == false) {
        nucleusFbxObject[2]->Draw(dxCommon->GetCmdList());
    }

    //// �j�����G�̃t���O�������ĂȂ�������`��
    //if (nucleusFlag == false) {
    //    //objectManager_->Draw();
    //    nucleusFbxObject->Draw(dxCommon->GetCmdList());
    //}
    //// �j�����G2�̃t���O�������ĂȂ�������`��
    //if (nucleusFlag2 == false) {
    //    nucleusFbxObject2->Draw(dxCommon->GetCmdList());
    //}
    //// �j�����G3�̃t���O�������ĂȂ�������`��
    //if (nucleusFlag3 == false) {
    //    nucleusFbxObject3->Draw(dxCommon->GetCmdList());
    //}

    // �G�̃t���O�������ĂȂ�������`��
    if (enemyFlag == false) {
        enemyFbxObject[0]->Draw(dxCommon->GetCmdList());
    }
    // �G2�̃t���O�������ĂȂ�������`��
    if (enemyFlag2 == false) {
        enemyFbxObject[1]->Draw(dxCommon->GetCmdList());
    }
    // �G3�̃t���O�������ĂȂ�������`��
    if (enemyFlag3 == false) {
        enemyFbxObject[2]->Draw(dxCommon->GetCmdList());
    }

    //// �G�̃t���O�������ĂȂ�������`��
    //if (enemyFlag == false) {
    //    enemyFbxObject->Draw(dxCommon->GetCmdList());
    //}
    //// �G2�̃t���O�������ĂȂ�������`��
    //if (enemyFlag2 == false) {
    //    enemyFbxObject2->Draw(dxCommon->GetCmdList());
    //}
    //// �G3�̃t���O�������ĂȂ�������`��
    //if (enemyFlag3 == false) {
    //    enemyFbxObject3->Draw(dxCommon->GetCmdList());
    //}

    //universeFbxObject->Draw(dxCommon->GetCmdList());


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
    else {
        wasd->Draw();
        enter->Draw();

    }
}
