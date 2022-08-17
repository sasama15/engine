#include "Input.h"
//#include <wrl.h>

//using namespace Microsoft::WRL;

//#define DIRECTINPUT_VERSION	0x0800	// DirectInput�̃o�[�W�����w��
//#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

WORD Input::ThumbToPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;	// ���X�e�B�b�N����\���{�^���ϊ��p

	if (sThumbX <= -sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;	// ���X�e�B�b�N�����ɓ|���̂��\���{�^������
	}
	else if (sThumbX >= sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;	// ���X�e�B�b�N���E�ɓ|���̂��\���{�^���E��
	}

	if (sThumbY >= sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;		// ���X�e�B�b�N����ɓ|���̂��\���{�^�����
	}
	else if (sThumbY <= -sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;	// ���X�e�B�b�N�����ɓ|���̂��\���{�^������
	}

	return wButtons;
}

Input* Input::GetInstance()
{
	static Input instance;

	return &instance;
}

void Input::Initialize(WinApp* winApp){
	HRESULT result;

	// �؂�Ă���winApp�̃C���X�^���X���L�^
	this->winApp = winApp;

	// DirectInput�̃C���X�^���X����
	//ComPtr<IDirectInput8> dinput = nullptr;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	// �L�[�{�[�h�f�o�C�X����
	//ComPtr<IDirectInputDevice8> devkeyboard;
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	
	// ���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	
	// �r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	// �}�E�X�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

	// �}�E�X���̓f�[�^�`���̃Z�b�g
	result = devMouse->SetDataFormat(&c_dfDIMouse2);	// �W���`��

	// �}�E�X�r�����䃌�x���̃Z�b�g
	result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update(){
	HRESULT result;

	// �O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	// �S�L�[�̓��͏����擾����
	//BYTE key[256] = {};
	result = devkeyboard->GetDeviceState(sizeof(key), key);

	// �}�E�X
	result = devMouse->Acquire();	// �}�E�X����J�n

	// �}�E�X�̓���
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

void Input::ControllerInitialize(DWORD controllerNum)
{
	// �\���̂̃N���A
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(controllerNum, &state);

	// �ڑ�����
	if (dwResult == ERROR_SUCCESS) {
		return;
	}
	// �ڑ����s
	else {
		int a = 0;
		return;
	}
}

void Input::ControllerUpdate(DWORD controllerNum)
{
	// �\���̂̃N���A
	oldstate = state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(controllerNum, &state);

	if ((state.Gamepad.sThumbLX<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY<XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY>-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) {
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	// ���X�e�B�b�N����̓��͂�����p�b�h�ɕϊ�
	state.Gamepad.wButtons |= ThumbToPad(
		state.Gamepad.sThumbLX,
		state.Gamepad.sThumbLY,
		XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

bool Input::PushKey(const BYTE& keyNumber){
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(const BYTE& keyNumber)
{
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::isMouseLeft()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[0]) {
		return true;
	}
	// �����Ă��Ȃ�
	return false;
}

bool Input::isMouseMiddle()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[2]) {
		return true;
	}
	// �����Ă��Ȃ�
	return false;
}

Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.IX = mouseState.lX;
	tmp.IY = mouseState.lY;
	tmp.IZ = mouseState.lZ;
	return tmp;
}

bool Input::PushButton(int button)
{
	if (state.Gamepad.wButtons & button) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushLt()
{
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushRt()
{
	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushLeftStickUp()
{
	if (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushLeftStickDown()
{
	if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushLeftStickLeft()
{
	if (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PushLeftStickRight()
{
	if (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::TriggerButton(int button)
{
	if ((state.Gamepad.wButtons & button) && !(oldstate.Gamepad.wButtons & button)) {
		return true;
	}
	else {
		return false;
	}
}
