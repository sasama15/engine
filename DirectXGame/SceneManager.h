#pragma once

#include "BaseScene.h"

/// <summary>
/// シーン管理
/// </summary>
class SceneManager
{
public:
	// このクラス全体で使う機能
	static SceneManager* GetInstance();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 次シーン予約
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }

private:
	// 今のシーン
	BaseScene* scene_ = nullptr;
	// 次のシーン
	BaseScene* nextScene_ = nullptr;

	//コンストラクタとデストラクタの隠蔽
	SceneManager() = default;
	~SceneManager();
	// コピーインストラクタの隠蔽
	SceneManager(const SceneManager&) = delete;
	// コピー代入演算子の隠蔽
	void operator = (const SceneManager&) = delete;
};

