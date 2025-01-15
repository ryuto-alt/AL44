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
	Vector3 GetPosition() const;

	 // プレイヤーの回転を取得するメソッド
	const Vector3& GetRotation() const { return worldTransform_.rotation_; }

	 // 弾を複数管理するためのベクター
	std::vector<PlayerBullet*> bullets_;
private:
	// ワールド返還データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	PlayerBullet* bullet_ = nullptr;


	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_=nullptr;
	//speed
	

};
