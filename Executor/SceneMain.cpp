#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr int kParrySuccessDuration = 120; // パリィ成功状態を表示するフレーム数（約2秒）
}

SceneMain::SceneMain():
	m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_frameCount = 0;
	m_player.Init();
	m_bossAttackCollision = {
		static_cast<float>(Game::kScreenWidth / 2 ),
		static_cast<float>(Game::kScreenHeight -40.0f),
		25.0f};
	m_parrySucceeded = false;
}

void SceneMain::End()
{
	m_player.End();
}

void SceneMain::Update()
{
	m_frameCount++;
	m_player.Update();

	if (m_parrySucceeded)
	{
		--m_parrySuccessTimer;

		if (m_parrySuccessTimer <= 0)
		{
			m_parrySucceeded = false;
		}
	}

	if (m_player.IsParrying() && !m_parrySucceeded)
	{
		const Circle parryCircle = m_player.GetParryCollision(); // プレイヤーの前方にある弾き判定

		if (Collision::IsCircleHit(parryCircle, m_bossAttackCollision))
		{
			m_parrySucceeded = true;
			m_parrySuccessTimer = kParrySuccessDuration;
		//	printfDx("[PARRY SUCCESS] Boss attack was parried. Frame: %d\n", m_frameCount);
		}
	}
}

void SceneMain::Draw()
{
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "X:%d Y:%d", m_player.GetX(), m_player.GetY());
	DrawString(0, 48, "Z: Parry", GetColor(255, 255, 255));

	if (m_parrySucceeded)
	{
		DrawString(0, 64, "[PARRY SUCCESS]", GetColor(0, 255, 0));
	}

	const int bossAttackColor =
		m_parrySucceeded ? GetColor(0, 255, 0) : GetColor(255, 0, 0); // 仮攻撃の表示色

	DrawCircle(
		static_cast<int>(m_bossAttackCollision.x),
		static_cast<int>(m_bossAttackCollision.y),
		static_cast<int>(m_bossAttackCollision.radius),
		bossAttackColor,
		TRUE);
	DrawString(
		static_cast<int>(m_bossAttackCollision.x - 45.0f),
		static_cast<int>(m_bossAttackCollision.y - 10.0f),
		"BOSS ATTACK",
		GetColor(255, 255, 255));

	m_player.Draw();
}
