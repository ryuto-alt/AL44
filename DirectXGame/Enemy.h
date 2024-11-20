#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Enemy {
public:
	// 状態フェーズ
	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱
	};

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// フェーズ
	Phase phase_ = Phase::Approach; // 初期フェーズは接近

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
