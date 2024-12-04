#include "EnemyBullet.h"
#include <MyMath.h>
#include <TextureManager.h>
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& playerPosition) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// 初期速度をプレイヤー方向に設定
	Vector3 direction = playerPosition - position;
	direction.Normalize(direction);
	velocity_ = direction * 0.05f; // 初期速度設定
	followFrames_ = 30;            // 30フレームだけ追従する
}

void EnemyBullet::Update(const Vector3& playerPosition) {
	// 追従処理（一定フレーム数のみ）
	if (followFrames_ > 0) {
		Vector3 directionToPlayer = playerPosition - worldTransform_.translation_;
		directionToPlayer.Normalize(directionToPlayer);

		// 追従中は方向を更新
	/*	velocity_ = directionToPlayer * 0.05f;*/
		followFrames_--; // 追従フレームを減らす
	}

	// 弾を移動
	worldTransform_.translation_ += velocity_;

	// 寿命タイマーの更新
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
