#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"


SceneMain::SceneMain():
	m_playerIdleHandle(-1),
	m_playerRunHandle(-1),
	m_bgmHandle(-1),
	m_hitSeHandle(-1),
	m_uiFontHandle(-1),
	m_fadeAlpha(0),
	m_fadeSpeed(0),
	m_frameCount(0),
	m_isGameover(false)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// シーン内で使用するリソースのロード
	m_playerIdleHandle = LoadGraph("image/idle.png");
	m_playerRunHandle = LoadGraph("image/run.png");
	
	// サウンドのロード
	m_hitSeHandle = LoadSoundMem("sound/hit.mp3");
	m_bgmHandle = LoadSoundMem("sound/bgm.mp3");

	// フォントの作成
	m_uiFontHandle = CreateFontToHandle("Bernard MT Condensed",48,-1,-1);

	// フェードイン開始
	m_fadeAlpha=255;
	m_fadeSpeed = -8;

	m_frameCount = 0;
	m_Bg.Init();

	m_player.SetIdleGraph(m_playerIdleHandle);
	m_player.SetRunGraph(m_playerRunHandle);
	m_player.Init();


	// フェードイン開始
	m_fadeAlpha = 255;
	m_fadeSpeed = -8;

	// BGMをならし始める
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	
}

void SceneMain::End()
{
	// BGMの停止
	StopSoundMem(m_bgmHandle);

	m_Bg.End();
	m_player.End();

	// シーンで使用したリソースをメモリから削除
	DeleteGraph(m_playerRunHandle);
	DeleteGraph(m_playerIdleHandle);
	// サウンドをメモリから削除
	DeleteSoundMem(m_hitSeHandle);
	DeleteSoundMem(m_bgmHandle);
	// フォントをメモリから削除
	DeleteFontToHandle(m_uiFontHandle);
}

void SceneMain::Update()
{
	m_frameCount++;
}

void SceneMain::Draw()
{
	m_Bg.Draw();
	m_player.Draw();

	// UIの表示 UIはゲームの最前面に表示される

	// ゲームオーバー表示
	if (m_isGameover)
	{
		int width = GetDrawStringWidthToHandle("GAME OVER!",strlen("GAMEOVER!"),m_uiFontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, 200, "GAMEOVER!",GetColor(200, 200, 200), m_uiFontHandle);
	}

	// フェード処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}