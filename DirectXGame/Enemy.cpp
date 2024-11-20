#include "Enemy.h"
#include <TextureManager.h>
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position) {
	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
}

void Enemy::Update() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ（フェーズごとの速度を設定）
	const float kApproachSpeed = 0.2f;
	const float kLeaveSpeed = 0.1f;

	// フェーズごとの挙動を管理
	switch (phase_) {
	case Phase::Approach:
		// 接近フェーズ
		move.z -= kApproachSpeed;
		// 離脱条件を判定
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;

	case Phase::Leave:
		// 離脱フェーズ（斜め左上に移動）
		move.x -= kLeaveSpeed; // 左方向
		move.y += kLeaveSpeed; // 上方向（Z軸の正方向）
		break;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }
