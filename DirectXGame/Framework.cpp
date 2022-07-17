#include "Framework.h"

void Framework::Run()
{
    // ゲームの初期化
    Initialize();

    while (true)  // ゲームループ
    {
        // 毎フレーム更新
        Update();

        // 終了リクエストが来たら抜ける
        if (IsEndRequst()) {
            break;
        }

        // 描画
        Draw();

    }
    // ゲームの終了
    Finalize();
}

void Framework::Initialize()
{
    // WindowsAPIの初期化
    winApp = new WinApp();
    winApp->Initialize();

    // DirectXの初期化
    //dxCommon = new DirectXcommon();
    dxCommon = DirectXcommon::GetInstance();
    dxCommon->Initialize(winApp);

    // スプライト共通部分の初期化
    spriteCommon = SpriteCommon::GetInstance();
    spriteCommon->Initialize(dxCommon->devGeter().Get(), dxCommon->cmdListGeter().Get(), winApp->window_width, winApp->window_height);

    // デバッグテキスト
    debugText = DebugText::GetInstance();

    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 0;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

    // 入力の初期化
    input = Input::GetInstance();
    input->Initialize(winApp);

    // サウンド
    Audio::Initialize();

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 3Dオブジェクト静的初期化
    Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);

    // Fbx関係
    FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());

    // デバイスをセット
    FbxObject3d::SetDevice(dxCommon->GetDev());
    PostSprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // ポストエフェクト用テクスチャの読み込み
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // ポストエフェクトの初期化
    postEffect = new PostEffect();
    postEffect->Initialize();

    MultiRenderTarget::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // ポストエフェクト用テクスチャの読み込み
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // ポストエフェクトの初期化
    postEffect2 = new MultiRenderTarget();
    postEffect2->Initialize();

    MultiTexture::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    // ポストエフェクト用テクスチャの読み込み
    //PostSprite::LoadTexture(100, L"Resources/white.png");
    // ポストエフェクトの初期化
    postEffect3 = new MultiTexture();
    postEffect3->Initialize();
}

void Framework::Finalize()
{
    // シーンファクトリ解放
    //delete sceneFactory_;
    //意図的に開放したい場合は引数なしで開放
    //sceneFactory_.reset();

    // 音声データ解放
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

    // DirectX解放
    //delete dxCommon;

    // Fbx関係
    FbxLoader::GetInstance()->Finalize();

    // PostEffect解放
    delete postEffect;
    delete postEffect2;
    delete postEffect3;

    // WindowsAPIの終了処理
    winApp->Finalize();
    // WindowsAPI解放
    delete winApp;
}

void Framework::Update()
{
#pragma region ウィンドウメッセージ処理
    // Windowsのメッセージ処理
    if (winApp->ProcessMessage()) {
        // ゲームループを抜ける
        endRequst_ = true;
        return;
    }
#pragma endregion ウィンドウメッセージ処理

    // 入力の更新
    input->Update();

    // シーンの更新
    SceneManager::GetInstance()->Update();
}

void Framework::Draw()
{
    // レンダーテクスチャへの描画
    /*postEffect->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect->PostDrawScene(dxCommon->GetCmdList());*/

    /*postEffect2->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect2->PostDrawScene(dxCommon->GetCmdList());*/

    postEffect3->PreDrawScene(dxCommon->GetCmdList());
    SceneManager::GetInstance()->Draw();
    postEffect3->PostDrawScene(dxCommon->GetCmdList());
    
    // 描画前処理
    dxCommon->PreDraw();
    // ポストエフェクトの描画
    //postEffect->Draw(dxCommon->GetCmdList());
    //postEffect2->Draw(dxCommon->GetCmdList());
    postEffect3->Draw(dxCommon->GetCmdList());

    // シーン描画
    //SceneManager::GetInstance()->Draw();

    // デバッグテキスト描画
    //debugText->DrawAll();

    // 描画後処理
    dxCommon->PostDraw();
}
