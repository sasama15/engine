#pragma once

#include "FbxModel.h"
#include "Camera.h"
#include "FbxLoader.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FbxObject3d
{
protected:	// �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// �ÓI�����o�֐�
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }
	void SetModel(FbxModel* fbxModel) { this->fbxModel = fbxModel; }
	const XMFLOAT3& GetPosition() { return position; }

public:	// �萔
	// �{�[���̍ő吔
	static const int MAX_BONES = 32;

private:	// �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �J����
	static Camera* camera;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr <ID3D12PipelineState> pipelinestate;
	// �萔�o�b�t�@(�X�L��)
	ComPtr <ID3D12Resource> constBuffSkin;

public:	// �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransform {
		XMMATRIX viewproj;	// �r���[�v���W�F�N�V�����s��
		XMMATRIX world;		// ���[���h�s��
		XMFLOAT3 cameraPos;	// �J�������W(���[���h���W)
	};

	// �萔�o�b�t�@�p�\����(�X�L�j���O)
	struct ConstBufferDataSkin {
		XMMATRIX bones[MAX_BONES];
	};

public:	// �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

protected:	// �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1, 1, 1 };
	// x, y, z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0, 0, 0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0, 0, 0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// ���f��
	FbxModel* fbxModel = nullptr;
};

