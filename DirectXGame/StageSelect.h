#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

#pragma once

/// <summary>
/// �X�e�[�W�Z���N�g
/// </summary>
class StageSelect : public BaseScene
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

private:
    XMFLOAT2 OperationSize;

    XMFLOAT2 SelectSize;
    XMFLOAT2 SelectSize2;
    XMFLOAT2 SelectSize3;

    XMFLOAT2 ClearSize;
    XMFLOAT2 ClearSize2;
    XMFLOAT2 ClearSize3;

    XMFLOAT3 FramePos;
    XMFLOAT3 OperationPos;
    XMFLOAT3 Select1Pos;
    XMFLOAT3 Select2Pos;
    XMFLOAT3 Select3Pos;

    Sprite* stageSelectSprite = nullptr;
    Sprite* miniOperationSprite = nullptr;
    Sprite* selectSprite1 = nullptr;
    Sprite* selectSprite2 = nullptr;
    Sprite* selectSprite3 = nullptr;
    Sprite* clearSprite1 = nullptr;
    Sprite* clearSprite2 = nullptr;
    Sprite* clearSprite3 = nullptr;
    Sprite* frameSprite = nullptr;

    bool OperationFlag = false;
    bool select1Flag = false;
    bool select2Flag = false;
    bool select3Flag = false;
    bool clear1Flag = false;
    bool clear2Flag = false;
    bool clear3Flag = false;

    //Audio::SoundData soundData1;
};

