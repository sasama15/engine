#include "SceneManager.h"

SceneManager::~SceneManager()
{
	// �Ō�̃V�[���̏I���Ɖ��
	scene_->Finalize();
	delete scene_;
}

SceneManager* SceneManager::GetInstance()
{
	// ���߂ČĂ΂ꂽ�������C���X�^���X�����������
	static SceneManager instance;

	// 2��ڈȍ~�͈ȉ��̂ݒʂ�
	return &instance;
}

void SceneManager::Update()
{
	// �V�[���؂�ւ�������Ȃ�
	if (nextScene_) {
		// ���V�[���̏I��
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}

		// �V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		//// �V�[���}�l�[�W���[���Z�b�g
		//scene_->SetSceneManager(this);

		// �V�V�[���̏�����
		scene_->Initialize();
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}
