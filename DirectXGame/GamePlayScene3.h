#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Audio.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "ParticleManager.h"
#include "Easing.h"

#include <memory>
#include <math.h>

class GamePlayScene3 : public BaseScene
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


};

