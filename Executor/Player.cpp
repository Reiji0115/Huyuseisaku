#include "DxLib.h"
#include "Player.h"
#include "Game.h"

namespace
{
	constexpr float kGravity = 0.5f;
	constexpr float kMoveAcceleration = 0.4f;
	constexpr float kFriction = 0.75f;
	constexpr float kMaxMoveSpeed = 8.0f;
	constexpr int kPlayerHalfSize = 25;
}

void Player::Init()
{
	m_playerX = static_cast<float>(Game::kScreenWidth) / 2.0f;
	m_playerY = static_cast<float>(Game::kScreenHeight) / 2.0f;
	m_playerVelocityX = 0.0f;
	m_playerVelocityY = 0.0f;

	m_playerGraph = LoadGraph("sozai/image/player2.png");
}

void Player::End()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_playerVelocityX -= kMoveAcceleration;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_playerVelocityX += kMoveAcceleration;
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 0)
	{
		m_playerVelocityX *= kFriction;
	}

	if (m_playerVelocityX > kMaxMoveSpeed)
	{
		m_playerVelocityX = kMaxMoveSpeed;
	}
	if (m_playerVelocityX < -kMaxMoveSpeed)
	{
		m_playerVelocityX = -kMaxMoveSpeed;
	}

	m_playerX += m_playerVelocityX;

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		m_playerVelocityY = -10.0f;
	}

	m_playerVelocityY += kGravity;
	m_playerY += static_cast<int>(m_playerVelocityY);

	const float floorY = Game::kScreenHeight - kPlayerHalfSize;
	if (m_playerY >= floorY)
	{
		m_playerY = static_cast<int>(floorY);
		m_playerVelocityY = 0.0f;
	}
}

void Player::Draw()
{
	if (m_playerGraph == -1)
	{
		DrawBox(
			static_cast<int>(m_playerX) - kPlayerHalfSize,
			m_playerY - kPlayerHalfSize,
			static_cast<int>(m_playerX) + kPlayerHalfSize,
			m_playerY + kPlayerHalfSize,
			GetColor(255, 0, 0),
			TRUE);

		return;
	}
	
	// プレイヤーの画像を描画
	DrawExtendGraph(
		static_cast<int>(m_playerX) - kPlayerHalfSize,
		m_playerY - kPlayerHalfSize,
		static_cast<int>(m_playerX) + kPlayerHalfSize,
		m_playerY + kPlayerHalfSize,
		m_playerGraph,
		TRUE);
}

int Player::GetX() const
{
	return static_cast<int>(m_playerX);
}

int Player::GetY() const
{
	return m_playerY;
}
