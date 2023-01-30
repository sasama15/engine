#include "Universe.h"

void Universe::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド座標の初期化
}

void Universe::Update()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	// 移動ベクトルを変更する処理

	// 座標移動(ベクトルの加算)

	// 行列更新

	// 座標を画面表示する処理
}

void Universe::Draw()
{
	// 宇宙描画
	model_->Draw(worldTransform_, viewProjection_);
}
