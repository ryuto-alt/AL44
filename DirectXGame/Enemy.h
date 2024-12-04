#pragma once
#include "EnemyBullet.h"
#include "Model.h"
#include "Player.h"
#include "WorldTransform.h"
#include <list>

class Enemy {
public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position);
	void Update(const Vector3& playerPosition); // 引数をVector3に変更
	void Draw(const ViewProjection& viewProjection);

	void Fire(const Vector3& playerPosition); // 引数にプレイヤーの位置を追加

	// 発射間隔
	static const int kFIreInterval = 60;

private:
	void ApproachInitialize();

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave     // 離脱する
	};
	Phase phase_ = Phase::Approach;

	// 発射タイマー
	int fireTimer = 0;

	// 弾丸のリスト
	std::list<EnemyBullet*> bullets_;
};
