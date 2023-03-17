#pragma once
#include "ParticleManager.h"
#include <memory>

class ParticleObjectManager
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
	std::weak_ptr<ParticleManager> AddObject(std::shared_ptr<ParticleManager> object);
private:
	// �I�u�W�F�N�g���X�g
	std::vector<std::shared_ptr<ParticleManager>> objects_;
};

