#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

#include "PointLight.h"
#include "CircleShadow.h"
class LigthGroup
{
private:	// エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// 定数
	// 点光源の数
	static const int PointLightNum = 3;
	// 丸影の数
	static const int CircleShadowNum = 1;

public:	// サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferData {
		// 環境光の色
		XMFLOAT3 ambientColor;
		float pad1;
		// 平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源
		PointLight::ConstBufferData pointLights[PointLightNum];
		// スポットライト用
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		// 丸影用
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};

public:	// メンバ関数(アクセッサ)
	// 点光源
	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index, const XMFLOAT3& lightpos);
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

	// 丸影
	void SetCircleShadowActive(int index, bool active);
	void SetCircleShadowCasterPos(int index, bool active);
	void SetCircleShadowDir(int index, const XMVECTOR& lightdir);
	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight);
	void SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten);
	void SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle);

public:
	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

private:	// メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 環境光の色
	XMFLOAT3 ambientColor = { 1, 1, 1 };
	// 点光源の配列
	PointLight pointLights[PointLightNum];
	// 丸影の配列
	CircleShadow circleSadows[CircleShadowNum];
};

