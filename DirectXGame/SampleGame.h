#pragma once

#include "Framework.h"

//#include "IScene.h"

//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXcommon.h"
//#include "Object3d.h"
//#include "Model.h"
//#include "Sprite.h"
//#include "Audio.h"
//#include "DebugText.h"

#include <vector>

//class GamePlayScene;
//class TitleScene;

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
    // �V�[��
    //GamePlayScene* scene_ = nullptr;
    //TitleScene* scene_ = nullptr;
    //IScene* scene_ = nullptr;
};

