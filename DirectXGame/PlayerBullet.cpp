#include "PlayerBullet.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& direction) {
	assert(model);
	model_ = model;
	model_ = Model::Create();
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	direction_ = direction;
	worldTransform_.translation_ = position;
	// ワールド行列を更新
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Update() { 
	
	worldTransform_.TransferMatrix();
	// 弾の移動
	worldTransform_.translation_.x += direction_.x * speed_;
	worldTransform_.translation_.y += direction_.y * speed_;
	worldTransform_.translation_.z += direction_.z * speed_;
	worldTransform_.UpdateMatrix();

	// 経過時間を更新
	elapsedTime_ += 0.016f; // フレームレート60fps想定で約1フレームごとに更新


	worldTransform_.UpdateMatrix(); 
}
bool PlayerBullet::IsExpired() const { return elapsedTime_ > lifespan_; }

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_); 

}
