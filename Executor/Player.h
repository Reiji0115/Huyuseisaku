#pragma once
class Player
{
public:
	void Init();
	void End();
	void Update();
	void Draw();

	int GetX() const;
	int GetY() const;

	int playerGraph;

private:
	int m_playerX = 0; // プレイヤーのX座標
	int m_playerY = 0; // プレイヤーのY座標
};

