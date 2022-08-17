#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800	// DirectInputのバージョン指定
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

// 入力
class Input{
public:
	// namespace省略
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
	// スティックの入力を十字ボタンに変換
	WORD ThumbToPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

public:		// メンバ関数

	static Input* GetInstance();

	// 初期化
	void Initialize(WinApp* winApp);
	// 更新
	void Update();
	// コントローラー初期化
	void ControllerInitialize(DWORD controllerNum);
	// コントローラー更新
	void ControllerUpdate(DWORD controllerNum);

private:	// メンバ変数
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> devkeyboard;
	// マウス

	// 前回の全キーの状態
	BYTE keyPre[256] = {};

	// 全キーの状態
	BYTE key[256] = {};

	// DirectInputのインスタンス
	ComPtr<IDirectInput8> dinput;

	// マウス
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};

	// WindowsAPI
	WinApp* winApp = nullptr;

public:
	/// <summary>
	/// キーの押し下をチェック
	/// </summary>
	/// <param name ="KeyNumber">キー番号(DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(const BYTE& keyNumber);

	/// <summary>
	/// キーの押し下をチェック
	/// </summary>
	/// <param name ="KeyNumber">キー番号(DIK_0 等)</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(const BYTE& keyNumber);

	/// <summary>
	/// キーの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool isMouseLeft();

	/// <summary>
	/// キーの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool isMouseMiddle();

	/// <summary>
	/// マウス移動量を取得
	/// </summary>
	/// <returns>マウス移動量</returns>
	MouseMove GetMouseMove();

	/// <summary>
	/// コントローラーボタンの押し下をチェック
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか</returns>
	bool PushButton(int button);

	/// <summary>
	/// コントローラーボタンの押し下をチェック
	/// </summary>
	/// <returns>左トリガーか</returns>
	bool PushLt();

	/// <summary>
	/// コントローラーボタンの押し下をチェック
	/// </summary>
	/// <returns>右トリガーか</returns>
	bool PushRt();

	/// <summary>
	/// コントローラースティックの押し下をチェック
	/// </summary>
	/// <returns>左スティック上が押されているか</returns>
	bool PushLeftStickUp();

	/// <summary>
	/// コントローラースティックの押し下をチェック
	/// </summary>
	/// <returns>左スティック下が押されているか</returns>
	bool PushLeftStickDown();

	/// <summary>
	/// コントローラースティックの押し下をチェック
	/// </summary>
	/// <returns>左スティック左が押されているか</returns>
	bool PushLeftStickLeft();

	/// <summary>
	/// コントローラースティックの押し下をチェック
	/// </summary>
	/// <returns>左スティック右が押されているか</returns>
	bool PushLeftStickRight();

	/// <summary>
	/// コントローラーボタンの押し下をチェック
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>トリガーボタンか</returns>
	bool TriggerButton(int button);
};

