#pragma once

//#include "IScene.h"
#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

/// <summary>
/// �Q�[���v���C�V�[��
/// </summary>
class GamePlayScene : public BaseScene
{
public:
    GamePlayScene(SceneManager* sceneManager);

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
    //std::vector<Sprite*> sprites;
    Sprite* sprite = nullptr;

    Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;

    Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;

    Audio::SoundData soundData1;
};

