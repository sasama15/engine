#pragma once

#include "Framework.h"

#include <vector>

/// <summary>
/// �Q�[���ŗL�̃N���X(�����͍��Q�[���̖��O�����A������)
/// </summary>
class SampleGame : public Framework
{
public:
    /// <summary>
    /// ������
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// �I��
    /// </summary>
    void Finalize() override;

    /// <summary>
    /// ���t���[������
    /// </summary>
    void Update() override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// HP�o�[�Ȃǂ̕\����
    /// </summary>
    //void DrawUI();

private:
};

