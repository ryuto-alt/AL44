#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update(const Vector3& playerPosition); // プレイヤー位置を渡すよう変更
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	Vector3 velocity_;
	static const int32_t klifeTime = 60 * 2;
	int32_t deathTimer_ = klifeTime;
	bool isDead_ = false;
};
