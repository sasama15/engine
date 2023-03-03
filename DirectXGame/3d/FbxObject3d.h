#pragma once

#include "FbxModel.h"
#include "Camera.h"
#include "FbxLoader.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FbxObject3d
{
protected:	// エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// 静的メンバ関数
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }
	void SetModel(FbxModel* fbxModel) { this->fbxModel = fbxModel; }
	const XMFLOAT3& GetPosition() { return position; }
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	//アニメーションを止める
	void SetIsPlay(const bool& isPlay) { this->isPlay = isPlay; }
	//アニメーションが終わったか
	const bool& animationIsEnd() {
		//1回きりの再生かつ再生が終わったら
		if ((isLoop == false && currentTime > endTime) || currentTime == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:	// 定数
	// ボーンの最大数
	static const int MAX_BONES = 32;

private:	// 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// カメラ
	static Camera* camera;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr <ID3D12PipelineState> pipelinestate;
	// 定数バッファ(スキン)
	ComPtr <ID3D12Resource> constBuffSkin;
	// 1フレームの時間
	FbxTime frameTime;
	// アニメーション開始時間
	FbxTime startTime;
	// アニメーション終了時間
	FbxTime endTime;
	// 現在時間(アニメーション)
	FbxTime currentTime;
	// アニメーション再生中
	bool isPlay = false;
	// アニメーションループ
	bool isLoop = true;

public:	// サブクラス
	// 定数バッファ用データ構造体(座標変換行列用)
	struct ConstBufferDataTransform {
		XMMATRIX viewproj;	// ビュープロジェクション行列
		XMMATRIX world;		// ワールド行列
		XMFLOAT3 cameraPos;	// カメラ座標(ワールド座標)
	};

	// 定数バッファ用構造体(スキニング)
	struct ConstBufferDataSkin {
		XMMATRIX bones[MAX_BONES];
	};

public:	// メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation(const int& AnimationNum = 0,const bool &isLoop = true);

	/// <summary>
	/// サイズセット
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

protected:	// メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	// ローカルスケール
	XMFLOAT3 scale = { 1, 1, 1 };
	// x, y, z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0, 0, 0 };
	// ローカル座標
	XMFLOAT3 position = { 0, 0, 0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// モデル
	FbxModel* fbxModel = nullptr;
};

