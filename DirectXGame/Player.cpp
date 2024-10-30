#include "Player.h"
#include <cassert>
#include <numbers>

#include "Mymath.h"


void Player::Initialize(Model* model, uint32_t textureHandle, const Vector3& position) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	input_->Input::GetInstance();
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// プレイヤーの座標
	worldTransform_.translation_ = position;
}

void Player::Update() {

	
	const float CharaSpeed = 0.5f;
	Vector3 move = {0, 0, 0};

	// 行列を定数うバッファに転送
	worldTransform_.TransferMatrix();
	

	if (Input::GetInstance()->PushKey(DIK_A)) {
		move.x -= CharaSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		move.x += CharaSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		move.y += CharaSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		move.y -= CharaSpeed;
	}

	if (bullet_) {
		bullet_->Update();
	}
	worldTransform_.translation_ .x+= move.x;
	worldTransform_.translation_ .y+= move.y;
	worldTransform_.translation_ .z+= move.z;
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Attack();
	}
}

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_);

if (bullet_) {
		bullet_->Draw(viewProjection);

	}

}

void Player::Attack() {

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
	
		// すでに弾が存在している場合、古い弾を解放
		if (bullet_ != nullptr) {
			delete bullet_;
		}

		// 新しい弾を生成してbullet_に保持
		bullet_ = new PlayerBullet();
		bullet_->Initialize(model_, worldTransform_.translation_);
	}

}
