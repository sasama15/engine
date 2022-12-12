#include "GamePlayScene.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

void GamePlayScene::Initialize()
{
    Input* input = Input::GetInstance();
#pragma region シーン初期化処理
    // モデル名を指定してファイル読み込み
    //FbxLoader::GetInstance()->LoadModelFromFile("cube");
    //FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
    fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // 敵核持ち
    fbxModel2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // プレイヤー
    fbxModel3 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");    // ノーマル敵

    // グラフィックスパイプライン生成
    FbxObject3d::CreateGraphicsPipeline();

    // 3Dオブジェクト生成とモデルのセット
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

    // OBJからモデルデータを読み込む
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");

    // オブジェクトマネージャ生成
    objectManager_ = std::make_unique<ObjectManager>();

    // 3Dオブジェクト生成
   /* object3d_1 = Object3d::Create();
    object3d_2 = Object3d::Create();
    object3d_3 = Object3d::Create();*/
    // 古いやり方
    /*object3d_1.reset(Object3d::Create());
    object3d_2.reset(Object3d::Create());
    object3d_3.reset(Object3d::Create());*/

    // weak_ptr使うときの残骸
    //std::shared_ptr<Object3d> object3d_1 = Object3d::Create();
    //std::shared_ptr<Object3d> object3d_2 = Object3d::Create();
    //std::shared_ptr<Object3d> object3d_3 = Object3d::Create();

    // weak_ptr使う場合
    /*object3d_1 = objectManager_->AddObject(Object3d::Create(model_1.get()));
    object3d_2 = objectManager_->AddObject(Object3d::Create(model_2.get()));
    object3d_3 = objectManager_->AddObject(Object3d::Create(model_3.get()));*/

    // shared_ptr使う場合
    std::weak_ptr<Object3d> objectWp1 = objectManager_->AddObject(Object3d::Create(model_1.get()));
    std::weak_ptr<Object3d> objectWp2 = objectManager_->AddObject(Object3d::Create(model_2.get()));
    std::weak_ptr<Object3d> objectWp3 = objectManager_->AddObject(Object3d::Create(model_3.get()));
    // オブジェクトの参照カウントを増加
    object3d_1 = objectWp1.lock();
    object3d_2 = objectWp2.lock();
    object3d_3 = objectWp3.lock();

    //C++11以降の方法    newを置き換える場合のみ使用可能
    //object3d_1 = std::make_unique<Object3d>();

    // オブジェクトにモデルをひも付ける
    /*object3d_1->SetModel(model_1.get());
    object3d_2->SetModel(model_2.get());
    object3d_3->SetModel(model_2.get());*/

    // 3Dオブジェクトの位置を指定
    /*object3d_2->SetPosition({ -5, 0, -5 });
    object3d_3->SetPosition({ +5, 0, +5 });*/

    // weak_ptr使う場合
   /* if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
        DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
        object3d_2Sp->SetPosition({ -5, 0, -5 });
    }
    if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
        DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
        object3d_3Sp->SetPosition({ +5, 0, +5 });
    }*/

    // shared_ptr使う場合
    DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
    object3d_2->SetPosition({ -5, 0, -5 });
    DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
    object3d_3->SetPosition({ +5, 0, +5 });

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gamePlay.jpg");
    
    // スプライトの生成
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    // 音声読み込み
    soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

    // カメラをセット
    FbxObject3d::SetCamera(camera);

    // カメラ注視点をセット
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
    // スプライト個別解放
    //delete sprite;

     // 3Dモデル解放
    /*delete model_1;
    delete model_2;
    delete model_3;*/
    // 3Dオブジェクト解放
    /*delete object3d_1;
    delete object3d_2;
    delete object3d_3;*/

    // FBXオブジェクト、モデル解放
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
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから


    /*OldEnemyPos = EnemyPos;
    OldEnemyPos2 = EnemyPos2;
    OldEnemyPos3 = EnemyPos3;*/

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
    {
        OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
    }

    if (input->TriggerKey(DIK_RETURN) || input->TriggerButton(static_cast<int>(Button::BACK))) {
        //シーン切り替え
        SceneManager::GetInstance()->ChangeScene("TITLE");
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->PushKey(DIK_X) || input->TriggerButton(static_cast<int>(Button::X))) {
        /*object3d_2->SetModel(model_3.get());
        object3d_3->SetModel(model_3.get());*/

        // weak_ptrからshare_ptrを取り出す weak_ptr使う場合
       /* if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
            DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
            object3d_2Sp->SetModel(model_3.get());
        }
        if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
            DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
            object3d_3Sp->SetModel(model_3.get());
        }*/

        // shared_ptr使う場合
        DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
        object3d_2->SetModel(model_3.get());
        DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
        object3d_3->SetModel(model_3.get());
    }
    else {
       /* object3d_2->SetModel(model_2.get());
        object3d_3->SetModel(model_2.get());*/

        // weak_ptr使う場合
        /*if (std::shared_ptr<Object3d> object3d_2Sp = object3d_2.lock()) {
            DirectX::XMFLOAT3 pos = object3d_2Sp->GetPosition();
            object3d_2Sp->SetModel(model_2.get());
        }
        if (std::shared_ptr<Object3d> object3d_3Sp = object3d_3.lock()) {
            DirectX::XMFLOAT3 pos = object3d_3Sp->GetPosition();
            object3d_3Sp->SetModel(model_2.get());
        }*/

        //shared_ptr使う場合
        DirectX::XMFLOAT3 pos = object3d_2->GetPosition();
        object3d_2->SetModel(model_2.get());
        DirectX::XMFLOAT3 pos2 = object3d_3->GetPosition();
        object3d_3->SetModel(model_2.get());
    }

    if (input->TriggerKey(DIK_P)) {
        // 音声再生
        Audio::SoundPlayWave(soundData1);
    }

    // カメラ移動
    /*if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {
        if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
        else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
        if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
        else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
    }*/

    // プレイヤー移動
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
        input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
        input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
        if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z++; }
        if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z--; }
        if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x++; }
        if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x--; }
        fbxObject2->SetPosition(PlayerPos);
    }

    // 敵移動
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

    // 当たり判定
    //spherePlayer.center = { object3d_2->GetPosition().x, object3d_2->GetPosition().y, object3d_2->GetPosition().z, 1 };
    //sphereEnemy.center = { object3d_3->GetPosition().x, object3d_3->GetPosition().y, object3d_3->GetPosition().z, 1 };
    //spherePlayer.radius = 2;
    //sphereEnemy.radius = 2;

    //if (SphereCollision(spherePlayer, sphereEnemy) == true) {
    //    flag = true;
    //}
    
    // プレイヤーと敵の距離感
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
    // Dラクエ
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

    // 各オブジェクトの半径
    const float radius1 = 3.0f;
    const float radisu2 = 3.0f;

    // X座標,Y座標を指定して表示
    DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    // X座標,Y座標,縮尺を指定して表示
    DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // 3Dオブジェクト更新
    /*object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();*/
    objectManager_->Update();

    // スプライト更新
    sprite->Update();

    // FBXオブジェクト更新
    fbxObject1->Update();
    fbxObject2->Update();
    fbxObject3->Update();
    fbxObject4->Update();

    camera->Update();

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
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
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    sprite->Draw();

    // 3Dオブジェクト描画前処理
    Object3d::PreDraw();

    // 3Dオブジェクトの描画
    /*object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();*/
   
#pragma region 3D描画
    DirectXcommon* dxCommon = DirectXcommon::GetInstance();
    // 3Dオブジェクトの描画
    
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


    // パーティクルの描画
    //particleMan->Draw(dxCommon->GetCmdList());
#pragma endregion

    // 3Dオブジェクト描画後処理
    Object3d::PostDraw();

    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
}
