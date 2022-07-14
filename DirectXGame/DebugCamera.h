#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class DebugCamera :
    public Camera
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="winWidth">画面幅</param>
    /// <param name="winHeight">画面高さ</param>
    /// <param name="input">入力</param>
    DebugCamera(int winWidth, int winHeight, Input* input);

    // 更新
    void Update() override;

    void SetDistance(float distance) { this->distance = distance; viewDirty = true; }

private:
    // 入力クラスのポインタ
    Input* input;
    // カメラ注視点までの距離
    float distance = 25;
    // スケーリング
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    // 回転行列
    DirectX::XMMATRIX matRot = DirectX::XMMatrixIdentity();
};

