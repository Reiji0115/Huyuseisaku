#pragma once
#include "Player.h"
#include "Collision.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();

private:
	int m_frameCount;
	Player m_player;
	Circle m_bossAttackCollision; // 仮のボス攻撃の円形当たり判定
	bool m_parrySucceeded; // パリィに成功したかどうか
	int m_parrySuccessTimer; // パリィ成功表示の残りフレーム数
};

