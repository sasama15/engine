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
	bulletFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("iceBullet");		// �e
	universeFbxModel = FbxLoader::GetInstance()->LoadModelFromFile("universe");     // �w�i

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

	// �e
	for (int i = 0; i < iceMax; i++) {
		bulletFbxObject[i] = new FbxObject3d;
		bulletFbxObject[i]->Initialize();
		bulletFbxObject[i]->SetModel(bulletFbxModel);
	}

	// �w�i�F��
	universeFbxObject = new FbxObject3d;
	universeFbxObject->Initialize();
	universeFbxObject->SetModel(universeFbxModel);

	// OBJ���烂�f���f�[�^��ǂݍ���
	//model_particle = Model::LoadFromOBJ("sphere");

	// �I�u�W�F�N�g�}�l�[�W������
	//particleObjectManager_ = std::make_unique<ParticleObjectManager>();

	// shared_ptr�g���ꍇ
	/*std::weak_ptr<ParticleManager> particleWp = particleObjectManager_->AddObject(ParticleManager::Create(model_particle.get()));
	object_particle = particleWp.lock();*/
	/*DirectX::XMFLOAT3 pos = object_particle->GetPosition();
	object_particle->SetPosition({ -5, 0, -5 });*/

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

	// �p�[�e�B�N���֘A
	//particleMan = ParticleManager::Create();
	//for (int i = 0; i < 100; i++) {
	//	// X, Y, Z�S��[-5.0f, +5.0f]�Ń����_���ɕ��z
	//	const float rnd_pos = 10.0f;
	//	XMFLOAT3 pos{};
	//	pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

	//	// X, Y, Z�S��[-0.05f, +0.05f]�Ń����_���ɕ��z
	//	const float rnd_vel = 0.1f;
	//	XMFLOAT3 vel{};
	//	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	// �d�͂Ɍ����Ă�Y�̂�[-0.0001f, 0]�Ń����_���ɕ��z
	//	XMFLOAT3 acc{};
	//	const float rnd_acc = 0.001f;
	//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

	//	// �ǉ�
	//	particleMan->Add(60, pos, vel, acc);
	//}


	/*endFlag = false;*/

	// �����ǂݍ���
	soundData1 = Audio::SoundLoadWave("Resources/Alarm01.wav");

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera);

	// �p�[�e�B�N��
	//particleMan = ParticleManager::GetInstance();

	// �v���C���[�̌���
	PlayerRotation = { 0, 180, 0 };
	playerFbxObject->SetRotation({ PlayerRotation });
	// �C�G�e�B�̌���
	yetiFbxObject->SetRotation({ 0, 90, 0 });

	// �v���C���[�A�j���[�V����
	walkAnimationFlag = false;

	// HP�\���傫��
	hp->SetSize({ 100, 100 });
	hp2->SetSize({ 500, 500 });
	hp3->SetSize({ 750, 750 });

	// �v���C���[�̑傫��
	playerFbxObject->SetScale({ 0.01f, 0.01f, 0.01f });
	// �C�G�e�B�̑傫��
	yetiFbxObject->SetScale({ 0.05f, 0.05f, 0.05f });
	// �e�̑傫��
	for (int i = 0; i < 5; i++) {
		bulletFbxObject[i]->SetScale({ 0.01f, 0.01f, 0.01f });
	}

	universeFbxObject->SetScale({ 5.0f, 5.0f, 5.0f });

	universeFbxObject->SetRotation({ 0, 0, 0 });

	// �v���C���[�̃|�W�V����
	PlayerPos = { 0,0,25 };
	playerFbxObject->SetPosition({ PlayerPos });

	// �C�G�e�B�̃|�W�V����
	YetiPos = { 0, 0, 70 };
	yetiFbxObject->SetPosition({ YetiPos });

	// �e�̃|�W�V����
	for (int i = 0; i < 5; i++) {
		BulletPos[i] = { 0, 0, 70 };
		bulletFbxObject[i]->SetPosition({ BulletPos[i] });
	}

	UniversePos = { 0, playerFbxObject->GetPosition().y, -100};
	universeFbxObject->SetPosition({ UniversePos });

	hp2->SetPosition({ 390, 110, 0});
	hp3->SetPosition({ 265, -15, 0 });

	camera->SetTarget({ playerFbxObject->GetPosition().x, playerFbxObject->GetPosition().y, playerFbxObject->GetPosition().z + 20 });
	camera->SetDistance(50);

	// �t���O��^�C�}�[�֘A
	playerFlag = true;
	yetiFlag = true;

	for (int i = 0; i < 5; i++) {
		bulletFlag[i] = false;
	}
	BulletJampPower = 0.4f;

	rollingFlag = false;
	clearFlag = false;
	endFlag = false;

	stopFlag = false;
	stopFlag2 = false;

	particleFlag = false;

	iceBulletTimer = 0;
	rollingTimer = 0;
	rollingNum = 0;

	stopTimer = 0;
	clearStopTimer = 0;

	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);
	particleSmoke = ParticleManager::GetInstance();
	particleSmoke->SetCamera(camera);
	particleGone = ParticleManager::GetInstance();
	particleGone->SetCamera(camera);
	particleBlood = ParticleManager::GetInstance();
	particleBlood->SetCamera(camera);
}

void GamePlayScene2::Finalize()
{
	// 3D���f�����
	/*delete model_particle;*/
	// 3D�I�u�W�F�N�g���
	//delete object_particle;
	
	// FBX�I�u�W�F�N�g�A���f�����
	delete playerFbxObject;
	delete yetiFbxObject;
	for (int i = 0; i < 5; i++) {
		delete bulletFbxObject[i];
	}
	delete universeFbxObject;

	delete playerFbxModel;
	delete yetiFbxModel;
	delete bulletFbxModel;
	delete universeFbxModel;

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
	if (stopTimer == 0 && clearStopTimer == 0) {
		//�e���ʂ�`���Ȃ�����
		if (rollingFlag == false) {

			iceBulletTimer++;
			for (int i = 0; i < 5; i++) {
				if (bulletFlag[i] == false) {
					//�ړ�
					BulletGravity[i] = 0;
					BulletPos[i] = { 0, 0, 0 };
					bulletFbxObject[i]->SetPosition(yetiFbxObject->GetPosition());
					oldPlayerPos[i] = playerFbxObject->GetPosition();
					if (iceBulletTimer >= 30) {

						bulletFlag[i] = true;
						iceBulletTimer = 0;
					}
					break;
				}
			}

			for (int i = 0; i < 5; i++) {
				if (bulletFbxObject[4]->GetPosition().y < -10) {
					iceBulletTimer = 0;
					for (int s = 0; s < 5; s++) {
						BulletGravity[s] = 0;
						BulletPos[s] = { 0, 0, 0 };
						bulletFbxObject[s]->SetPosition(yetiFbxObject->GetPosition());
						bulletFlag[s] = false;
					}
					rollingFlag = true;
				}
				if (bulletFlag[i] == true) {
					if (oldPlayerPos[i].z < bulletFbxObject[i]->GetPosition().z) {
						BulletPos[i].z += 0.4f;
					}
					if (oldPlayerPos[i].z > bulletFbxObject[i]->GetPosition().z) {
						BulletPos[i].z -= 0.4f;
					}
					if (oldPlayerPos[i].x <= bulletFbxObject[i]->GetPosition().x) {
						BulletPos[i].x = BulletPos[i].x + BulletJampPower;
					}
					if (oldPlayerPos[i].x >= bulletFbxObject[i]->GetPosition().x) {
						BulletPos[i].x = BulletPos[i].x - BulletJampPower;
					}
					BulletGravity[i] += 0.005f;
					BulletPos[i].y = BulletPos[i].y - BulletJampPower;
					BulletPos[i].y += BulletGravity[i];
					bulletFbxObject[i]->SetPosition({ YetiPos.x - BulletPos[i].x, YetiPos.y - BulletPos[i].y, YetiPos.z - BulletPos[i].z });
				}
			}
		}

		// �ːi
		if (rollingFlag == false) {
			rollingTimer = 0;
			rollingNum = 0;
		}
		if (rollingTimer == 0) {
			oldPlayerPos2 = playerFbxObject->GetPosition();
			if (rollingFlag == true) {
				rollingTimer = 1;
			}
		}
		if (rollingFlag == true && rollingTimer >= 1) {
			iceBulletTimer = 0;
			if (oldPlayerPos2.z < yetiFbxObject->GetPosition().z) {
				YetiPos.z -= 0.4f;
			}
			if (oldPlayerPos2.z > yetiFbxObject->GetPosition().z) {
				YetiPos.z += 0.4f;
			}
			if (oldPlayerPos2.x <= yetiFbxObject->GetPosition().x) {
				YetiPos.x = YetiPos.x - 0.4f;
			}
			if (oldPlayerPos2.x >= yetiFbxObject->GetPosition().x) {
				YetiPos.x = YetiPos.x + 0.4f;
			}
			if (yetiFbxObject->GetPosition().x <= oldPlayerPos2.x + 0.4f && yetiFbxObject->GetPosition().x >= oldPlayerPos2.x - 0.4f &&
				yetiFbxObject->GetPosition().z <= oldPlayerPos2.z + 0.4f && yetiFbxObject->GetPosition().z >= oldPlayerPos2.z - 0.4f) {
				rollingTimer++;
				if (rollingTimer >= 60) {
					rollingNum++;
					if (rollingNum == 3) {
						rollingFlag = false;
					}
					rollingTimer = 0;
				}
			}

			for (int i = 0; i < 5; i++) {
				bulletFbxObject[i]->SetPosition(yetiFbxObject->GetPosition());
			}
			yetiFbxObject->SetPosition({ YetiPos.x, YetiPos.y, YetiPos.z });
		}
	}

	float clearColor[] = { 0.1f, 0.25f, 0.5f, 0.0f }; // ���ۂ��F

	// �v���C���[�ړ�
	if (walkAnimationFlag == true || attackAnimationFlag == true) {
		playerFbxObject->SetIsPlay(true);
	}
	else{
		//�A�j���[�V�������~�߂�
		playerFbxObject->SetIsPlay(false);
	}
	if (playerFbxObject->animationIsEnd() == true){
		if (input->TriggerKey(DIK_W) || input->TriggerKey(DIK_S) || input->TriggerKey(DIK_D) || input->TriggerKey(DIK_A) ||
			input->TriggerButton(static_cast<int>(Button::UP)) || input->TriggerButton(static_cast<int>(Button::DOWN)) ||
			input->TriggerButton(static_cast<int>(Button::RIGHT)) || input->TriggerButton(static_cast<int>(Button::LEFT))) {
			playerFbxObject->PlayAnimation(1, true);
		}
	}
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
		input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
		input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
		if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z += 0.5f; }
		if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z -= 0.5f; }
		if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x += 0.5f; }
		if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x -= 0.5f; }
		playerFbxObject->SetPosition(PlayerPos);
		walkAnimationFlag = true;
		// shared_ptr�g���ꍇ
		//DirectX::XMFLOAT3 pos = object_particle->GetPosition();
		//object_particle->SetModel(model_particle.get());
	}
	else {
		walkAnimationFlag = false;
	}

	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A) ||
		input->PushButton(static_cast<int>(Button::UP)) || input->PushButton(static_cast<int>(Button::DOWN)) ||
		input->PushButton(static_cast<int>(Button::RIGHT)) || input->PushButton(static_cast<int>(Button::LEFT))) {
		if (input->TriggerKey(DIK_LSHIFT)) {
			if (input->PushKey(DIK_W) || input->PushButton(static_cast<int>(Button::UP))) { PlayerPos.z += 2.0f; }
			if (input->PushKey(DIK_S) || input->PushButton(static_cast<int>(Button::DOWN))) { PlayerPos.z -= 2.0f; }
			if (input->PushKey(DIK_D) || input->PushButton(static_cast<int>(Button::RIGHT))) { PlayerPos.x += 2.0f; }
			if (input->PushKey(DIK_A) || input->PushButton(static_cast<int>(Button::LEFT))) { PlayerPos.x -= 2.0f; }
			playerFbxObject->SetPosition(PlayerPos);
			particleSmoke->LoadTexture(L"Resources/smoke.png");
			for (int i = 0; i < 100; i++) {
				//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
				/*const float rnd_pos = 1.0f;
				XMFLOAT3 pos{};
				pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;*/
				//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
				const float rnd_vel = 0.01f;
				XMFLOAT3 vel{};
				//vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = 0.2f;
				//vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
				XMFLOAT3 acc{};
				const float rnd_acc = 0.001f;
				acc.y = -(float)rand() / RAND_MAX * rnd_acc;

				//�ǉ�
				particleSmoke->Add(60, { playerFbxObject->GetPosition().x,  playerFbxObject->GetPosition().y - 5, playerFbxObject->GetPosition().z }, vel, acc, 3.0f, 0.0f);
			}
		}
	}


	if (input->TriggerKey(DIK_RETURN)) {
		attackAnimationFlag = true;
		playerFbxObject->PlayAnimation(0, false);
	}

	if (playerFbxObject->animationIsEnd() == true) {
		attackAnimationFlag = false;
	}

	//for (int i = 0; i < 100; i++) {
	//	// X, Y, Z�S��[-5.0f, +5.0f]�Ń����_���ɕ��z
	//	const float rnd_pos = 10.0f;
	//	XMFLOAT3 pos{};
	//	pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	// X, Y, Z�S��[-0.05f, + 0.05f]�Ń����_���ɕ��z
	//	const float rnd_vel = 0.1f;
	//	XMFLOAT3 vel{};
	//	pos.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	pos.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	pos.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	// �d�͂Ɍ����Ă�Y�̂�[-0.0001f, 0]�Ń����_���ɕ��z
	//	XMFLOAT3 acc{};
	//	const float rnd_acc = 0.001f;
	//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

	//	// �ǉ�
	//	particleMan->Add(60, pos, vel, acc);
	//	break;
	//}
	//if (input->TriggerKey(DIK_Q)) {
	//	particleMan->LoadTexture(L"Resources/HP.png");
	//	for (int i = 0; i < 100; i++) {
	//		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
	//		const float rnd_pos = 1.0f;
	//		XMFLOAT3 pos{};
	//		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
	//		const float rnd_vel = 0.1f;
	//		XMFLOAT3 vel{};
	//		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//		//�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
	//		XMFLOAT3 acc{};
	//		const float rnd_acc = 0.001f;
	//		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

	//		//�ǉ�
	//		particleMan->Add(60, { playerFbxObject->GetPosition().x,  playerFbxObject->GetPosition().y + 5, playerFbxObject->GetPosition().z - 5 }, vel, acc, 100.0f, 0.0f);
	//	}
	//}

	if (OnCollisionCircle(playerFbxObject, yetiFbxObject, 5, 7) == true) {
		if (input->TriggerKey(DIK_RETURN) || input->PushButton(static_cast<int>(Button::B))) {
			particleMan->LoadTexture(L"Resources/particlePla.png");
			for (int i = 0; i < 100; i++) {
				//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
				/*const float rnd_pos = 1.0f;
				XMFLOAT3 pos{};
				pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;*/
				//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
				const float rnd_vel = 0.1f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
				XMFLOAT3 acc{};
				const float rnd_acc = 0.001f;
				acc.y = -(float)rand() / RAND_MAX * rnd_acc;

				//�ǉ�
				particleMan->Add(60, { yetiFbxObject->GetPosition().x,  yetiFbxObject->GetPosition().y + 5, yetiFbxObject->GetPosition().z -5 }, vel, acc, 10.0f, 0.0f);
			}
			// �C�G�e�B
			yetiFlag = false;

			clearFlag = true;
			//�V�[���؂�ւ�
			//SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
		}
	}

	// �N���A�t���O��������N���A��ʂ�
	if (clearFlag == true) {
		endFlag = false;
		clearStopTimer++;
		if (clearStopTimer >= 120) {
			stopFlag = true;
		}
		if (clearStopTimer >= 240) {
			stopFlag = false;
			stopFlag2 = true;
		}
		if (clearStopTimer >= 360) {
			stopFlag2 = false;
			//particleMan = ParticleManager::Create();
			particleGone->LoadTexture(L"Resources/Gone-export.png");
			for (int i = 0; i < 100; i++) {
				// X, Y, Z�S��[-5.0f, +5.0f]�Ń����_���ɕ��z
				const float rnd_pos = 1000.0f;
				XMFLOAT3 pos{};
				pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

				// X, Y, Z�S��[-0.05f, +0.05f]�Ń����_���ɕ��z
				const float rnd_vel = 0.1f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				// �d�͂Ɍ����Ă�Y�̂�[-0.0001f, 0]�Ń����_���ɕ��z
				XMFLOAT3 acc{};
				const float rnd_acc = 0.001f;
				acc.y = -(float)rand() / RAND_MAX * rnd_acc;

				// �ǉ�
				particleGone->Add(60, pos, vel, acc, 10.0f, 0.0f);
			}
			// �v���C���[
			//playerFlag = false;
		}
		if (clearStopTimer >= 500) {
			SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
		}
	}

	/*if (yetiFlag == false) {
		if (input->TriggerKey(DIK_SPACE)) {
			SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
		}
	}*/

	/*if (yetiFlag == false) {
		endFlag = false;
	}*/
	if (particleFlag == true) {
		particleBlood->LoadTexture(L"Resources/particleEne.png");
		for (int i = 0; i < 100; i++) {
			//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
			/*const float rnd_pos = 1.0f;
			XMFLOAT3 pos{};
			pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;*/
			//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//�d�͂Ɍ����Ă�Y�̂�[-0.0001f,0]�Ń����_���ɕ��z
			XMFLOAT3 acc{};
			const float rnd_acc = 0.001f;
			acc.y = -(float)rand() / RAND_MAX * rnd_acc;

			//�ǉ�
			particleBlood->Add(10, { playerFbxObject->GetPosition().x,  playerFbxObject->GetPosition().y, playerFbxObject->GetPosition().z }, vel, acc, 5.0f, 0.0f);
		}
	}

	// �G���e�ɓ���������G���h
	if (OnCollisionCircle(playerFbxObject, yetiFbxObject, 5, 4) == true || OnCollisionCircle(playerFbxObject, bulletFbxObject[0], 2, 2) == true || OnCollisionCircle(playerFbxObject, bulletFbxObject[1], 2, 2) == true ||
		OnCollisionCircle(playerFbxObject, bulletFbxObject[2], 2, 2) == true || OnCollisionCircle(playerFbxObject, bulletFbxObject[3], 2, 2) == true ||
		OnCollisionCircle(playerFbxObject, bulletFbxObject[4], 2, 2) == true) {
		endFlag = true;
		particleFlag = true;
	}

	// �G���h�t���O��������G���h��ʂ�
	if (endFlag == true) {
		clearFlag = false;
		stopTimer++;
		if (stopTimer >= 120) {
			particleFlag = false;
			particleBlood->LoadTexture(L"Resources/particleEne.png");
			for (int i = 0; i < 100; i++) {
				// X, Y, Z�S��[-5.0f, +5.0f]�Ń����_���ɕ��z
				const float rnd_pos = 1000.0f;
				XMFLOAT3 pos{};
				pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

				// X, Y, Z�S��[-0.05f, +0.05f]�Ń����_���ɕ��z
				const float rnd_vel = 0.1f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				// �d�͂Ɍ����Ă�Y�̂�[-0.0001f, 0]�Ń����_���ɕ��z
				XMFLOAT3 acc{};
				const float rnd_acc = 0.001f;
				acc.y = -(float)rand() / RAND_MAX * rnd_acc;

				// �ǉ�
				particleBlood->Add(60, pos, vel, acc, 10.0f, 0.0f);
			}
			// �v���C���[
			playerFlag = false;
			//stopFlag = true;
		}
		if (stopTimer >= 240) {
			/*stopFlag = false;
			stopFlag2 = true;*/
		}
		if (stopTimer >= 360) {
			SceneManager::GetInstance()->ChangeScene("GAMEEND");
			//stopFlag2 = false;
			//particleMan = ParticleManager::Create();
			//particleBlood->LoadTexture(L"Resources/particleEne.png");
			//for (int i = 0; i < 100; i++) {
			//	// X, Y, Z�S��[-5.0f, +5.0f]�Ń����_���ɕ��z
			//	const float rnd_pos = 1000.0f;
			//	XMFLOAT3 pos{};
			//	pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			//	pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			//	pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

			//	// X, Y, Z�S��[-0.05f, +0.05f]�Ń����_���ɕ��z
			//	const float rnd_vel = 0.1f;
			//	XMFLOAT3 vel{};
			//	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//	vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//	// �d�͂Ɍ����Ă�Y�̂�[-0.0001f, 0]�Ń����_���ɕ��z
			//	XMFLOAT3 acc{};
			//	const float rnd_acc = 0.001f;
			//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

			//	// �ǉ�
			//	particleBlood->Add(60, pos, vel, acc, 10.0f, 0.0f);
			//}
			// �v���C���[
			/*playerFlag = false;*/
		}
		if (stopTimer >= 500) {
				SceneManager::GetInstance()->ChangeScene("GAMEEND");
		}
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
	//bulletFbxObject->Update();

	for (int i = 0; i < 5; i++) {
		bulletFbxObject[i]->Update();
	}

	universeFbxObject->Update();

	// �p�[�e�B�N���I�u�W�F�N�g�X�V
	/*object_particle->Update();
	particleObjectManager_->Update();*/
	particleMan->Update();
	particleSmoke->Update();
	particleGone->Update();
	particleBlood->Update();

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
	// 3D�I�u�W�F�N�g�`��O����
	//Object3d::PreDraw();

	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDrow();
	// �X�v���C�g�`��
	//title->Draw();
	//hp->Draw();


#pragma region 3D�`��
	DirectXcommon* dxCommon = DirectXcommon::GetInstance();
	// 3D�I�u�W�F�N�g�̕`��
	// �v���C���[�`��
	if (playerFlag == true) {
		playerFbxObject->Draw(dxCommon->GetCmdList());
	}
	
	// �e�`��
	for (int i = 0; i < 5; i++) {
		if (yetiFlag == true) {
			// �C�G�e�B�`��
			yetiFbxObject->Draw(dxCommon->GetCmdList());
			bulletFbxObject[i]->Draw(dxCommon->GetCmdList());
		}
	}
	universeFbxObject->Draw(dxCommon->GetCmdList());

	// �p�[�e�B�N���I�u�W�F�N�g�̕`��
	//object_particle->Draw();
	particleMan->Draw(dxCommon->GetCmdList());
	particleSmoke->Draw(dxCommon->GetCmdList());
	particleGone->Draw(dxCommon->GetCmdList());
	particleBlood->Draw(dxCommon->GetCmdList());

	// 3D�I�u�W�F�N�g�`��㏈��
	//Object3d::PostDraw();
	//ParticleManager::PostDraw();
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDrow();

	/*if (endFlag == true) {
		end->Draw();
	}*/
	if (stopFlag == true) {
		hp2->Draw();
	}
	if (stopFlag2 == true) {
		hp3->Draw();
	}
}
