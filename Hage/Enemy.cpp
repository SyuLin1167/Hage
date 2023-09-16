#include"DxLib.h"
#include "Enemy.h"

//------------------------------------//
//エネミー初期化
//------------------------------------//
void Enemy::Init()
{
	X = FIRST_ENEMY_POSITION_X;																//初期位置X座標
	Y = FIRST_ENEMY_POSITION_Y;																//初期位置Y座標
	Speed = FIRST_ENEMY_SPEED;																//初期速度
	enemy = false;
	DrawFlag = false;
	Img = Normal;
}

//------------------------------------//
//エネミー読み込み
//------------------------------------//
void Enemy::Load()
{
	//待機画像読み込み//
	Normal=LoadGraph("HageImg/Enemy/HageWalkUp.png");

	//移動画像分割読み込み//
	Walk=LoadGraph("HageImg/Enemy/HageWalk.png");
	WalkUp=LoadGraph("HageImg/Enemy/HageWalkUp.png");
	WalkDown=LoadGraph("HageImg/Enemy/HageWalkDown.png");

	RunBgm = LoadSoundMem("HageSound/RunBgm.mp3");
}

//------------------------------------//
//エネミールーチン
//------------------------------------//
void Enemy::Main(Player* player,Game*game)
{
	Img = Normal;
	if (enemy)
	{
		int CenterX = X + EW / 2;														//エネミーX座標の中心
		int CenterY = Y + EH / 2;														//エネミーY座標の中心
		int PlayerCenterX = player->X + PW / 2;											//プレイヤーX座標の中心
		int PlayerCenterY = player->Y + PH / 2;											//プレイヤーY座標の中心
	
		if (Num == 1)
		{
			Img = Walk;
			(abs(CenterX) < abs(PlayerCenterX)) ? X += FIRST_ENEMY_SPEED : X -= FIRST_ENEMY_SPEED;
			(abs(CenterX) < abs(PlayerCenterX)) ? Reverse = true : Reverse = false;
		}
		if (Num == -1)
		{
			(abs(CenterY) < abs(PlayerCenterY)) ? Y += FIRST_ENEMY_SPEED : Y -= FIRST_ENEMY_SPEED;
			(abs(CenterY) < abs(PlayerCenterY)) ? Img = WalkDown : Img = WalkUp;
		}
		(abs(CenterX - PlayerCenterX) < abs(CenterY - PlayerCenterY)) ? Num = -1 : Num = 1;
		///プレイヤーとの当たり判定///
		if (X - EW / 2 < player->X + PW / 2 && X + EW / 2 > player->X - PW / 2
			&& Y + EH > player->Y - PH / 4 && Y - EH / 4 < player->Y + PH)
		{
			StopSoundMem(RunBgm);
			StopSoundMem(player->WalkSound);
			game->Status = OVER;
		}
		if (!isSoundFlag)
		{
			PlaySoundMem(RunBgm, DX_PLAYTYPE_LOOP);
			isSoundFlag = true;
		}
	}
	else
	{
		StopSoundMem(RunBgm);
		isSoundFlag = false;
	}
}

//------------------------------------//
//エネミー描画
//------------------------------------//
void Enemy::Draw()
{
	if (DrawFlag)
	{
		DrawRotaGraph(X, Y, 1.5f, 0, Img, TRUE, Reverse);										//エネミー描画
	}
}

//------------------------------------//
//エネミー左上右下座標
//------------------------------------//
//....................左上...................//
void Enemy::GetX(int Gx)
{
	X = Gx;
}
void Enemy::SetX(int Sx)
{
	X += Sx;
}
//....................右下...................//
void Enemy::GetY(int Gy)
{
	Y = Gy;
}
void Enemy::SetY(int Sy)
{
	Y += Sy;
}
