#include "SampleGame.h"
#include "SceneFactory.h"

void SampleGame::Initialize()
{
    // ���N���X�̏���������
    Framework::Initialize();

#pragma region WindowsAPI������
    MSG msg{};  // ���b�Z�[�W

#pragma region DirectX����������
    // DirectX�����������@��������
#ifdef _DEBUG
    //�f�o�b�O���C���[���I����
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }
#endif

    HRESULT result;

    // DirectX�����������@�����܂�
#pragma endregion DirectX����������

#pragma region �V�[������������
    // �V�[���}�l�[�W���[�𐶐����A�}�l�[�W���[�ɃZ�b�g
    sceneFactory_ = new SceneFactory();
    SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

    // �V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
    SceneManager::GetInstance()->ChangeScene("TITLE");

#pragma endregion �V�[������������
}

void SampleGame::Finalize()
{
   // ���N���X�̏I������
    Framework::Finalize();
}

void SampleGame::Update()
{
    // ���N���X�̍X�V����
    Framework::Update();
}

void SampleGame::Draw()
{
#pragma region �O���t�B�b�N�X�R�}���h

    // ���N���X�̕`��
    Framework::Draw();
}
