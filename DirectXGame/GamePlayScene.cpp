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
    fbxModel1 = FbxLoader::GetInstance()->LoadModelFromFile("cube");
    fbxModel2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

    // グラフィックスパイプライン生成
    FbxObject3d::CreateGraphicsPipeline();

    // 3Dオブジェクト生成とモデルのセット
    fbxObject1 = new FbxObject3d;
    fbxObject1->Initialize();
    fbxObject1->SetModel(fbxModel1);
    fbxObject2 = new FbxObject3d;
    fbxObject2->Initialize();
    fbxObject2->SetModel(fbxModel2);

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
    camera->SetTarget({ 0, 20, 10 });
    camera->SetDistance(10.0f);
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
    delete fbxModel1;
    delete fbxModel2;
    delete camera;
}

void GamePlayScene::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

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

    camera->SetTarget(fbxObject2->GetPosition());
    camera->Update();

    Input* input = Input::GetInstance();

    if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
    {
        OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
    }

    if (input->TriggerKey(DIK_SPACE)) {
        //シーン切り替え
        SceneManager::GetInstance()->ChangeScene("TITLE");
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->PushKey(DIK_X)) {
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
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {
        if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
        else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
        if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
        else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
    }

    // 各オブジェクトの半径
    const float radius1 = 3.0f;
    const float radisu2 = 3.0f;

    // X座標,Y座標を指定して表示
    DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    // X座標,Y座標,縮尺を指定して表示
    DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
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
    //objectManager_->Draw();

#pragma region 3D描画
    DirectXcommon* dxCommon = DirectXcommon::GetInstance();
    // 3Dオブジェクトの描画
    //fbxObject1->Draw(dxCommon->GetCmdList());
    fbxObject2->Draw(dxCommon->GetCmdList());

    // パーティクルの描画
    //particleMan->Draw(dxCommon->GetCmdList());
#pragma endregion

    // 3Dオブジェクト描画後処理
    Object3d::PostDraw();

    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
}
