#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"

#include <memory>

class GamePlayScene2 : public BaseScene
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
    /// �����蔻��
    /// </summary>
    /// <param name="playerCircle">�v���C���[�͈�</param>
    /// <param name="enemyCircle">�G�l�~�[�͈�</param>
    /// <param name="playerR">�v���C���[���a</param>
    /// <param name="enemyR">�G�l�~�[���a</param>
    /// <returns></returns>
    bool OnCollisionCircle(FbxObject3d* playerCircle, FbxObject3d* enemyCircle, float playerR, float enemyR);

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;

private:
    // �eUI
    Sprite* title = nullptr;
    Sprite* hp = nullptr;
    Sprite* hp2 = nullptr;
    Sprite* hp3 = nullptr;
    Sprite* end = nullptr;

    // BGM
    Audio::SoundData soundData1;

    // �v���C���[
    FbxModel* playerFbxModel = nullptr;
    // �C�G�e�B
    FbxModel* yetiFbxModel = nullptr;

    // �v���C���[
    FbxObject3d* playerFbxObject = nullptr;
    // �C�G�e�B
    FbxObject3d* yetiFbxObject = nullptr;

    // �v���C���[�|�W�V����
    XMFLOAT3 PlayerPos;
    // �C�G�e�B�|�W�V����
    XMFLOAT3 YetiPos;

    // �v���C���[�t���O
    bool playerFlag = false;
    // �C�G�e�B�t���O
    bool yetiFlag = false;
    // �G���h�t���O
    bool endFlag = false;

    DebugCamera* camera;
};

