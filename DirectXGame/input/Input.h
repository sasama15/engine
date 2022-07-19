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

	struct MouseMove {
		LONG IX;
		LONG IY;
		LONG IZ;
	};

public:		// �����o�֐�

	static Input* GetInstance();

	// ������
	void Initialize(WinApp* winApp);
	// �X�V
	void Update();

private:	// �����o�ϐ�
	// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;
	// �}�E�X

	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};

	// �S�L�[�̏��
	BYTE key[256] = {};

	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dinput;

	// �}�E�X
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};

	// WindowsAPI
	WinApp* winApp = nullptr;

public:
	/// <summary>
	/// �L�[�̉��������`�F�b�N
	/// </summary>
	/// <param name ="KeyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(const BYTE& keyNumber);

	/// <summary>
	/// �L�[�̉��������`�F�b�N
	/// </summary>
	/// <param name ="KeyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerKey(const BYTE& keyNumber);

	/// <summary>
	/// �L�[�̍��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool isMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool isMouseMiddle();

	/// <summary>
	/// �}�E�X�ړ��ʂ��擾
	/// </summary>
	/// <returns>�}�E�X�ړ���</returns>
	MouseMove GetMouseMove();
};

