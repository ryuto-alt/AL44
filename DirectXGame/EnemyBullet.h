#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& playerPosition);
	void Update(const Vector3& playerPosition);
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	Vector3 velocity_;                       // 弾の速度
	static const int32_t klifeTime = 60 * 2; // 弾の寿命
	int32_t deathTimer_ = klifeTime;
	int followFrames_ = 0; // 追従するフレーム数
	bool isDead_ = false;
};
