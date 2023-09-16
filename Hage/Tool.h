#pragma once


//------------------------------------//
//マップ変数・関数
//------------------------------------//
#define TILE_WIDTH 64															//タイルの幅
#define TILE_HEIGHT 64															//タイルの高さ
#define TILE_NUM_X 900															//タイルの横方向の数
#define TILE_NUM_Y 17															//タイルの縦方向の数
#define WINDOW_X 1920
#define WINDOW_Y 1080

class Tool
{
public:
const char* ToolFileName = "Tool.csv";
	int Handle[8];										//タイル絵の総数
	int Width;
	int Height;
	int TileX;																		//背景画像の座標X
	int TileY;
	int Pack;																	//文字を格納する変数
	int RawNum = 0;																//横方向のタイルナンバー
	int ColumnNum = 0;															//縦方向のタイルナンバー
	int i;																		//for文カウンター
	int j;
	int Num;																	//タイル番号
	char Buffer[10];															//文字列変数
	bool EofFlag = false;														//eof検出フラグ
	int ToolCell[TILE_NUM_X][TILE_NUM_Y];															//タイル用構造体
	Tool();
	~Tool();
	void View(int num,int num2);
};

