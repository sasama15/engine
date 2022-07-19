#pragma once
#include <Windows.h>
#include <wrl.h>
#include <DirectXMath.h>

#include "PipelineSet.h"

/// <summary>
/// �X�v���C�g���ʕ���
/// </summary>
class SpriteCommon
{
public:
    static SpriteCommon* GetInstance();

	// �e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

private:
    // �p�C�v���C���Z�b�g
    PipelineSet pipelineSet_;
    // �ˉe�s��
    DirectX::XMMATRIX matProjection_{};
    // �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap_;
    // �e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̔z��
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff_[spriteSRVCount];
    // �f�o�C�X(�؂�Ă���)
    ID3D12Device* device_ = nullptr;
    // �R�}���h���X�g(�؂�Ă���)
    ID3D12GraphicsCommandList* commandList_ = nullptr;

public: // �����o�֐�
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="device">�f�o�C�X</param>
	/// <param name="commandList">�R�}���h���X�g</param>
	/// <param name="window_width">�E�B���h�E����</param>
    /// <param name="window_height">�E�B���h�E�c��</param>
    void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, int window_width, int window_height);

    /// <summary>
    /// �`��O����
    /// </summary>
    void PreDrow();

    /// <summary>
    /// �e�N�X�`���ǂݍ���
    /// </summary>
    void LoadTexture(UINT texnumber, const wchar_t* filename);

    /// <summary>
    /// ���[�g�f�X�N���v�^�̐ݒ�
    /// </summary>
    /// <param name="rootParameterIndex">���[�g�p�����[�^�\�ԍ�</param>
    /// <param name="texnumber">�e�N�X�`���ԍ�</param>
    void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, UINT texnumber);

    /// <summary>
    /// �e�N�X�`���擾
    /// </summary>
    /// <param name="texNumber">�e�N�X�`���ԍ�</param>
    /// <returns>�e�N�X�`�����\�[�X</returns>
    ID3D12Resource* GetTexBuff(int texNumber);

    ID3D12Device* GetDevice() { return device_; }
    const DirectX::XMMATRIX& GetMatProjection() { return matProjection_; }
    ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }


private:
    /// <summary>
    /// �X�v���C�g�p�p�C�v���C������
    /// </summary>
    void CreateGraphicsPipeline();
};

