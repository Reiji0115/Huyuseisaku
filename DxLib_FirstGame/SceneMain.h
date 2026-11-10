#pragma once
#include "Player.h"
#include "Bg.h"

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
	// シーンで使用するリソースのハンドル
	int m_playerIdleHandle;
	int m_playerRunHandle;

	// フォントのハンドル
	int m_uiFontHandle;

	// サウンドリソースのハンドル
	int m_bgmHandle;
	int m_hitSeHandle;

	// フェード処理
	int m_fadeAlpha;
	int m_fadeSpeed;

	int m_frameCount;

	// ゲームオーバーになったか？
	bool m_isGameover;

	Player m_player;
	Bg m_Bg;

};

