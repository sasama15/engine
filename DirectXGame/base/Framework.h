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
#include "AbstractSceneFactory.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "PostEffect.h"
#include "MultiRenderTarget.h"
#include "MultiTexture.h"
#include "ParticleManager.h"

#include <memory>

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

    const DirectXcommon* GetCommon() { return dxCommon; }
//private:
protected:
    bool endRequst_ = false;

    WinApp* winApp = nullptr;
    DirectXcommon* dxCommon = nullptr;
    Input* input = nullptr;
    DebugText* debugText = nullptr;
    SpriteCommon* spriteCommon = nullptr;
    Audio::SoundData soundData1;
    PostEffect* postEffect = nullptr;
    MultiRenderTarget* postEffect2 = nullptr;
    MultiTexture* postEffect3 = nullptr;
    // �p�[�e�B�N��
    ParticleManager* particleMan = nullptr;

    // ���L��(�Ǘ���)
    //AbstractSceneFactory* sceneFactory_ = nullptr;
    std::unique_ptr<AbstractSceneFactory> sceneFactory_;
};

