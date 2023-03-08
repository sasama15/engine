//cbuffer cbuff0 : register(b0)
//{
//	matrix viewProject; // ビュープロジェクション行列
//	matrix viewProjectBillboard; // ビルボード行列
//};
//
//// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
//struct VSOutput
//{
//	float4 pos : POSITION; // 頂点座標
//	float scale : TEXCOORD; // スケール
//};
//
//struct GSOutput
//{
//	float4 svpos : SV_POSITION; // システム用頂点座標
//	float2 uv  :TEXCOORD; // uv値
//};
// 点光源の数
static const int POINTLIGHT_NUM = 3;

struct PointLight {
	float3 lightpos;	// ライト座標
	float3 lightcolor;	// ライトの色(RGB)
	float3 lightatten;	// ライト距離減衰係数
	uint active;
};

cbuffer cbuff0 : register(b0) {
	matrix viewProject;	// ビュープロジェクション行列
	matrix viewProjectBillboard; // ビルボード行列
	matrix world;		// ワールド行列
	float3 cameraPos;	// カメラの座標(ワールド座標)
}

// バーテックスバッファーの入力
struct VSInput {
	float4 pos	  : POSITION;			// 位置
	float3 normal : NORMAL;				// 頂点法線
	float2 uv     :	TEXCOORD;			// テクスチャー座標
	uint4 boneIndices : BONEINDICES;	// ボーンの番号
	float4 boneWeights : BONEWEIGHTS;	// ボーンのスキンウェイト
};

// 頂点シェーダ―からピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput {
	float4 svpos  : SV_POSITION;	// システム用頂点座標
	float3 normal : NORMAL;			// 法線
	float2 uv     : TEXCOORD;		// UV値
};

// ボーンの最大数
static const int MAX_BONES = 32;

cbuffer skinning:register(b3) {	// ボーンのスキニング行列が入る
	matrix matSkinning[MAX_BONES];
};
