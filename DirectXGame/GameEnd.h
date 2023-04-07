#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "Easing.h"

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
    Sprite* blackIn = nullptr;

    // black�A�E�g������
    bool blackInFlag = false;

    // �t�F�C�h�C���p
    double fadeInSize;
    double fadeInTime;

    //Audio::SoundData soundData1;
};


