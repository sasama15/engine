#pragma once
#include "../PostSprite.h"
class PostEffect :
    public PostSprite
{
private:
    // 画面クリアカラー
    static const float clearColor[4];

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="comList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// 描画コマンドの発行
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画後処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// パイプライン生成
    /// </summary>
    void CreateGraphicsPipelineState();

private:
    // テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff;
    // SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    // 深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    // RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    // DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    // グラフィックスパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    // ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;
};

