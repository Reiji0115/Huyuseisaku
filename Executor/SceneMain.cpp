#include "SceneMain.h"
#include "DxLib.h"

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
}

void SceneMain::End()
{
	m_player.End();
}

void SceneMain::Update()
{
	m_frameCount++;
	m_player.Update();
}

void SceneMain::Draw()
{
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "X:%d Y:%d", m_player.GetX(), m_player.GetY());
	m_player.Draw();
}
