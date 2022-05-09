#include "SampleGame.h"
#include "GamePlayScene.h"
#include "TitleScene.h"

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

#pragma region �`�揉��������

    BaseScene* scene = new TitleScene();
    // �V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
    SceneManager::GetInstance()->SetNextScene(scene);

#pragma endregion �`�揉��������
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
