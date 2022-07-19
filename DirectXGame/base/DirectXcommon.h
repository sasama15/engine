#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"

#pragma once

// DirectX���
class DirectXcommon
{
private:
	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	// DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	// WindowsAPI �؂�Ă���
	WinApp* winApp = nullptr;

	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	// �t�F���X�l
	UINT64 fenceVal = 0;

public:
	Microsoft::WRL::ComPtr<ID3D12Device> devGeter() { return dev; }

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchainGeter() { return swapchain; }

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdListGeter() { return cmdList; }

	// ���f���ɍ��΂���
	//Microsoft::WRL::ComPtr<ID3D12Device> GetDev() { return dev; }

	// �f�o�C�X�擾
	ID3D12Device* GetDev() { return dev.Get(); }

	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }

private:
	// �f�o�C�X�̏�����
	void InitializeDevice();
	// �R�}���h�֘A������
	void InitializeCommand();
	// �X���b�v�`�F�[���̏�����
	void InitializeSwapchain();
	// �����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();
	// �[�x�o�b�t�@�̏�����
	void InitializeDepthBuffer();
	// �t�F���X�̏�����
	void InitializeFence();

public:	// �����o�֐�
	// ������
	void Initialize(WinApp* winApp);
	// �`��O����
	void PreDraw();
	// �`��㏈��
	void PostDraw();

public:
	static DirectXcommon* GetInstance();

	~DirectXcommon();
};

