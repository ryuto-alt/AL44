#pragma once
#include <Model.h>
#include <TextureManager.h>
#include <Vector3.h>
#include <WorldTransform.h>
#include <ViewProjection.h>

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	Model* model_;
private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	int textureHandle_ = 0;
};
