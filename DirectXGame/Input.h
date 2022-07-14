#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800	// DirectInputのバージョン指定
#include <dinput.h>

#include "WinApp.h"

#pragma once

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

public:		// メンバ関数

	static Input* GetInstance();

	// 初期化
	void Initialize(WinApp* winApp);
	// 更新
	void Update();

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
};

