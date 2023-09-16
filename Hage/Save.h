#pragma once
#include"Seen.h"
#include"Player.h"
#include"Enemy.h"
#include"Collision.h"
#include"Item.h"
#include"Comment.h"

const int ImgX = 10;
const int ImgY = 10;
const int Select_Num = 72;
class Save
{
public:
	int SaveImg;
	int EscSound;
	int SelectImg;
	int SelectY = 35;
	bool save=false;

	int PlayerX=FIRST_PLAYER_POSITION_X;
	int PlayerY=FIRST_PLAYER_POSITION_Y;
	int EnemyX;
	int EnemyY;
	bool EnemyFlag;
	bool EnemyDrawFlag;
	int FileNum;
	int FileNum2;
	int ItemNum;
	int CommentFlag;

	void Load();
	void GameSave(Game*game,Player*player,Enemy*enemy,Collision*collision,Item*item,Comment*comment);
	void LoadData(Game* game, Player* player, Enemy* enemy, Collision* collision, Item* item,Comment*comment);
};

