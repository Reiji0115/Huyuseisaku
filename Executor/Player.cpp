#include "DxLib.h"
#include "Player.h"
#include "Game.h"

namespace
{
	float playerVelocityY = 0.0f; // プレイヤーのY方向の速度
	constexpr float kGravity = 0.5f;
	constexpr int kPlayerHalfSize = 25;
}

void Player::Init()
{
	m_playerX = Game::kScreenDepth / 2;
	m_playerY = Game::kScreenHeight / 2;
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
		m_playerX -= 5;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_playerX += 5;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		playerVelocityY = -10.0f;
	}

	playerVelocityY += kGravity;
	m_playerY += playerVelocityY;

	const float floorY = Game::kScreenHeight - kPlayerHalfSize;
	if (m_playerY >= floorY)
	{
		m_playerY = floorY;
		playerVelocityY = 0.0f;
	}
}

void Player::Draw()
{
	if (playerGraph == -1)
	{
		DrawBox(
			m_playerX - kPlayerHalfSize,
			m_playerY - kPlayerHalfSize,
			m_playerX + kPlayerHalfSize,
			m_playerY + kPlayerHalfSize,
			GetColor(255, 0, 0),
			TRUE);

		return;
	}
	
	// プレイヤーの画像を描画
	DrawExtendGraph(
		m_playerX - kPlayerHalfSize,
		m_playerY - kPlayerHalfSize,
		m_playerX + kPlayerHalfSize,
		m_playerY + kPlayerHalfSize,
		playerGraph,
		TRUE);
}

int Player::GetX() const
{
	return m_playerX;
}

int Player::GetY() const
{
	return m_playerY;
}
