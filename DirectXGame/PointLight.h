#pragma once

#include <DirectXMath.h>

/// <summary>
/// �_����
/// </summary>
class PointLight {
private:	// �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		XMFLOAT3 lightpos;
		float pad1;
		XMFLOAT3 lightcolor;
		float pad2;
		XMFLOAT3 lightatten;
		unsigned int active;
	};

public:	// �����o�֐�
	// ���C�g���W(���[���h���W)
	XMFLOAT3 lightpos = { 0, 0, 0 };
	// ���C�g�F
	XMFLOAT3 lightcolor = { 1, 1, 1 };
	// ���C�g���������W��
	XMFLOAT3 lightAtten = { 1.0f, 1.0f, 1.0f };
	// �L���t���O
	bool active = false;
};