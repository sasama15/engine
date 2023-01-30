#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include <math.h>

#pragma once
/// <summary>
/// �F��
/// </summary>
class Universe
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// ���[���h�ϊ��f�[�^
	//WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;
};

