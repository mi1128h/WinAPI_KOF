#pragma once
#include "config.h"

enum Stage {
	Stage1,
	Stagelength
};

class Image;
class AnimCharacter;
class AnimBackground
{
private:
	FPOINT position;
	float speed;

	vector<Image*> vImages[Stage::Stagelength];
	Stage curStage;
	int frameIdx;

	AnimCharacter* focusTarget;

public:
	void Init();
	void Release();
	void Update();
	void Animate();
	void Render(HDC hdc);

	FPOINT GetPos() { return position; }
	Stage GetStage() { return curStage; }
	void SetStage(Stage stage) { curStage = stage; }
};

