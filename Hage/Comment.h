#pragma once
#include"Player.h"
#include"Enemy.h"

const int TextX = 400;
const int TextY = 860;

class Comment
{
public:
	bool CommentFlag = true;
	bool LockFlag = false;
	int CommentImg;

	void Load();
	void Init();
	void Main(int num1,int num2,Player*player,Enemy*enemy,Game*game);
};

