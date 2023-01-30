#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "FbxObject3d.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
//#include "../LigthGroup.h"

#include <memory>

/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
class GamePlayScene : public BaseScene
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
    Sprite* sprite = nullptr;
    Sprite* end = nullptr;
    Sprite* wasd = nullptr;
    //std::unique_ptr<Sprite> sprite;

   /* Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;*/

    std::unique_ptr<Model> model_1;
    std::unique_ptr<Model> model_2;
    std::unique_ptr<Model> model_3;
    std::unique_ptr<Model> model_universe;

    /*Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;*/

    //���j�[�N�|�C���^(������̂���)
    // nullptr�͏���ɓ��邽�ߕK�v�Ȃ�
    /*std::unique_ptr<Object3d> object3d_1;
    std::unique_ptr<Object3d> object3d_2;
    std::unique_ptr<Object3d> object3d_3;*/

    // shared_ptr�g���ꍇ
    std::shared_ptr<Object3d> object3d_1;
    std::shared_ptr<Object3d> object3d_2;
    std::shared_ptr<Object3d> object3d_3;
    std::shared_ptr<Object3d> object3d_universe;

    // weak_ptr�g���ꍇ
    /*std::weak_ptr<Object3d> object3d_1;
    std::weak_ptr<Object3d> object3d_2;
    std::weak_ptr<Object3d> object3d_3;*/

    // shared_ptr(���L����Ƃ��Ɏg��)
    // weak_ptr(�ǔ��e�Ɏg��)

    Audio::SoundData soundData1;

    std::unique_ptr<ObjectManager> objectManager_;

    FbxModel* nucleusFbxModel = nullptr;
    FbxModel* playerFbxModel = nullptr;
    FbxModel* enemyFbxModel = nullptr;

    FbxObject3d* playerFbxObject = nullptr;

    FbxObject3d* nucleusFbxObject[3];

    /*FbxObject3d* nucleusFbxObject = nullptr;
    FbxObject3d* nucleusFbxObject2 = nullptr;
    FbxObject3d* nucleusFbxObject3 = nullptr;*/

    FbxObject3d* enemyFbxObject[3];

   /* FbxObject3d* enemyFbxObject = nullptr;
    FbxObject3d* enemyFbxObject2 = nullptr;
    FbxObject3d* enemyFbxObject3 = nullptr;*/

    DebugCamera* camera;


    XMFLOAT3 PlayerPos;

    XMFLOAT3 NucleusPos;
    XMFLOAT3 NucleusPos2;
    XMFLOAT3 NucleusPos3;

    XMFLOAT3 EnemyPos;
    XMFLOAT3 EnemyPos2;
    XMFLOAT3 EnemyPos3;

    XMFLOAT3 OldEnemyPos;
    XMFLOAT3 OldEnemyPos2;
    XMFLOAT3 OldEnemyPos3;

    // �j�����G�̍ő吔
    const int nucleusMax = 3;
    // �G�̍ő吔
    const int enemyMax = 3;


    // �j�����G
    bool NucleusJump;
    float NucleusGravity;
    /*float Angle;
    float Ax;
    float Az;*/

    // �j�����G2
    bool NucleusJump2;
    float NucleusGravity2;

    // �j�����G3
    bool NucleusJump3;
    float NucleusGravity3;

    // �G2
    bool EnemyJump;
    float EnemyGravity;
    /*float Angle2;
    float Ax2;
    float Az2;*/

    // �G3
    bool EnemyJump2;
    float EnemyGravity2;
    /*float Angle3;
    float Ax3;
    float Az3;*/

    // �G4
    bool EnemyJump3;
    float EnemyGravity3;

    // �����蔻��
    //Sphere spherePlayer;
    //Sphere sphereEnemy;
    bool playerFlag = false;

    bool nucleusFlag;
    bool nucleusFlag2;
    bool nucleusFlag3;

    bool enemyFlag;
    bool enemyFlag2;
    bool enemyFlag3;

    bool endFlag;

    // �_����
    float pointLightPos[3] = { 0, 0, 0 };
    float pointLightColor[3] = { 1, 1, 1 };
    float pointLightAtten[3] = { 0.3f, 0.1f, 0.1f };
};

