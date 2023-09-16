#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Comment.h"
#include"Item.h"

//------------------------------------//
//コリジョン変数・関数
//------------------------------------//
#define COLLISION_TILE_WIDTH 64													//タイルの幅
#define COLLISION_TILE_HEIGHT 64												//タイルの高さ
#define COLLISION_TILE_NUM_X 150												//横のタイル数
#define COLLISION_TILE_NUM_Y 36													//縦のタイル数
#define COLLISION_WINDOW_X 1920													//ウィンドウの幅
#define COLLISION_WINDOW_Y 1080													//ウィンドウの高さ

class Collision
{
public:
	//..............ファイル読み込み.............//
	const char* FileName = "Collision.csv";										//読み込みファイル
	int LockSound;																//鍵がかかっているときのサウンド
	int DoorSound;																//部屋を出入りするときのサウンド
	int BoxHandle[7];															//画像ハンドル
	int Marker;																	//マーカー
	int RawNum = 0;																//行
	int ColumnNum = 0;															//列
	int Num;																	//ハンドル番号
	char Buffer[10];															//バッファー
	bool EofFlag = false;														//Eofフラグ
	int cell[COLLISION_TILE_NUM_X][COLLISION_TILE_NUM_Y];						//縦と横のマップチップ数

	//..............当たり判定処理..............//
	int FileNum;																//ファイル番号
	int FileNum2;																//ファイル番号その2
	int NumX_1;																	//X座標処理1
	int NumY_1;																	//Y座標処理1
	int NumX_2;																	//X座標処理2
	int NumY_2;																	//Y座標処理2
	int NumX_3;																	//X座標処理3
	int NumY_3;																	//Y座標処理3
	int NumX_4;																	//X座標処理4
	int NumY_4;																	//Y座標処理4

	Collision();
	~Collision();
	void Init();
	void PlayerColBox(int num, Player* playe, Comment* coomment, Item* item, Enemy* enemy);
	void EnemyColBox(Enemy* enemy);
};


