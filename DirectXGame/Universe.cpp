#include "Universe.h"

void Universe::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h���W�̏�����
}

void Universe::Update()
{
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0, 0, 0 };

	// �ړ��x�N�g����ύX���鏈��

	// ���W�ړ�(�x�N�g���̉��Z)

	// �s��X�V

	// ���W����ʕ\�����鏈��
}

void Universe::Draw()
{
	// �F���`��
	model_->Draw(worldTransform_, viewProjection_);
}
