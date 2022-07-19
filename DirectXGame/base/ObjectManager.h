#pragma once

#include "Object3d.h"
#include <memory>

// �I�u�W�F�N�g�}�l�[�W��
class ObjectManager
{
public:
	/// <summary>
	/// 3D�I�u�W�F�N�g�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="object">�I�u�W�F�N�g</param>
	//void AddObject(std::shared_ptr<Object3d> object);
	std::weak_ptr<Object3d> AddObject(std::shared_ptr<Object3d> object);
private:
	// �I�u�W�F�N�g���X�g
	std::vector<std::shared_ptr<Object3d>> objects_;
};

