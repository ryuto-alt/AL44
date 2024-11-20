#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 3dモデルデータ
	Model* model_ = nullptr;
	Model* Bulletmodel_ = nullptr;
private: // メンバ変数
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t BullettextureHandle_ = 0;

	// ワールドトランスフォーム
	/*WorldTransform worldTransform_;*/
	Player* player_ = nullptr;
	PlayerBullet* playerBullet_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
