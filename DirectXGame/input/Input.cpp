#include "Input.h"
//#include <wrl.h>

//using namespace Microsoft::WRL;

//#define DIRECTINPUT_VERSION	0x0800	// DirectInputのバージョン指定
//#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

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
