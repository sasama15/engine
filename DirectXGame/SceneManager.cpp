#include "SceneManager.h"

#include <cassert>

SceneManager::~SceneManager()
{
	// 最後のシーンの終了と解放
	scene_->Finalize();
	delete scene_;
}

SceneManager* SceneManager::GetInstance()
{
	// 初めて呼ばれた時だけインスタンスが生成される
	static SceneManager instance;

	// 2回目以降は以下のみ通る
	return &instance;
}

void SceneManager::Update()
{
	// シーン切り替えがあるなら
	if (nextScene_) {
		// 旧シーンの終了
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}

		// シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;

		// 新シーンの初期化
		scene_->Initialize();
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// 次シーンを生成
	nextScene_ = sceneFactory_->CreateScene(sceneName);
}
