#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "SpriteCommon.h"

using namespace Microsoft::WRL;
using namespace DirectX;

/// <summary>
/// スプライト1枚分を表すクラス
/// </summary>
class Sprite
{
public:
    // 頂点データ
    struct VertexPosUv
    {
        XMFLOAT3 pos; // xyz座標
        XMFLOAT2 uv;  // uv座標
    };

    // 定数バッファ用データ構造体
    struct ConstBufferData {
        XMFLOAT4 color; // 色 (RGBA)
        XMMATRIX mat;   // ３Ｄ変換行列
    };

    /// <summary>
    /// スプライト生成
    /// </summary>
    /// <param name="texNumber">テクスチャ番号</param>
    /// <param name="anchorpoint">アンカーポイント</param>
    /// <param name="isFlipX">X反転するか</param>
    /// <param name="isFlipY">Y反転するか</param>
    /// <returns>スプライト</returns>
    static Sprite* Create(UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

private:
    //頂点バッファ;
    ComPtr<ID3D12Resource> vertBuff_;
    //頂点バッファビュー;
    D3D12_VERTEX_BUFFER_VIEW vbView_{};
    //定数バッファ;
    ComPtr<ID3D12Resource> constBuff_;
    // Z軸回りの回転角
    float rotation_ = 0.0f;
    // 座標
    XMFLOAT3 position_ = { 0,0,0 };
    // ワールド行列
    XMMATRIX matWorld_;
    // 色(RGBA)
    XMFLOAT4 color_ = { 1, 1, 1, 1 };
    // テクスチャ番号
    UINT texNumber_ = 0;
    // 大きさ
    XMFLOAT2 size_ = { 100, 100 };
    // アンカーポイント
    XMFLOAT2 anchorpoint_ = { 0.5f, 0.5f };
    // 左右反転
    bool isFlipX_ = false;
    // 上下反転
    bool isFlipY_ = false;
    // テクスチャ左上座標
    XMFLOAT2 texLeftTop_ = { 0, 0 };
    // テクスチャ切り出しサイズ
    XMFLOAT2 texSize_ = { 100, 100 };
    // 非表示
    bool isInvisible_ = false;

public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

    /// <summary>
    /// 頂点バッファの転送
    /// </summary>
    void TransferVertexBuffer();

    /// <summary>
    /// 毎フレーム更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    void SetPosition(const XMFLOAT3& position) { position_ = position; }
    void SetRotation(float rotation) { rotation_ = rotation; }
    void SetSize(const XMFLOAT2& size) { size_ = size; }
    void SetTexLeftTop(const XMFLOAT2& texLeftTop) { texLeftTop_ = texLeftTop; }
    void SetTexSize(const XMFLOAT2& texSize) { texSize_ = texSize; }
};

