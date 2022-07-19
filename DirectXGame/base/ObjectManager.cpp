#include "ObjectManager.h"

void ObjectManager::Update()
{
	for (std::shared_ptr<Object3d>& object : objects_) {
		object->Update();
	}
}

void ObjectManager::Draw()
{
	for (std::shared_ptr<Object3d>& object : objects_) {
		object->Draw();
	}
}

std::weak_ptr<Object3d>  ObjectManager::AddObject(std::shared_ptr<Object3d> object)
{
	// �I�u�W�F�N�g���X�g�ɓo�^
	objects_.push_back(std::move(object));

	return objects_.back();
}
