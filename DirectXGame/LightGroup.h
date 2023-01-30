#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

#include "PointLight.h"
#include "CircleShadow.h"
class LigthGroup
{
private:	// �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// �萔
	// �_�����̐�
	static const int PointLightNum = 3;
	// �ۉe�̐�
	static const int CircleShadowNum = 1;

public:	// �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		// �����̐F
		XMFLOAT3 ambientColor;
		float pad1;
		// ���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_����
		PointLight::ConstBufferData pointLights[PointLightNum];
		// �X�|�b�g���C�g�p
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		// �ۉe�p
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

public:	// �����o�֐�(�A�N�Z�b�T)
	// �_����
	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index, const XMFLOAT3& lightpos);
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

	// �ۉe
	void SetCircleShadowActive(int index, bool active);
	void SetCircleShadowCasterPos(int index, bool active);
	void SetCircleShadowDir(int index, const XMVECTOR& lightdir);
	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight);
	void SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten);
	void SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle);

public:
	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

private:	// �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// �����̐F
	XMFLOAT3 ambientColor = { 1, 1, 1 };
	// �_�����̔z��
	PointLight pointLights[PointLightNum];
	// �ۉe�̔z��
	CircleShadow circleSadows[CircleShadowNum];
};

