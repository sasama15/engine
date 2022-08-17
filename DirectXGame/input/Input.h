#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800	// DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <Xinput.h>

#include "WinApp.h"

#pragma once
#pragma comment(lib,"xinput.lib")

enum class Button {
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	UP = XINPUT_GAMEPAD_DPAD_UP,
	DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
	LEFTTHUMB = XINPUT_GAMEPAD_LEFT_THUMB,
	RIGHTTHUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
};

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

private:
	XINPUT_STATE state;
	XINPUT_STATE oldstate;
	DWORD dwResult;
	// �X�e�B�b�N�̓��͂��\���{�^���ɕϊ�
	WORD ThumbToPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

public:		// �����o�֐�

	static Input* GetInstance();

	// ������
	void Initialize(WinApp* winApp);
	// �X�V
	void Update();
	// �R���g���[���[������
	void ControllerInitialize(DWORD controllerNum);
	// �R���g���[���[�X�V
	void ControllerUpdate(DWORD controllerNum);

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

	/// <summary>
	/// �R���g���[���[�{�^���̉��������`�F�b�N
	/// </summary>
	/// <param name="button">�{�^��</param>
	/// <returns>������Ă��邩</returns>
	bool PushButton(int button);

	/// <summary>
	/// �R���g���[���[�{�^���̉��������`�F�b�N
	/// </summary>
	/// <returns>���g���K�[��</returns>
	bool PushLt();

	/// <summary>
	/// �R���g���[���[�{�^���̉��������`�F�b�N
	/// </summary>
	/// <returns>�E�g���K�[��</returns>
	bool PushRt();

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̉��������`�F�b�N
	/// </summary>
	/// <returns>���X�e�B�b�N�オ������Ă��邩</returns>
	bool PushLeftStickUp();

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̉��������`�F�b�N
	/// </summary>
	/// <returns>���X�e�B�b�N����������Ă��邩</returns>
	bool PushLeftStickDown();

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̉��������`�F�b�N
	/// </summary>
	/// <returns>���X�e�B�b�N����������Ă��邩</returns>
	bool PushLeftStickLeft();

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̉��������`�F�b�N
	/// </summary>
	/// <returns>���X�e�B�b�N�E��������Ă��邩</returns>
	bool PushLeftStickRight();

	/// <summary>
	/// �R���g���[���[�{�^���̉��������`�F�b�N
	/// </summary>
	/// <param name="button">�{�^��</param>
	/// <returns>�g���K�[�{�^����</returns>
	bool TriggerButton(int button);
};

