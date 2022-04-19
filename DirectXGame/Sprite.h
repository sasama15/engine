#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "SpriteCommon.h"

using namespace Microsoft::WRL;
using namespace DirectX;

/// <summary>
/// �X�v���C�g1������\���N���X
/// </summary>
class Sprite
{
public:
    // ���_�f�[�^
    struct VertexPosUv
    {
        XMFLOAT3 pos; // xyz���W
        XMFLOAT2 uv;  // uv���W
    };

    // �萔�o�b�t�@�p�f�[�^�\����
    struct ConstBufferData {
        XMFLOAT4 color; // �F (RGBA)
        XMMATRIX mat;   // �R�c�ϊ��s��
    };

    /// <summary>
    /// �X�v���C�g����
    /// </summary>
    /// <param name="texNumber">�e�N�X�`���ԍ�</param>
    /// <param name="anchorpoint">�A���J�[�|�C���g</param>
    /// <param name="isFlipX">X���]���邩</param>
    /// <param name="isFlipY">Y���]���邩</param>
    /// <returns>�X�v���C�g</returns>
    static Sprite* Create(UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

private:
    //���_�o�b�t�@;
    ComPtr<ID3D12Resource> vertBuff_;
    //���_�o�b�t�@�r���[;
    D3D12_VERTEX_BUFFER_VIEW vbView_{};
    //�萔�o�b�t�@;
    ComPtr<ID3D12Resource> constBuff_;
    // Z�����̉�]�p
    float rotation_ = 0.0f;
    // ���W
    XMFLOAT3 position_ = { 0,0,0 };
    // ���[���h�s��
    XMMATRIX matWorld_;
    // �F(RGBA)
    XMFLOAT4 color_ = { 1, 1, 1, 1 };
    // �e�N�X�`���ԍ�
    UINT texNumber_ = 0;
    // �傫��
    XMFLOAT2 size_ = { 100, 100 };
    // �A���J�[�|�C���g
    XMFLOAT2 anchorpoint_ = { 0.5f, 0.5f };
    // ���E���]
    bool isFlipX_ = false;
    // �㉺���]
    bool isFlipY_ = false;
    // �e�N�X�`��������W
    XMFLOAT2 texLeftTop_ = { 0, 0 };
    // �e�N�X�`���؂�o���T�C�Y
    XMFLOAT2 texSize_ = { 100, 100 };
    // ��\��
    bool isInvisible_ = false;

public:
    /// <summary>
    /// ������
    /// </summary>
    void Initialize(UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

    /// <summary>
    /// ���_�o�b�t�@�̓]��
    /// </summary>
    void TransferVertexBuffer();

    /// <summary>
    /// ���t���[���X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    void SetPosition(const XMFLOAT3& position) { position_ = position; }
    void SetRotation(float rotation) { rotation_ = rotation; }
    void SetSize(const XMFLOAT2& size) { size_ = size; }
    void SetTexLeftTop(const XMFLOAT2& texLeftTop) { texLeftTop_ = texLeftTop; }
    void SetTexSize(const XMFLOAT2& texSize) { texSize_ = texSize; }
};

