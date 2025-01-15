#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <Vector3.h>
#include <ViewProjection.h>
#include <WorldTransform.h>

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& direction);

	void Update();

	bool IsExpired() const;

	void Draw(const ViewProjection& viewProjection);

	Model* model_;

	Vector3 GetPosition() const { return worldTransform_.translation_; }
private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	int textureHandle_ = 0;

	Vector3 direction_;           // 発射方向
	float speed_ = 1.0f;          // 弾の速度
	const float lifespan_ = 3.0f; // 生存時間（秒）
	float elapsedTime_ = 0.0f;    // 経過時間
};
