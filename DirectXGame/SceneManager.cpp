#include "SceneManager.h"

SceneManager::~SceneManager()
{
	// �Ō�̃V�[���̏I���Ɖ��
	scene_->Finalize();
	delete scene_;
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

		scene_->Initialize();
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}
