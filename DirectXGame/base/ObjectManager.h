#pragma once

#include "Object3d.h"
#include <memory>

// オブジェクトマネージャ
class ObjectManager
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
	std::weak_ptr<Object3d> AddObject(std::shared_ptr<Object3d> object);
private:
	// オブジェクトリスト
	std::vector<std::shared_ptr<Object3d>> objects_;
};

