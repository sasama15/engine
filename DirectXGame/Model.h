#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

// 3D���f��
class Model
{
public:	// �C���i�[�N���X
// ���_�f�[�^�\����
	struct VertexPosNormalUv {
		DirectX::XMFLOAT3 pos;		// xyz���W
		DirectX::XMFLOAT3 normal;	// �@���x�N�g��
		DirectX::XMFLOAT2 uv;		// uv���W
	};

	// �}�e���A��
	struct Material {
		std::string name;			// �}�e���A����
		DirectX::XMFLOAT3 ambient;	// �A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse;	// �f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular;	// �X�y�L�����[�e���x
		float alpha;
		std::string textureFilename;	// �e�N�X�`���t�@�C����
		// �R���X�g���N�^
		Material() {
			ambient = { 0.3f, 0.3f, 0.3f };
			diffuse = { 0.0f, 0.0f, 0.0f };
			specular = { 0.0f, 0.0f, 0.0f };
			alpha = 1.0f;
		}
	};

	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1 {
		DirectX::XMFLOAT3 ambient;	// �A���r�G���g�W��
		float pad1;					// �p�f�B���O
		DirectX::XMFLOAT3 diffuse;	// �f�B�t���[�Y�W��
		float pad2;					// �p�f�B���O
		DirectX::XMFLOAT3 specular;	// �X�y�L�����[�W��
		float alpha;
	};

public:	// �ÓI�����o�֐�
	// OBJ�t�@�C������3D���f����ǂݍ���
	//static Model* LoadFromOBJ(const std::string& modelname);
	static std::unique_ptr<Model> LoadFromOBJ(const std::string& modelname);

	// setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

private:	// �����o�ϐ�
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;

	// �}�e���A��
	Material material;
	// �f�o�C�X
	static ID3D12Device* device;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �萔�o�b�t�@(�}�e���A��)
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;

private:	// ����J�̃����o�֐�
	// OBJ�t�@�C������3D���f����ǂݍ���(����J)
	void LoadFromOBJInternal(const std::string& modelname);

	// �}�e���A���ǂݍ���
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	// �e�N�X�`���ǂݍ���
	bool LoadTexture(const std::string & directoryPath, const std::string& filename);

	// �f�X�N���v�^�q�[�v�̏�����
	bool InitializeDescriptorHeap();

	// �e��o�b�t�@����
	void CreateBuffers();

public:	// �����o�֐�
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	/// <param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);
};

