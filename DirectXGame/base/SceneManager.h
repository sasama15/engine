#pragma once

#include "BaseScene.h"
#include "AbstractSceneFactory.h"

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

	/// <summary>
	/// ���V�[���\��
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { sceneFactory_ = sceneFactory; }

private:
	// ���̃V�[��
	BaseScene* scene_ = nullptr;
	// ���̃V�[��
	BaseScene* nextScene_ = nullptr;

	// �V�[���t�@�N�g��
	AbstractSceneFactory* sceneFactory_ = nullptr;

	//�R���X�g���N�^�ƃf�X�g���N�^�̉B��
	SceneManager() = default;
	~SceneManager();
	// �R�s�[�C���X�g���N�^�̉B��
	SceneManager(const SceneManager&) = delete;
	// �R�s�[������Z�q�̉B��
	void operator = (const SceneManager&) = delete;
};

