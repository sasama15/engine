#include "GamePlayScene2.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

void GamePlayScene2::Initialize()
{
	Input* input = Input::GetInstance();
#pragma region シーン初期化処理
	// モデル名を指定してファイル読み込み
	playerFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("player");         // プレイヤー
	yetiFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("blueMountain");		// イエティ

	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();

	// 3Dオブジェクト生成とモデルのセット
	 // プレイヤー
	playerFbxObject = new FbxObject3d;
	playerFbxObject->Initialize();
	playerFbxObject->SetModel(playerFbxModel);

	// イエティ
	yetiFbxObject = new FbxObject3d;
	yetiFbxObject->Initialize();
	yetiFbxObject->SetModel(yetiFbxModel);
	
    // スプライト共通テクスチャ読み込み
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title1.png");
	SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/HP.png");
	SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/HP2.png");
	SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/HP3.png");
	SpriteCommon::GetInstance()->LoadTexture(5, L"Resources/gameend.png");

	// スプライトの生成
	title = Sprite::Create(1, { 0, 0 }, false, false);
	hp = Sprite::Create(2, { 0,0 }, false, false);
	hp2 = Sprite::Create(3, { 0,0 }, false, false);
	hp3 = Sprite::Create(4, { 0,0 }, false, false);
	end = Sprite::Create(5, { 0,0 }, false, false);

	endFlag = false;

	// 音声読み込み
	soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// カメラをセット
	FbxObject3d::SetCamera(camera);

	camera->SetTarget(playerFbxObject->GetPosition());
	camera->SetDistance(50);

	// プレイヤーの向き
	playerFbxObject->SetRotation({ 0, 180, 0 });
	// イエティの向き
	yetiFbxObject->SetRotation({ 0, 90, 0 });

	// プレイヤーアニメーション
	playerFbxObject->PlayAnimation(1);
	// イエティアニメーション
	//yetiFbxObject->PlayAnimation(1);

	hp->SetSize({ 10, 10 });

	// プレイヤーの大きさ
	playerFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });
	// イエティの大きさ
	yetiFbxObject->SetScale({ 0.1f, 0.1f, 0.1f });

	// プレイヤーのポジション
	PlayerPos = { 0,0,50 };
	playerFbxObject->SetPosition({ PlayerPos });

	// イエティのポジション
	YetiPos = { 15, 0, 100 };
	yetiFbxObject->SetPosition({ YetiPos });
}

void GamePlayScene2::Finalize()
{
	// FBXオブジェクト、モデル解放
	delete playerFbxObject;

	delete playerFbxModel;

	delete camera;
}

void GamePlayScene2::Update()
{
#pragma region DirectX毎フレーム処理
	// DirectX毎フレーム処理　ここから

	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
	{
		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}

	if ((input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK)))) {
		//シーン切り替え
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

	// プレイヤー移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
		input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
		input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
		if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z++; }
		if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z--; }
		if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x++; }
		if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x--; }
		playerFbxObject->SetPosition(PlayerPos);
	}

	// 各オブジェクトの半径
	const float radius1 = 3.0f;
	const float radisu2 = 3.0f;

	// X座標,Y座標を指定して表示
	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	// X座標,Y座標,縮尺を指定して表示
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

	// スプライト更新
	title->Update();
	hp->Update();
	hp2->Update();
	hp3->Update();
	end->Update();

	// FBXオブジェクト更新
	playerFbxObject->Update();
	yetiFbxObject->Update();

	camera->Update();

	// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

bool GamePlayScene2::OnCollisionCircle(FbxObject3d* playerCircle, FbxObject3d* enemyCircle, float playerR, float enemyR)
{
	float x = playerCircle->GetPosition().x - enemyCircle->GetPosition().x;
	float y = playerCircle->GetPosition().y - enemyCircle->GetPosition().y;
	float z = playerCircle->GetPosition().z - enemyCircle->GetPosition().z;

	float c = sqrt(x * x + y * y + z * z);
	float sum_radius = playerR + enemyR;

	if (c <= sum_radius)
	{
		return true;
	}
	return false;
}

void GamePlayScene2::Draw()
{
	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDrow();
	// スプライト描画
	title->Draw();
	hp->Draw();
	hp2->Draw();
	hp3->Draw();


#pragma region 3D描画
	DirectXcommon* dxCommon = DirectXcommon::GetInstance();
	// 3Dオブジェクトの描画
	// プレイヤー描画
	playerFbxObject->Draw(dxCommon->GetCmdList());
	// イエティ描画
	yetiFbxObject->Draw(dxCommon->GetCmdList());
	
	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDrow();

	if (endFlag == true) {
		end->Draw();
	}
}
