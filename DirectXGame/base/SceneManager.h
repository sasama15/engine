#pragma once

#include "BaseScene.h"
#include "AbstractSceneFactory.h"

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

	/// <summary>
	/// 次シーン予約
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { sceneFactory_ = sceneFactory; }

private:
	// 今のシーン
	BaseScene* scene_ = nullptr;
	// 次のシーン
	BaseScene* nextScene_ = nullptr;

	// シーンファクトリ
	AbstractSceneFactory* sceneFactory_ = nullptr;

	//コンストラクタとデストラクタの隠蔽
	SceneManager() = default;
	~SceneManager();
	// コピーインストラクタの隠蔽
	SceneManager(const SceneManager&) = delete;
	// コピー代入演算子の隠蔽
	void operator = (const SceneManager&) = delete;
};

