#pragma once

#include "Framework.h"

//#include "Input.h"
//#include "WinApp.h"
//#include "DirectXcommon.h"
//#include "Object3d.h"
//#include "Model.h"
//#include "Sprite.h"
//#include "Audio.h"
//#include "DebugText.h"

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
    /// 
    /// </summary>
    /// <returns></returns>
    //bool IsEndRequst() { return endRequst_; }

private:
   /* bool endRequst_ = false;

    WinApp* winApp = nullptr;
    DirectXcommon* dxCommon = nullptr;
    Input* input = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;*/

    std::vector<Sprite*> sprites;

    Model* model_1 = nullptr;
    Model* model_2 = nullptr;
    Model* model_3 = nullptr;

    Object3d* object3d_1 = nullptr;
    Object3d* object3d_2 = nullptr;
    Object3d* object3d_3 = nullptr;

   /* Audio::SoundData soundData1;*/
};

