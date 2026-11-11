#include "DxLib.h"
#include "Player.h"
#include "Game.h"

namespace
{
	int playerX = 0; // プレイヤーのX座標
	float playerY = 0.0f; // プレイヤーのY座標
	float playerVelocityY = 0.0f; // プレイヤーのY方向の速度
	constexpr float kGravity = 0.5f;
	constexpr int kPlayerHalfSize = 25;

	
}

void Player::Init()
{
	playerX = Game::kScreenWidth / 2;
	playerY = Game::kScreenHeight / 2;
	playerVelocityY = 0.0f;

	playerGraph = LoadGraph("sozai/image/player2.png");
}

void Player::End()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		playerX -= 5;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		playerX += 5;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		playerVelocityY = -10.0f;
	}

	playerVelocityY += kGravity;
	playerY += playerVelocityY;

	const float floorY = Game::kScreenHeight - kPlayerHalfSize;
	if (playerY >= floorY)
	{
		playerY = floorY;
		playerVelocityY = 0.0f;
	}
}

void Player::Draw()
{
	if (playerGraph == -1)
	{
		DrawBox(
			playerX - kPlayerHalfSize,
			static_cast<int>(playerY) - kPlayerHalfSize,
			playerX + kPlayerHalfSize,
			static_cast<int>(playerY) + kPlayerHalfSize,
			GetColor(255, 0, 0),
			TRUE);

		return;
	}
	
	DrawExtendGraph(
		playerX - kPlayerHalfSize,
		static_cast<int>(playerY) - kPlayerHalfSize,
		playerX + kPlayerHalfSize,
		static_cast<int>(playerY) + kPlayerHalfSize,
		playerGraph,
		TRUE);
}
