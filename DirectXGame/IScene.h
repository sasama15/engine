#pragma once

/// <summary>
/// �V�[���C���^�[�t�F�C�X
/// </summary>
class IScene
{
public:

    /// <summary>
    /// ������
    /// </summary>
    virtual void Initialize() = 0;  // virtual��0�����邱�Ƃɂ���ď������z�֐��ɂȂ�

    /// <summary>
    /// �I��
    /// </summary>
    virtual void Finalize() = 0;

    /// <summary>
    /// ���t���[������
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() = 0;
};

