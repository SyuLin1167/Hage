#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Comment.h"

//------------------------------------//
//コリジョン変数・関数
//------------------------------------//
#define ITEM_TILE_WIDTH 64													//タイルの幅
#define ITEM_TILE_HEIGHT 64													//タイルの高さ
#define ITEM_TILE_NUM_X 90													//横のタイル数
#define ITEM_TILE_NUM_Y 18													//縦のタイル数
#define ITEM_WINDOW_X 1920													//ウィンドウの幅
#define ITEM_WINDOW_Y 1080													//ウィンドウの高さ

class Item
{
public:
	//..............ファイル読み込み.............//
	const char* FileName = "Item.csv";										//読み込みファイル
	int BoxHandle[6];														//画像ハンドル
	int Marker;																//マーカー
	int RawNum = 0;															//行
	int ColumnNum = 0;														//列
	int Num;																//ハンドル番号
	char Buffer[10];														//バッファー
	bool EofFlag = false;													//Eofフラグ
	int cell[ITEM_TILE_NUM_X][ITEM_TILE_NUM_Y];								//縦と横のマップチップ数

	//..............当たり判定処理..............//
	bool Reverse;
	bool ItemFlag = false;
	int ItemImg[8];
	int ItemNum=0;
	int PicUpSound;


	Item();
	~Item();
	void Init();
	void ItemBox(int num,int num2,Player* playe,Enemy*enemy,Comment* comment);
};

