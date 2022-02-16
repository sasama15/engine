#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800	// DirectInput�̃o�[�W�����w��
#include <dinput.h>

#include "WinApp.h"

#pragma once

// ����
class Input{
public:
	// namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:		// �����o�֐�
	// ������
	void Initialize(WinApp* winApp);
	// �X�V
	void Update();

private:	// �����o�ϐ�
	// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;

	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};

	// �S�L�[�̏��
	BYTE key[256] = {};

	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dinput;

	// WindowsAPI
	WinApp* winApp = nullptr;

public:
	/// <summary>
	/// �L�[�̉��������`�F�b�N
	/// </summary>
	/// <param name ="KeyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̉��������`�F�b�N
	/// </summary>
	/// <param name ="KeyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);
};

