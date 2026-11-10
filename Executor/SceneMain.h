#pragma once
#include "Player.h"

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
};

