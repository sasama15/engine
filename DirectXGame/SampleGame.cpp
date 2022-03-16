#include "SampleGame.h"

void SampleGame::Initialize()
{
#pragma region WindowsAPI初期化
    // WindowsAPIの初期化
    //WinApp* winApp = new WinApp();
    winApp = new WinApp();
    winApp->Initialize();

    // DirectXの初期化
    //DirectXcommon* dxCommon = new DirectXcommon();
    dxCommon = new DirectXcommon();
    dxCommon->Initialize(winApp);

    MSG msg{};  // メッセージ

#pragma region DirectX初期化処理
    // DirectX初期化処理　ここから
#ifdef _DEBUG
    //デバッグレイヤーをオンに
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }
#endif

    HRESULT result;

    // スプライト共通部分の初期化
    //SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->devGeter().Get(), dxCommon->cmdListGeter().Get(), winApp->window_width, winApp->window_height);

    // サウンド
    Audio::Initialize();

    // 音声読み込み
    //Audio::SoundData soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");
    soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 入力の初期化
    //Input* input = new Input();
    input = new Input();
    input->Initialize(winApp);

    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理
    // 3Dオブジェクト静的初期化
    Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

    // OBJからモデルデータを読み込む
    /*Model* model_1 = Model::LoadFromOBJ("ground");
    Model* model_2 = Model::LoadFromOBJ("triangle_mat");
    Model* model_3 = Model::LoadFromOBJ("sphere");*/
    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");
    model_3 = Model::LoadFromOBJ("sphere");

    // 3Dオブジェクト生成
    /*Object3d* object3d_1 = Object3d::Create();
    Object3d* object3d_2 = Object3d::Create();
    Object3d* object3d_3 = Object3d::Create();*/
    object3d_1 = Object3d::Create();
    object3d_2 = Object3d::Create();
    object3d_3 = Object3d::Create();

    // オブジェクトにモデルをひも付ける
    object3d_1->SetModel(model_1);
    object3d_2->SetModel(model_2);
    object3d_3->SetModel(model_2);

    // 3Dオブジェクトの位置を指定
    object3d_2->SetPosition({ -5, 0, -5 });
    object3d_3->SetPosition({ +5, 0, +5 });

    // スプライト共通テクスチャ読み込み
    /*spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");*/
    spriteCommon->LoadTexture(1, L"Resources/texture.png");
    spriteCommon->LoadTexture(2, L"Resources/house.png");

    //std::vector<Sprite*> sprites;

    // スプライトの生成
    for (int i = 0; i < 20; i++)
    {
        //int texNumber = rand() % 2;
        int texNumber = 1;
        Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

        // スプライトの座標変更
        sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });

        sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });

        // 頂点バッファに反映
        sprite->TransferVertexBuffer();

        sprites.push_back(sprite);
    }

    // デバッグテキスト
    //DebugText* debugText = new DebugText();
    debugText = new DebugText();

    // デバッグテキスト用のテクスチャ番号を指定
    //const int debugTextTexNumber = 2;
    const int debugTextTexNumber = 0;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

#pragma endregion 描画初期化処理

    //int counter = 0; // アニメーションの経過時間カウンター
}

void SampleGame::Finalize()
{
    // 音声データ解放
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

#pragma region WindowsAPI後始末
    // WindowsAPIの終了処理
    winApp->Finalize();

#pragma endregion WindowsAPI後始末
#pragma endregion WindowsAPI初期化

    // デバッグテキスト解放
    delete debugText;

    // スプライト個別解放
    for (auto& sprite : sprites) {
        delete sprite;
    }
    sprites.clear();
    // スプライト共通部分解放
    delete spriteCommon;

    // 3Dモデル解放
    delete model_1;
    delete model_2;
    delete model_3;
    // 3Dオブジェクト解放
    delete object3d_1;
    delete object3d_2;
    delete object3d_3;

    // DirectX解放
    delete dxCommon;
    // 入力解放
    delete input;
    // WindowsAPI解放
    delete winApp;
}

void SampleGame::Update()
{
#pragma region ウィンドウメッセージ処理
    // Windowsのメッセージ処理
    if (winApp->ProcessMessage()) {
        // ゲームループを抜ける
        endRequst_ = true;
        return;
    }

#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
    // DirectX毎フレーム処理　ここから

    // 入力の更新
    input->Update();

    // 3Dオブジェクト更新
    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    // スプライト更新
    for (auto& sprite : sprites) {
        sprite->Update();
    }

    //const int cycle = 540; // 繰り返しの周期
    //counter++;
    //counter %= cycle; // 周期を超えたら0に戻る
    //float scale = (float)counter / cycle; // [0,1]の数値

    //scale *= 360.0f;

    //float offset = sinf(XM_2PI * (float)counter / cycle);
    //offset *= 10.0f;

    if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
    {
        OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
    }

    float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

    if (input->PushKey(DIK_SPACE)) {
        object3d_2->SetModel(model_3);
        object3d_3->SetModel(model_3);
    }
    else {
        object3d_2->SetModel(model_2);
        object3d_3->SetModel(model_2);
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
    debugText->Print("Hello,DirectX!!", 200, 100);
    // X座標,Y座標,縮尺を指定して表示
    debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

    // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void SampleGame::Draw()
{
#pragma region グラフィックスコマンド
    // 描画前処理
    dxCommon->PreDraw();

    // 3Dオブジェクト描画前処理
    Object3d::PreDraw(dxCommon->GetCmdList());

    // 3Dオブジェクトの描画
    object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();


    // 3Dオブジェクト描画後処理
    Object3d::PostDraw();

    // スプライト共通コマンド
    spriteCommon->PreDrow();
    // スプライト描画
    for (auto& sprite : sprites) {
        sprite->Draw();
    }

    // デバッグテキスト描画
    debugText->DrawAll();

    // 描画後処理
    dxCommon->PostDraw();

    // ４．描画コマンドここまで
}
