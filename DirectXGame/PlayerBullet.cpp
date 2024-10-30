#include "PlayerBullet.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	model_ = Model::Create();
	
	worldTransform_.Initialize();
	
	worldTransform_.translation_ = position;
	// ワールド行列を更新
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Update() { 
	
	worldTransform_.TransferMatrix();
	


	worldTransform_.UpdateMatrix(); 
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_); 

}
