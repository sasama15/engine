#include "SampleGame.h"
#include "SceneFactory.h"

void SampleGame::Initialize()
{
    // 基底クラスの初期化処理
    Framework::Initialize();

#pragma region WindowsAPI初期化
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

    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region シーン初期化処理
    // シーンマネージャーを生成し、マネージャーにセット
    sceneFactory_ = new SceneFactory();
    SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

    // シーンマネージャーに最初のシーンをセット
    SceneManager::GetInstance()->ChangeScene("TITLE");

#pragma endregion シーン初期化処理
}

void SampleGame::Finalize()
{
   // 基底クラスの終了処理
    Framework::Finalize();
}

void SampleGame::Update()
{
    // 基底クラスの更新処理
    Framework::Update();
}

void SampleGame::Draw()
{
#pragma region グラフィックスコマンド

    // 基底クラスの描画
    Framework::Draw();
}
