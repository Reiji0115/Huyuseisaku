#include "DxLib.h"
#include <cmath>
#include "Player.h"
#include "Game.h"

namespace
{
	constexpr float kGravity = 0.5f;
	constexpr float kMaxMoveSpeed = 5.0f; // プレイヤーの横移動の最高速度
	constexpr float kMoveResponse = 0.2f; // 現在速度を目標速度へ近づける割合
	constexpr int kPlayerHalfSize = 25;
	constexpr float kDeadZone = 0.1f;
	constexpr int kParryDuration = 8; // 弾き状態を維持するフレーム数
	constexpr float kParryRadius = 40.0f; // 弾き判定の半径
	constexpr float kParryOffset = 45.0f; // プレイヤー中心から前方へずらす距離
}

void Player::Init()
{
	m_playerX = static_cast<float>(Game::kScreenWidth) / 2.0f;
	m_playerY = static_cast<float>(Game::kScreenHeight) / 2.0f;
	m_playerVelocityX = 0.0f;
	m_playerVelocityY = 0.0f;
	m_facingDirection = 1;
	m_isParrying = false;
	m_parryTimer = 0;
	m_parryButtonDown = false;

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

	const bool keyboardParryButtonDown =
		CheckHitKey(KEY_INPUT_Z) == 1; // Zキーが押されているか
	const bool padParryButtonDown =
		(padInput & PAD_INPUT_1) != 0; // パッドAボタンが押されているか
	const bool parryButtonDown =
		keyboardParryButtonDown || padParryButtonDown; // 弾きボタンの統合入力

	if (parryButtonDown && !m_parryButtonDown)
	{
		m_isParrying = true;
		m_parryTimer = kParryDuration;
	}

	if (m_parryTimer > 0)
	{
		--m_parryTimer;
	}
	else
	{
		m_isParrying = false;
	}

	m_parryButtonDown = parryButtonDown;

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

	if (moveInputX > 0.0f)
	{
		m_facingDirection = 1;
	}
	else if (moveInputX < 0.0f)
	{
		m_facingDirection = -1;
	}

	// 統合した入力値を速度に反映する
	// スティックの傾きに応じた目標速度を計算する
	float targetVelocityX = moveInputX * kMaxMoveSpeed; // スティック入力から計算した目標速度

	// 現在の速度を目標速度へ徐々に近づける
	m_playerVelocityX += (targetVelocityX - m_playerVelocityX) * kMoveResponse;

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
}

void Player::Draw()
{
	if (m_playerGraph == -1)
	{
		DrawBox(
			static_cast<int>(m_playerX) - kPlayerHalfSize,
			static_cast<int>(m_playerY) - kPlayerHalfSize,
			static_cast<int>(m_playerX) + kPlayerHalfSize,
			static_cast<int>(m_playerY) + kPlayerHalfSize,
			GetColor(255, 0, 0),
			TRUE);
	}
	else
	{
		// プレイヤーの画像を描画
		DrawExtendGraph(
			static_cast<int>(m_playerX) - kPlayerHalfSize,
			static_cast<int>(m_playerY) - kPlayerHalfSize,
			static_cast<int>(m_playerX) + kPlayerHalfSize,
			static_cast<int>(m_playerY) + kPlayerHalfSize,
			m_playerGraph,
			TRUE);
	}

	const Circle parryCircle = GetParryCollision(); // 前方にあるパリィ判定
	const int parryColor = m_isParrying
		? GetColor(0, 255, 255)
		: GetColor(100, 100, 100); // パリィ中かどうかによる判定表示色

	DrawCircle(
		static_cast<int>(parryCircle.x),
		static_cast<int>(parryCircle.y),
		static_cast<int>(GetParryRadius()),
		parryColor,
		FALSE);
}

int Player::GetX() const
{
	return static_cast<int>(m_playerX);
}

int Player::GetY() const
{
	return static_cast<int>(m_playerY);
}

bool Player::IsParrying() const
{
	return m_isParrying;
}

Circle Player::GetParryCollision() const
{
	Circle parryCollision; // プレイヤーの弾き判定

	parryCollision.x = m_playerX; // 円の中心のX座標を設定
	parryCollision.y = m_playerY; // 円の中心のY座標を設定
	parryCollision.x += kParryOffset * m_facingDirection; // プレイヤーの前方へ判定を移動
	parryCollision.radius = kParryRadius; // 円の半径を設定

	return parryCollision;
}

float Player::GetParryRadius() const
{
	return kParryRadius;
}
