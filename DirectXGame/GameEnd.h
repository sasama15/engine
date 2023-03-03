#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"

/// <summary>
/// �Q�[���N���A�V�[��
/// </summary>
class GameEnd : public BaseScene
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

private:
    Sprite* sprite1 = nullptr;

    //Audio::SoundData soundData1;
};


