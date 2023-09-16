#pragma once


//------------------------------------//
//プレイヤー変数・関数
//------------------------------------//
const int FIRST_PLAYER_POSITION_X = 1300;										//プレイヤーの初期X座標
const int FIRST_PLAYER_POSITION_Y = 400;										//プレイヤーの初期Y座標
const int FIRST_PLAYER_SPEED = 6;												//プレイヤーの初期速度
const int PW = 32;																//プレイヤーの幅(48/1.5)
const int PH = 42;																//プレイヤーの高さ(64/1.5)

class Player
{
public:
	//..................画像処理.................//
	int Img;																	//プレイヤー画像
	int ImgNum = 0;																//画像番号
	int WalkSound;																//足音
	bool isSoundFlag = false;													//足音のフラグ
	int Normal;																	//プレイヤー待機画像
	int NormalUp;																//プレイヤー待機画像(上)
	int NormalDown;																//プレイヤー待機画像(下)
	int Walk[12];																//プレイヤー移動アニメーション
	int WalkUp[8];																//プレイヤー移動アニメーション(上)
	int WalkDown[8];															//プレイヤー移動アニメーション(下)
	int Timer;																	//プレイヤーのアニメーションタイマー
	int Frame12;																//12コマのアニメーションフレーム
	int Frame8;																	//8コマのアニメーションフレーム
	bool Reverse = false;														//プレイヤー反転

	//..................移動処理.................//
	int X;																		//プレイヤーX座標
	int Y;																		//プレイヤーY座標
	int Speed;																	//プレイヤー速度
	bool player=false;																//操作フラグ

	void Init();
	void Load();
	void Main();
	void Draw();
	void GetX(int Gx);
	void SetX(int Sx);
	void GetY(int Gy);
	void SetY(int Sy);
};

