#pragma once
#include"Actor.h"
class Player : public Actor
{
public:
	void Init() override;
	void End() override;
	void Update()override;
	void Draw()override;

	int GetX() const;
	int GetY() const;

private:
	float m_playerX = 0.0f; // プレイヤーのX座標
	float m_playerY = 0.0f; // プレイヤーのY座標
	float m_playerVelocityX = 0.0f; // プレイヤーのX方向の速度
	float m_playerVelocityY = 0.0f; // プレイヤーのY方向の速度
	int m_playerGraph = -1;
};
