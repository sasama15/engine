#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// �f�o�b�O�p�J����
/// </summary>
class DebugCamera :
    public Camera
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="winWidth">��ʕ�</param>
    /// <param name="winHeight">��ʍ���</param>
    /// <param name="input">����</param>
    DebugCamera(int winWidth, int winHeight, Input* input);

    // �X�V
    void Update() override;

    void SetDistance(float distance) { this->distance = distance; viewDirty = true; }

private:
    // ���̓N���X�̃|�C���^
    Input* input;
    // �J���������_�܂ł̋���
    float distance = 25;
    // �X�P�[�����O
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    // ��]�s��
    DirectX::XMMATRIX matRot = DirectX::XMMatrixIdentity();
};

