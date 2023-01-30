#pragma once

// �O���錾
class SceneManager;

/// <summary>
/// �V�[�����
/// </summary>
class BaseScene
{
public:
    virtual ~BaseScene() = default;

    /// <summary>
    /// ������
    /// </summary>
    virtual void Initialize() = 0;  // virtual��0�����邱�Ƃɂ���ď������z�֐��ɂȂ�

    /// <summary>
    /// �I��
    /// </summary>
    virtual void Finalize() = 0;

    /// <summary>
    /// ���t���[������
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() = 0;

    //virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

//protected:
//    // �V�[���}�l�[�W���[(�؂�Ă���)
//    SceneManager* sceneManager_ = nullptr;
};
