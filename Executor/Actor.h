#pragma once

class Actor
{
public:
	virtual ~Actor() = default;

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};