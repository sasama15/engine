#include "GamePlayScene2.h"
#include "Input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

void GamePlayScene2::Initialize()
{
	Input* input = Input::GetInstance();
#pragma region �V�[������������
	// ���f�������w�肵�ăt�@�C���ǂݍ���
	playerFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("player");         // �v���C���[
	yetiFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("blueMountain");		// �C�G�e�B

	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();

	// 3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
	 // �v���C���[
	playerFbxObject = new FbxObject3d;
	playerFbxObject->Initialize();
	playerFbxObject->SetModel(playerFbxModel);

	// �C�G�e�B
	yetiFbxObject = new FbxObject3d;
	yetiFbxObject->Initialize();
	yetiFbxObject->SetModel(yetiFbxModel);
	
    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title1.png");
	SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/HP.png");
	SpriteCommon::GetInstance()->LoadTexture(3, L"Resources/HP2.png");
	SpriteCommon::GetInstance()->LoadTexture(4, L"Resources/HP3.png");
	SpriteCommon::GetInstance()->LoadTexture(5, L"Resources/gameend.png");

	// �X�v���C�g�̐���
	title = Sprite::Create(1, { 0, 0 }, false, false);
	hp = Sprite::Create(2, { 0,0 }, false, false);
	hp2 = Sprite::Create(3, { 0,0 }, false, false);
	hp3 = Sprite::Create(4, { 0,0 }, false, false);
	end = Sprite::Create(5, { 0,0 }, false, false);

	endFlag = false;

	// �����ǂݍ���
	soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera);

	camera->SetTarget(playerFbxObject->GetPosition());
	camera->SetDistance(50);

	// �v���C���[�̌���
	playerFbxObject->SetRotation({ 0, 180, 0 });
	// �C�G�e�B�̌���
	yetiFbxObject->SetRotation({ 0, 90, 0 });

	// �v���C���[�A�j���[�V����
	playerFbxObject->PlayAnimation(1);
	// �C�G�e�B�A�j���[�V����
	//yetiFbxObject->PlayAnimation(1);

	hp->SetSize({ 10, 10 });

	// �v���C���[�̑傫��
	playerFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });
	// �C�G�e�B�̑傫��
	yetiFbxObject->SetScale({ 0.1f, 0.1f, 0.1f });

	// �v���C���[�̃|�W�V����
	PlayerPos = { 0,0,50 };
	playerFbxObject->SetPosition({ PlayerPos });

	// �C�G�e�B�̃|�W�V����
	YetiPos = { 15, 0, 100 };
	yetiFbxObject->SetPosition({ YetiPos });
}

void GamePlayScene2::Finalize()
{
	// FBX�I�u�W�F�N�g�A���f�����
	delete playerFbxObject;

	delete playerFbxModel;

	delete camera;
}

void GamePlayScene2::Update()
{
#pragma region DirectX���t���[������
	// DirectX���t���[�������@��������

	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_0)) // ������0�L�[��������Ă�����
	{
		OutputDebugStringA("Hit 0\n");  // �o�̓E�B���h�E�ɁuHit 0�v�ƕ\��
	}

	if ((input->TriggerKey(DIK_SPACE) || input->TriggerButton(static_cast<int>(Button::BACK)))) {
		//�V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

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

	// �e�I�u�W�F�N�g�̔��a
	const float radius1 = 3.0f;
	const float radisu2 = 3.0f;

	// X���W,Y���W���w�肵�ĕ\��
	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	// X���W,Y���W,�k�ڂ��w�肵�ĕ\��
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

	// �X�v���C�g�X�V
	title->Update();
	hp->Update();
	hp2->Update();
	hp3->Update();
	end->Update();

	// FBX�I�u�W�F�N�g�X�V
	playerFbxObject->Update();
	yetiFbxObject->Update();

	camera->Update();

	// DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
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
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDrow();
	// �X�v���C�g�`��
	title->Draw();
	hp->Draw();
	hp2->Draw();
	hp3->Draw();


#pragma region 3D�`��
	DirectXcommon* dxCommon = DirectXcommon::GetInstance();
	// 3D�I�u�W�F�N�g�̕`��
	// �v���C���[�`��
	playerFbxObject->Draw(dxCommon->GetCmdList());
	// �C�G�e�B�`��
	yetiFbxObject->Draw(dxCommon->GetCmdList());
	
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDrow();

	if (endFlag == true) {
		end->Draw();
	}
}
