#include "Enemy.h"
#include <MyMath.h>
#include <TextureManager.h>
#include <cassert>

Enemy::~Enemy() {
	// bullet_の解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	bullets_.clear();
}

void Enemy::Initialize(Model* model, const Vector3& position) {
	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.x = 15.0f;
	worldTransform_.translation_.z = 50.0f;

	ApproachInitialize();
}

void Enemy::Update(const Vector3& playerPosition) {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	switch (phase_) {
	case Phase::Approach:
		worldTransform_.translation_ -= Vector3(0, 0, 0.1f);
		if (worldTransform_.translation_.z < 10.0f) {
			phase_ = Phase::Leave;
		}
		fireTimer--;
		if (fireTimer <= 0) {
			Fire(playerPosition); // プレイヤーの位置を渡す
			fireTimer = kFIreInterval;
		}
		break;
	case Phase::Leave:
		worldTransform_.translation_ += Vector3(-0.1f, 0.1f, -0.1f);
		break;
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update(playerPosition); // プレイヤーの位置を弾の更新に渡す
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire(const Vector3& playerPosition) {
	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, playerPosition);

	// 弾をリストに追加
	bullets_.push_back(newBullet);
}

void Enemy::ApproachInitialize() { fireTimer = kFIreInterval; }
