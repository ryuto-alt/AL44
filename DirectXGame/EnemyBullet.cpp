#include "EnemyBullet.h"
#include <MyMath.h> // 必要に応じて線形補間関数を使用
#include <cassert>
#include <TextureManager.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void EnemyBullet::Update(const Vector3& playerPosition) {
	// プレイヤーの位置に向かうベクトルを計算
	Vector3 direction = playerPosition - worldTransform_.translation_;
	direction.Normalize(direction);

	// 速度を調整
	velocity_ = direction * 0.5f; // 弾速を0.5に設定（調整可）
	worldTransform_.translation_ += velocity_;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
