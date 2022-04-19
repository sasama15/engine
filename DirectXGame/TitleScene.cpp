#include "TitleScene.h"
#include "Input.h"
#include "DebugText.h"
#include "GamePlayScene.h"
#include "SceneManager.h"

TitleScene::TitleScene(SceneManager* sceneManager)
    :BaseScene(sceneManager)
{
}

void TitleScene::Initialize()
{
#pragma region シーン初期化処理

    //// OBJからモデルデータを読み込む
    //model_1 = Model::LoadFromOBJ("ground");
    //model_2 = Model::LoadFromOBJ("triangle_mat");
    //model_3 = Model::LoadFromOBJ("sphere");

    //// 3Dオブジェクト生成
    //object3d_1 = Object3d::Create();
    //object3d_2 = Object3d::Create();
    //object3d_3 = Object3d::Create();

    //// オブジェクトにモデルをひも付ける
    //object3d_1->SetModel(model_1);
    //object3d_2->SetModel(model_2);
    //object3d_3->SetModel(model_2);

    //// 3Dオブジェクトの位置を指定
    //object3d_2->SetPosition({ -5, 0, -5 });
    //object3d_3->SetPosition({ +5, 0, +5 });

    // スプライト共通テクスチャ読み込み
    SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.jpg");
    /*spriteCommon->LoadTexture(1, L"Resources/texture.png");
    spriteCommon->LoadTexture(2, L"Resources/house.png");*/
    //spriteCommon->LoadTexture(1, L"Resources/gamePlay.jpg");

    // スプライトの生成
    sprite = Sprite::Create(1, { 0,0 }, false, false);

    //for (int i = 0; i < 20; i++)
    //{
    //    int texNumber = 1;
    //    Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);
    //    
    //    // スプライトの座標変更
    //    sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });

    //    sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });

    //    // 頂点バッファに反映
    //    sprite->TransferVertexBuffer();

    //    sprites.push_back(sprite);
    //}


    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
}

void TitleScene::Finalize()
{
    // スプライト個別解放
    /*for (auto& sprite : sprites) {*/
    delete sprite;
    /* }
     sprites.clear();*/

    // // 3Dモデル解放
    //delete model_1;
    //delete model_2;
    //delete model_3;
    //// 3Dオブジェクト解放
    //delete object3d_1;
    //delete object3d_2;
    //delete object3d_3;
}

void TitleScene::Update()
{
#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // 3Dオブジェクト更新
    /*object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();*/

    // スプライト更新
    /*for (auto& sprite : sprites) {*/
    sprite->Update();
    /*}*/

    Input* input = Input::GetInstance();

    //if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
    //{
    //    OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
    //}

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    /*if (input->PushKey(DIK_SPACE)) {
        object3d_2->SetModel(model_3);
        object3d_3->SetModel(model_3);
    }*/
    /*else {
        object3d_2->SetModel(model_2);
        object3d_3->SetModel(model_2);
    }*/

    //if (input->TriggerKey(DIK_P)) {
    //    // 音声再生
    //    Audio::SoundPlayWave(soundData2);
    //}

    // カメラ移動
    if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
    {
        /*if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
        else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
        if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
        else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }*/
    }

    if (input->TriggerKey(DIK_RETURN)){
        //シーン切り替え
        BaseScene* scene = new GamePlayScene(sceneManager_);
        sceneManager_->SetNextScene(scene);
    }

    //// 各オブジェクトの半径
    //const float radius1 = 3.0f;
    //const float radisu2 = 3.0f;

    //// X座標,Y座標を指定して表示
    //DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
    //// X座標,Y座標,縮尺を指定して表示
    //DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void TitleScene::Draw()
{
    // スプライト共通コマンド
    SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    /*for (auto& sprite : sprites) {*/
    sprite->Draw();
    /*}*/

    //// 3Dオブジェクト描画前処理
    //Object3d::PreDraw();

    //// 3Dオブジェクトの描画
    //object3d_1->Draw();
    //object3d_2->Draw();
    //object3d_3->Draw();


    //// 3Dオブジェクト描画後処理
    //Object3d::PostDraw();

    // スプライト共通コマンド
    //SpriteCommon::GetInstance()->PreDrow();
    // スプライト描画
    /*for (auto& sprite : sprites) {*/
     //   sprite->Draw();
    /*}*/
}