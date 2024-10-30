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

	const float RotationSpeed = 0.05f; // 回転速度
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

	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= RotationSpeed; // 左方向に回転
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

		worldTransform_.rotation_.y += RotationSpeed; // 左方向に回転
	}

	if (bullet_) {
		bullet_->Update();
	}
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
	worldTransform_.UpdateMatrix();
	// スペースキーが押されたら弾を発射
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Attack();
	}
	
	// 全ての弾を更新し、期限切れの弾を削除
	for (auto it = bullets_.begin(); it != bullets_.end();) {
		(*it)->Update();
		if ((*it)->IsExpired()) {
			delete *it;
			it = bullets_.erase(it); // 弾が期限切れなら削除
		} else {
			++it;
		}
	}
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
	// 全ての弾を描画
	for (auto bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		// プレイヤーのY軸の回転角度から発射方向を計算
		float angle = worldTransform_.rotation_.y;

		// X-Z平面での方向ベクトルを計算
		Vector3 direction = {
		    sin(angle), // X成分（Y軸回転に基づく）
		    0.0f,       // Y成分（平面上なので0）
		    cos(angle)  // Z成分（Y軸回転に基づく）
		};

		// 新しい弾を生成してリストに追加
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, direction);
		bullets_.push_back(newBullet);
	}
}
