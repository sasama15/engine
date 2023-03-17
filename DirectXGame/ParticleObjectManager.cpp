#include "ParticleObjectManager.h"

void ParticleObjectManager::Update()
{
	for (std::shared_ptr<ParticleManager>& object : objects_) {
		object->Update();
	}
}

void ParticleObjectManager::Draw()
{
	for (std::shared_ptr<ParticleManager>& object : objects_) {
		object->Draw();
	}
}

std::weak_ptr<ParticleManager>  ParticleObjectManager::AddObject(std::shared_ptr<ParticleManager> object)
{
	// �I�u�W�F�N�g���X�g�ɓo�^
	objects_.push_back(std::move(object));

	return objects_.back();
}