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
#include <math.h>

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
    // �e
    FbxModel* bulletFbxModel = nullptr;

    // �v���C���[
    FbxObject3d* playerFbxObject = nullptr;
    // �C�G�e�B
    FbxObject3d* yetiFbxObject = nullptr;
    // �e
    //FbxObject3d* bulletFbxObject = nullptr;

    // �e
    FbxObject3d* bulletFbxObject[5];

    // �v���C���[�|�W�V����
    XMFLOAT3 PlayerPos;
    // �C�G�e�B�|�W�V����
    XMFLOAT3 YetiPos;
    // �e
    //XMFLOAT3 BulletPos;
    // �v���C���[�|�W�V����(�v���C���[�������ꏊ)
    XMFLOAT3 oldPlayerPos[5];
    XMFLOAT3 oldPlayerPos2;
    // �e
    XMFLOAT3 BulletPos[5];

    // �e�̍ő吔
    const int iceMax = 5;

    // �v���C���[�t���O
    bool playerFlag = false;
    // �C�G�e�B�t���O
    bool yetiFlag = false;
    // �G���h�t���O
    bool endFlag = false;
    // �e�t���O
    /*bool bulletFlag = false;
    bool bulletFlag2 = false;
    bool bulletFlag3 = false;
    bool bulletFlag4 = false;
    bool bulletFlag5 = false;*/

    bool bulletFlag[5];
    // �e����
    bool shootFlag = false;
    /*bool shootFlag2 = false;
    bool shootFlag3 = false;
    bool shootFlag4 = false;
    bool shootFlag5 = false;*/


    // �ˌ�
    //bool onrushFlag = false;
    //�G�]����
    bool rollingFlag = false;
    // �e���W�����v
    bool BulletJump;
    bool BulletJump2;
    bool BulletJump3;
    bool BulletJump4;
    bool BulletJump5;

    int bulletSpeed;
    int iceBulletTimer;

    float BulletGravity[5];
    float BulletJampPower;

    DebugCamera* camera;
};

