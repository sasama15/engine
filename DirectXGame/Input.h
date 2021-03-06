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

public:		// メンバ関数

	static Input* GetInstance();

	// 初期化
	void Initialize(WinApp* winApp);
	// 更新
	void Update();

private:	// メンバ変数
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> devkeyboard;

	// 前回の全キーの状態
	BYTE keyPre[256] = {};

	// 全キーの状態
	BYTE key[256] = {};

	// DirectInputのインスタンス
	ComPtr<IDirectInput8> dinput;

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
};

