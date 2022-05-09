#pragma once

#include "BaseScene.h"

/// <summary>
/// �V�[���Ǘ�
/// </summary>
class SceneManager
{
public:
	// ���̃N���X�S�̂Ŏg���@�\
	static SceneManager* GetInstance();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	// ���V�[���\��
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }

private:
	// ���̃V�[��
	BaseScene* scene_ = nullptr;
	// ���̃V�[��
	BaseScene* nextScene_ = nullptr;

	//�R���X�g���N�^�ƃf�X�g���N�^�̉B��
	SceneManager() = default;
	~SceneManager();
	// �R�s�[�C���X�g���N�^�̉B��
	SceneManager(const SceneManager&) = delete;
	// �R�s�[������Z�q�̉B��
	void operator = (const SceneManager&) = delete;
};

