#include "DxLib.h"
#include <cmath>
#include "Player.h"
#include "Game.h"

namespace
{
	constexpr float kGravity = 0.5f;
	constexpr float kMoveAcceleration = 0.8f;
	constexpr float kFriction = 0.70f;
	constexpr float kMaxMoveSpeed = 5.0f;
	constexpr int kPlayerHalfSize = 25;
	constexpr float kDeadZone = 0.1f;
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
	int padInput = GetJoypadInputState(DX_INPUT_PAD1); // コントローラーのボタン入力状態

	int analogX = 0; // 左スティックのX方向の入力値
	int analogY = 0; // 左スティックのY方向の入力値

	GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

	float moveInputX = 0.0f; // キーボードとパッドを統合した横方向の入力値

	// キーボード入力を確認する
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		moveInputX -= 1.0f;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		moveInputX += 1.0f;
	}

	// コントローラーの十字キー入力を確認する
	if (padInput & PAD_INPUT_LEFT)
	{
		moveInputX = -1.0f;
	}

	if (padInput & PAD_INPUT_RIGHT)
	{
		moveInputX = 1.0f;
	}

	// 左スティックの入力値を-1.0～1.0に変換する
	float stickX = static_cast<float>(analogX) / 1000.0f; // 左スティックのX方向入力

	// スティックが十分に倒されている場合は、スティック入力を使用する
	if (std::abs(stickX) >= kDeadZone)
	{
		moveInputX = stickX;
	}

	// 統合した入力値を速度に反映する
	if (moveInputX != 0.0f)
	{
		m_playerVelocityX += moveInputX * kMoveAcceleration;
	}
	else
	{
		m_playerVelocityX *= kFriction;
	}

	// 横方向の最高速度を制限する
	if (m_playerVelocityX > kMaxMoveSpeed)
	{
		m_playerVelocityX = kMaxMoveSpeed;
	}

	if (m_playerVelocityX < -kMaxMoveSpeed)
	{
		m_playerVelocityX = -kMaxMoveSpeed;
	}

	// 速度をプレイヤーのX座標へ反映する
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

	// パッドでのプレイヤーの移動処理
	GetJoypadAnalogInput(&analogX, &analogY, 0);
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
