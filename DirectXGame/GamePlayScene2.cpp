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
	bulletFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("iceBullet");		// 弾

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

	// 弾
	bulletFbxObject = new FbxObject3d;
	bulletFbxObject->Initialize();
	bulletFbxObject->SetModel(bulletFbxModel);

	// 弾がプレイヤーに飛ぶ
	/*for (int i = 0; i < iceMax; i++) {
	bulletFbxObject[i] = new FbxObject3d;
	bulletFbxObject[i]->Initialize();
	bulletFbxObject[i]->SetModel(bulletFbxModel);
	}*/
	
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

	// プレイヤーの向き
	playerFbxObject->SetRotation({ 0, 180, 0 });
	// イエティの向き
	yetiFbxObject->SetRotation({ 0, 90, 0 });

	// プレイヤーアニメーション
	playerFbxObject->PlayAnimation(1);
	// イエティアニメーション
	//yetiFbxObject->PlayAnimation(1);

	// HP表示大きさ
	hp->SetSize({ 100, 100 });
	hp2->SetSize({ 250, 250 });
	hp3->SetSize({ 100, 100 });

	// プレイヤーの大きさ
	playerFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });
	// イエティの大きさ
	yetiFbxObject->SetScale({ 0.05f, 0.05f, 0.05f });
	// 弾の大きさ
	bulletFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });
	//bulletFbxObject[0]->SetScale({0.025f, 0.025f, 0.025f});
	/*bulletFbxObject[1]->SetScale({ 0.025f, 0.025f, 0.025f });
	bulletFbxObject[2]->SetScale({ 0.025f, 0.025f, 0.025f });
	bulletFbxObject[3]->SetScale({ 0.025f, 0.025f, 0.025f });
	bulletFbxObject[4]->SetScale({ 0.025f, 0.025f, 0.025f });*/

	// プレイヤーのポジション
	PlayerPos = { 0,0,25 };
	playerFbxObject->SetPosition({ PlayerPos });

	// イエティのポジション
	YetiPos = { 0, 0, 70 };
	yetiFbxObject->SetPosition({ YetiPos });

	// 弾のポジション
	BulletPos = { 0, 0, 70 };
	bulletFbxObject->SetPosition({ BulletPos });
	//bulletFbxObject[0]->SetPosition({BulletPos});
	/*bulletFbxObject[1]->SetPosition({ BulletPos });
	bulletFbxObject[2]->SetPosition({ BulletPos });
	bulletFbxObject[3]->SetPosition({ BulletPos });
	bulletFbxObject[4]->SetPosition({ BulletPos });*/

	hp2->SetPosition({ 515, 300.5f, 0});

	camera->SetTarget({ playerFbxObject->GetPosition().x, playerFbxObject->GetPosition().y, playerFbxObject->GetPosition().z + 20 });
	camera->SetDistance(50);

	bulletFlag = false;
	BulletJampPower = 0.3f;
}

void GamePlayScene2::Finalize()
{
	// FBXオブジェクト、モデル解放
	delete playerFbxObject;
	delete yetiFbxObject;
	delete bulletFbxObject;

	delete playerFbxModel;
	delete yetiFbxModel;
	delete bulletFbxModel;

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

	//if (bulletFlag == false){
	//	BulletPos = { 0,0,0 };
	//	bulletFbxObject->SetPosition(yetiFbxObject->GetPosition());
	//	bulletFlag = true;
	//}
	//if (bulletFbxObject->GetPosition().z < playerFbxObject->GetPosition().z) {
	//	bulletFlag = false;
	//}

	//if (bulletFlag == true){
	//	BulletPos.z += 0.4f;
	//	//bulletFbxObject->SetPosition({YetiPos.x - BulletPos.x,YetiPos.y - BulletPos.y,YetiPos.z - BulletPos.z});

	//	//ジャンプ
	//	BulletPos.y -= BulletGravity;
	//	bulletFbxObject->SetPosition({ BulletPos });
	//	if (BulletPos.y <= 20 && BulletJump == true) {
	//		BulletPos.y += 0.2;
	//		BulletGravity += 0.005f;
	//		bulletFbxObject->SetPosition({ YetiPos.x - BulletPos.x,YetiPos.y - BulletPos.y,YetiPos.z - BulletPos.z });
	//	}
	//	if (BulletPos.y >= 20) {
	//		BulletJump = false;
	//	}
	//	if (BulletPos.y <= 0) {
	//		BulletGravity = 0.1f;
	//		BulletPos.y = 0;
	//		BulletJump = true;
	//		bulletFbxObject->SetPosition({ YetiPos.x - BulletPos.x,YetiPos.y - BulletPos.y,YetiPos.z - BulletPos.z });
	//	}
	//}

	//弾が飛びながら飛ぶ
	if (shootFlag == false) {
		if (bulletFlag == false) {

			oldPlayerPos = playerFbxObject->GetPosition();

			//移動
			BulletGravity = 0;
			BulletPos.x = 0;
			BulletPos.y = 0;
			BulletPos.z = 0;
			bulletFbxObject->SetPosition(yetiFbxObject->GetPosition());
			bulletFlag = true;
		}
		if (bulletFbxObject->GetPosition().y < -10) {
			bulletFlag = false;
		}

		if (bulletFlag == true) {
			if (oldPlayerPos.z < bulletFbxObject->GetPosition().z) {
				BulletPos.z += 0.4f;
			}
			if (oldPlayerPos.x <= bulletFbxObject->GetPosition().x) {
				BulletPos.x = BulletPos.x + BulletJampPower;
			}
			if (oldPlayerPos.x >= bulletFbxObject->GetPosition().x) {
				BulletPos.x = BulletPos.x - BulletJampPower;
			}
			BulletGravity += 0.005f;
			BulletPos.y = BulletPos.y - BulletJampPower;
			BulletPos.y += BulletGravity;
			bulletFbxObject->SetPosition({ YetiPos.x - BulletPos.x, YetiPos.y - BulletPos.y, YetiPos.z - BulletPos.z });
		}
		//if(bulletFlag == false){
		//	
		//	/*if (playerFbxObject->GetPosition().z <= bulletFbxObject->GetPosition().z) {
		//		BulletPos.z = BulletPos.z + BulletJampPower;
		//	}
		//	if (playerFbxObject->GetPosition().z >= bulletFbxObject->GetPosition().z) {
		//		BulletPos.z = BulletPos.z - BulletJampPower;
		//	}*/
		//}
	}

	if (onrushFlag == true) {
		shootFlag = true;
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
	bulletFbxObject->Update();
	/*bulletFbxObject[1]->Update();
	bulletFbxObject[2]->Update();
	bulletFbxObject[3]->Update();
	bulletFbxObject[4]->Update();*/

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
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw();

	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDrow();
	// スプライト描画
	title->Draw();
	hp->Draw();
	//hp2->Draw();
	//hp3->Draw();


#pragma region 3D描画
	DirectXcommon* dxCommon = DirectXcommon::GetInstance();
	// 3Dオブジェクトの描画
	// プレイヤー描画
	playerFbxObject->Draw(dxCommon->GetCmdList());
	// イエティ描画
	yetiFbxObject->Draw(dxCommon->GetCmdList());
	// 弾描画
	bulletFbxObject->Draw(dxCommon->GetCmdList());
	/*bulletFbxObject[1]->Draw(dxCommon->GetCmdList());
	bulletFbxObject[2]->Draw(dxCommon->GetCmdList());
	bulletFbxObject[3]->Draw(dxCommon->GetCmdList());
	bulletFbxObject[4]->Draw(dxCommon->GetCmdList());*/

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDrow();

	if (endFlag == true) {
		end->Draw();
	}
}
