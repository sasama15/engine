#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include <math.h>

#pragma once
/// <summary>
/// 宇宙
/// </summary>
class Universe
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ワールド変換データ
	//WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;
};

