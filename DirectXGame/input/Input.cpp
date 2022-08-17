#include "Input.h"
//#include <wrl.h>

//using namespace Microsoft::WRL;

//#define DIRECTINPUT_VERSION	0x0800	// DirectInputのバージョン指定
//#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

WORD Input::ThumbToPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;	// 左スティックから十字ボタン変換用

	if (sThumbX <= -sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;	// 左スティックを左に倒すのを十字ボタン左に
	}
	else if (sThumbX >= sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;	// 左スティックを右に倒すのを十字ボタン右に
	}

	if (sThumbY >= sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;		// 左スティックを上に倒すのを十字ボタン上に
	}
	else if (sThumbY <= -sDeadZone) {
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;	// 左スティックを下に倒すのを十字ボタン下に
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

	// 借りてきたwinAppのインスタンスを記録
	this->winApp = winApp;

	// DirectInputのインスタンス生成
	//ComPtr<IDirectInput8> dinput = nullptr;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	// キーボードデバイス生成
	//ComPtr<IDirectInputDevice8> devkeyboard;
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	
	// 入力データ形成のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	
	// 排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	// マウスデバイスの生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

	// マウス入力データ形成のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2);	// 標準形式

	// マウス排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update(){
	HRESULT result;

	// 前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));

	// キーボード情報の取得開始
	result = devkeyboard->Acquire();

	// 全キーの入力情報を取得する
	//BYTE key[256] = {};
	result = devkeyboard->GetDeviceState(sizeof(key), key);

	// マウス
	result = devMouse->Acquire();	// マウス動作開始

	// マウスの入力
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

void Input::ControllerInitialize(DWORD controllerNum)
{
	// 構造体のクリア
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(controllerNum, &state);

	// 接続成功
	if (dwResult == ERROR_SUCCESS) {
		return;
	}
	// 接続失敗
	else {
		int a = 0;
		return;
	}
}

void Input::ControllerUpdate(DWORD controllerNum)
{
	// 構造体のクリア
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

	// 左スティックからの入力を方向パッドに変換
	state.Gamepad.wButtons |= ThumbToPad(
		state.Gamepad.sThumbLX,
		state.Gamepad.sThumbLY,
		XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

bool Input::PushKey(const BYTE& keyNumber){
	// 指定キーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	// そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(const BYTE& keyNumber)
{
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}
	// そうでなければfalseを返す
	return false;
}

bool Input::isMouseLeft()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[0]) {
		return true;
	}
	// 押していない
	return false;
}

bool Input::isMouseMiddle()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}
	// 押していない
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
