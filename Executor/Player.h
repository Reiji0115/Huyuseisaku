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
};

