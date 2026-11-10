#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	// 使用するグラフィックハンドルの設定
	void SetIdleGraph(int handle) { m_idleGraph = handle; }
	void SetRunGraph(int handle) { m_runGraph = handle; }

	// 当たり判定実装用
	float GetColCenterX() const;
	float GetColCenterY() const;
	float GetRadius()const;

	// 死亡通知
	void OnDead();

private:
	// グラフィックハンドル
	int m_idleGraph;  // 待機
	int m_runGraph;   // 移動中

	// 位置情報
	float m_x;
	float m_y;

	// アニメーション管理用変数
	int m_animFrame;
	// 左右反転フラグ
	bool m_isFlip;
	// 移動中かどうかフラグ
	bool m_isMoving;
	// 死亡フラグ
	bool m_isDead;
};

