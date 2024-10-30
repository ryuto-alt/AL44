#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include<PlayerBullet.h>
#include <ViewProjection.h>
#include <input.h>
class Player {

public:
	/// 初期化
	

	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	/// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void Attack();

private:
	// ワールド返還データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	PlayerBullet* bullet_ = nullptr;

	 // 弾を複数管理するためのベクター
	std::vector<PlayerBullet*> bullets_;

	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_=nullptr;
	//speed
	

};
