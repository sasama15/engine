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
    dxCommon = new DirectXcommon();
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
    //Input* input = new Input();
    input = Input::GetInstance();
    input->Initialize(winApp);

    // サウンド
    Audio::Initialize();

    // 音声読み込み
    //soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

    // 3Dオブジェクト静的初期化
    Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);

    // シーンマネージャーの生成
    sceneManager_ = new SceneManager;
}

void Framework::Finalize()
{
    // シーンマネージャー解放
    delete sceneManager_;

    // 音声データ解放
    Audio::SoundUnload(&soundData1);

    Audio::Finalize();

    // DirectX解放
    delete dxCommon;

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
    sceneManager_->Update();
}

void Framework::Draw()
{
    // 描画前処理
    dxCommon->PreDraw();

    // シーン描画
    sceneManager_->Draw();

    // デバッグテキスト描画
    debugText->DrawAll();

    // 描画後処理
    dxCommon->PostDraw();
}
