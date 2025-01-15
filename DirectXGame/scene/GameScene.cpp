#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	BullettextureHandle_ = TextureManager::Load("white1x1.png");

	// モデルの生成
	model_ = Model::Create();
	Bulletmodel_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	player_ = new Player();
	Vector3 playerPosition = {0, 0, 0};
	player_->Initialize(model_, textureHandle_, playerPosition);

	// 敵の生成
	enemy_ = new Enemy();
	Vector3 EnemyPosition = {0, 0, 20};
	// 敵の初期化
	enemy_->Initialize(model_, EnemyPosition);


	Vector3 direction = {
	    cos(player_->GetRotation().y), // Y軸の回転に基づくX方向の成分
	    0.0f,
	    sin(player_->GetRotation().y) // Y軸の回転に基づくZ方向の成分
	};
	// PlayerBulletの初期化
	playerBullet_ = new PlayerBullet(); // ここでplayerBullet_のメモリを確保
	playerBullet_->Initialize(Bulletmodel_, playerPosition, direction);
}

void GameScene::Update() {
	player_->Update();
	playerBullet_->Update();
	// 敵の更新
	// プレイヤーの位置を取得
	Vector3 playerPosition = player_->GetPosition();

	// 敵の更新にプレイヤーの位置を渡す
	enemy_->Update(playerPosition);

	// プレイヤーの弾とエネミーの弾の衝突判定
	for (auto playerIt = player_->bullets_.begin(); playerIt != player_->bullets_.end();) {
		bool playerBulletDeleted = false;

		for (auto enemyIt = enemy_->bullets_.begin(); enemyIt != enemy_->bullets_.end();) {
			if (CheckCollision((*playerIt)->GetPosition(), (*enemyIt)->GetPosition(), 0.5f, 0.5f)) {
				delete *playerIt;
				playerIt = player_->bullets_.erase(playerIt);

				delete *enemyIt;
				enemyIt = enemy_->bullets_.erase(enemyIt);

				playerBulletDeleted = true;
				break;
			} else {
				++enemyIt;
			}
		}

		if (!playerBulletDeleted) {
			++playerIt;
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// 自キャラ描画
	player_->Draw(viewProjection_);
	/*playerBullet_->Draw(viewProjection_);*/
	// 敵の描画
	enemy_->Draw(viewProjection_);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

bool GameScene::CheckCollision(const Vector3& pos1, const Vector3& pos2, float radius1, float radius2) {
	float distanceSq = (pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z);
	float combinedRadius = radius1 + radius2;
	return distanceSq <= (combinedRadius * combinedRadius);
}