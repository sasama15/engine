#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXcommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "Audio.h"
#include "DebugText.h"
#include "SceneManager.h"

/// <summary>
/// �t���[�����[�N
/// </summary>
class Framework
{
public:
    /// <summary>
    /// ���s
    /// </summary>
    void Run();

    /// <summary>
   /// ������
   /// </summary>
    virtual void Initialize();

    /// <summary>
    /// �I��
    /// </summary>
    virtual void Finalize();

    /// <summary>
    /// ���t���[������
    /// </summary>
    virtual void Update();

    /// <summary>
    /// �`��
    /// </summary>
    //virtual void Draw() = 0;
    virtual void Draw();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    virtual bool IsEndRequst() { return endRequst_; }

//private:
protected:
    bool endRequst_ = false;

    WinApp* winApp = nullptr;
    DirectXcommon* dxCommon = nullptr;
    Input* input = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;
    Audio::SoundData soundData1;
};

