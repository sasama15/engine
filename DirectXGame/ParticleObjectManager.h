#pragma once
#include "ParticleManager.h"
#include <memory>

class ParticleObjectManager
{
public:
	/// <summary>
	/// 3Dオブジェクト更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクト追加
	/// </summary>
	/// <param name="object">オブジェクト</param>
	//void AddObject(std::shared_ptr<Object3d> object);
	std::weak_ptr<ParticleManager> AddObject(std::shared_ptr<ParticleManager> object);
private:
	// オブジェクトリスト
	std::vector<std::shared_ptr<ParticleManager>> objects_;
};

