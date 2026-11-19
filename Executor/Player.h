#pragma once
#include"Actor.h"
#include"Collision.h"
class Player : public Actor
{
public:
	void Init() override;
	void End() override;
	void Update()override;
	void Draw()override;

	int GetX() const;
	int GetY() const;

	bool IsParrying() const; // 弾き中かどうかを返す
	Circle GetParryCollision()const; // 弾き用の円を返す
	float GetParryRadius() const; // 弾き判定の半径を返す

private:
	float m_playerX = 0.0f; // プレイヤーのX座標
	float m_playerY = 0.0f; // プレイヤーのY座標
	float m_playerVelocityX = 0.0f; // プレイヤーのX方向の速度
	float m_playerVelocityY = 0.0f; // プレイヤーのY方向の速度
	int m_facingDirection = 1; // プレイヤーが向いている方向（右が1、左が-1）
	bool m_isParrying = false; // 現在弾き中かどうか
	int m_parryTimer = 0; // 弾き状態の残りフレーム数
	bool m_parryButtonDown = false; // 前フレームで弾きボタンが押されていたか
	int m_playerGraph = -1;
};
