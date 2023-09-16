#pragma once
#include"Player.h"
#include"Seen.h"

//------------------------------------//
//エネミー変数・関数
//------------------------------------//
const int FIRST_ENEMY_POSITION_X = 1000;										//エネミーの初期X座標
const int FIRST_ENEMY_POSITION_Y = 750;											//エネミーの初期Y座標
const int FIRST_ENEMY_SPEED = 5;												//エネミーの初期速度
const int EW = 32;																//エネミーの幅(48/1.5)
const int EH = 42;																//エネミーの高さ(62/1.5)

class Enemy
{
public:
	//..................画像処理.................//
	int Img;																	//エネミー画像
	int Normal;																	//エネミー待機画像
	int Walk;																	//エネミー移動画像
	int WalkUp;																	//エネミー移動画像(上)
	int WalkDown;																//エネミー移動画像(下)
	bool Reverse = false;														//エネミー反転
	bool DrawFlag = false;														//エネミー描画フラグ
	int RunBgm;
	bool isSoundFlag = false;

	//..................移動処理.................//
	int X;																		//エネミーX座標
	int Y;																		//エネミーY座標
	int Speed;																	//エネミー速度
	int Num = -1;																//エネミー番号
	bool enemy = false;

	void Init();
	void Load();
	void Main(Player* playe, Game* game);
	void Draw();
	void GetX(int Gx);
	void SetX(int Sx);
	void GetY(int Gy);
	void SetY(int Sy);
};

