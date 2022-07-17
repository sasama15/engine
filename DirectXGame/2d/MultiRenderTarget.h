#pragma once
#include "../PostSprite.h"
class MultiRenderTarget :
    public PostSprite
{
private:
    // ��ʃN���A�J���[
    static const float clearColor[4];

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MultiRenderTarget();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �V�[���`��O����
    /// </summary>
    /// <param name="comList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �`��R�}���h�̔��s
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPipelineState();

private:
    // �e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff[2];
    // SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    // �[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    // RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    // DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    // �O���t�B�b�N�X�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    // ���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;
};

