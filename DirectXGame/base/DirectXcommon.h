#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"

#pragma once

// DirectX基盤
class DirectXcommon
{
private:
	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	// WindowsAPI 借りてきた
	WinApp* winApp = nullptr;

	// バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	// フェンス値
	UINT64 fenceVal = 0;

public:
	Microsoft::WRL::ComPtr<ID3D12Device> devGeter() { return dev; }

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchainGeter() { return swapchain; }

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdListGeter() { return cmdList; }

	// ↓素直に作ればこれ
	//Microsoft::WRL::ComPtr<ID3D12Device> GetDev() { return dev; }

	// デバイス取得
	ID3D12Device* GetDev() { return dev.Get(); }

	//コマンドリスト取得
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }

private:
	// デバイスの初期化
	void InitializeDevice();
	// コマンド関連初期化
	void InitializeCommand();
	// スワップチェーンの初期化
	void InitializeSwapchain();
	// レンダーターゲットビューの初期化
	void InitializeRenderTargetView();
	// 深度バッファの初期化
	void InitializeDepthBuffer();
	// フェンスの初期化
	void InitializeFence();

public:	// メンバ関数
	// 初期化
	void Initialize(WinApp* winApp);
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

public:
	static DirectXcommon* GetInstance();

	~DirectXcommon();
};

