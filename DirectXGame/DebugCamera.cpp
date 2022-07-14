#include "DebugCamera.h"
#include <cassert>

using namespace DirectX;

DebugCamera::DebugCamera(int winWidth, int winHeight, Input* input)
	: Camera(winWidth, winHeight)
{
	assert(input);

	this->input = input;
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 1.0f / (float)winWidth;
	scaleY = 1.0f / (float)winHeight;
}

void DebugCamera::Update()
{
	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̍��{�^����������Ă�����J��������]������
	if (input->isMouseLeft()) {
		float dy = mouseMove.IX * scaleY;
		float dx = mouseMove.IY * scaleX;

		angleX = -dx * XM_PI;
		angleY = -dy * XM_PI;
		dirty = true;
	}

	// �}�E�X�̒��{�^����������Ă�����J��������s�ړ�������
	if (input->isMouseMiddle()) {
		float dx = mouseMove.IX / 100.0f;
		float dy = mouseMove.IY / 100.0f;

		XMVECTOR move = { -dx, +dy, 0, 0 };
		move = XMVector3Transform(move, matRot);

		MoveVector(move);
		dirty = true;
	}

	// �z�C�[�����͂ŋ�����ύX
	if (mouseMove.IZ != 0) {
		distance -= mouseMove.IZ / 100.0f;
		distance = max(distance, 1.0f);
		dirty = true;
	}

	if (dirty || viewDirty) {
		// �ǉ���]���̉�]�s��𐶐�
		XMMATRIX matRotNew = XMMatrixIdentity();
		matRotNew *= XMMatrixRotationX(-angleX);
		matRotNew *= XMMatrixRotationY(-angleY);
		// �ݐς̉�]�s�������
		// ����]�s���ݐς��Ă����ƁA�덷�ŃX�P�[�����O��������댯�������
		// �N�H�[�^�j�I�����g�p��������]�܂���
		matRot = matRotNew * matRot;

		// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
		XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };

		// �x�N�g������]
		vTargetEye = XMVector3Transform(vTargetEye, matRot);
		vUp = XMVector3Transform(vUp, matRot);

		//�����_���炸�炵���ʒu�Ɏ��_���W������
		const XMFLOAT3& target = GetTarget();
		SetEye({ target.x + vTargetEye.m128_f32[0], target.y + vTargetEye.m128_f32[1], target.z + vTargetEye.m128_f32[2] });
		SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });
	}
	Camera::Update();
}
