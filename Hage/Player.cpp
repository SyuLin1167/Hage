#include"DxLib.h"
#include"Player.h"

//------------------------------------//
//プレイヤー初期化
//------------------------------------//
void Player::Init()
{
	X =FIRST_PLAYER_POSITION_X;																//初期位置X座標
	Y =FIRST_PLAYER_POSITION_Y;																//初期位置Y座標
	Speed = FIRST_PLAYER_SPEED;																//初期速度
}

//------------------------------------//
//プレイヤー読み込み
//------------------------------------//
void Player::Load()
{
	//待機画像読み込み//
	Normal = LoadGraph("HageImg/Player/PlayerNomal.png");
	NormalUp= LoadGraph("HageImg/Player/PlayerNomalUp.png");
	NormalDown= LoadGraph("HageImg/Player/PlayerNomalDown.png");

	//移動画像分割読み込み//
	LoadDivGraph("HageImg/Player/PlayerWalk.png", 12, 12, 1, 48, 64, Walk);
	LoadDivGraph("HageImg/Player/PlayerWalkUp.png", 8, 8, 1, 48, 64, WalkUp);
	LoadDivGraph("HageImg/Player/PlayerWalkDown.png", 8, 8, 1, 48, 64, WalkDown);

	WalkSound = LoadSoundMem("HageSound/Walk.mp3");
}

//------------------------------------//
//プレイヤールーチン
//------------------------------------//
void Player::Main()
{
	if (!player)
	{
		//--横移動で停止したら--//
		if (ImgNum == 0)
		{
			Img = Normal;																		//画像を待機画像(横向き)に
		}
		//--下移動で停止したら--//
		if (ImgNum == 1)
		{
			Img = NormalDown;																	//画像を待機画像(下向き)に
		}
		//--上移動で停止したら--//
		if (ImgNum == 2)
		{
			Img = NormalUp;																		//画像を待機画像(上向き)に
		}

		///→キーが押されたら///
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Reverse = true;																		//画像は反転
			Img = Walk[Frame12];																//画像を移動画像に
			X += Speed;																			//右に移動する
			ImgNum = 0;
		}
		///←キーが押されたら///
		else if (CheckHitKey(KEY_INPUT_LEFT))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Reverse = false;																	//画像は反転しない
			Img = Walk[Frame12];																//画像を移動画像に
			X -= Speed;																			//左に移動する
			ImgNum = 0;
		}
		///↓キーが押されたら///
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Img = NormalDown;
			Img = WalkDown[Frame8];																//画像を移動画像に
			Y += Speed;																			//下に移動する
			ImgNum = 1;
		}
		///↑キーが押されたら///
		else if (CheckHitKey(KEY_INPUT_UP))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Img = NormalUp;
			Img = WalkUp[Frame8];																//画像を移動画像に
			Y -= Speed;																			//上に移動する
			ImgNum = 2;
		}
		///待機中は///
		else
		{
			isSoundFlag = false;																//soundフラグを立てない
			StopSoundMem(WalkSound);															//soundを止める
		}
	}
}

//------------------------------------//
//プレイヤー描画
//------------------------------------//
void Player::Draw()
{
	Timer = GetNowCount();																	//現在時刻を取得

	///タイマーを90で割ってフレーム数で割ることでコマ数を出す///
	Frame12 = Timer / 90 % 12;
	Frame8 = Timer / 90 % 8;
	if (!player)
	{
		DrawRotaGraph(X, Y, 1.5f, 0, Img, TRUE, Reverse);										//プレイヤー描画
	}
}

//------------------------------------//
//プレイヤー左上右下座標
//------------------------------------//
//....................左上...................//
void Player::GetX(int Gx)
{
	X = Gx;
}
void Player::SetX(int Sx)
{
	X += Sx;
}
//....................右下...................//
void Player::GetY(int Gy)
{
	Y = Gy;
}
void Player::SetY(int Sy)
{
	Y += Sy;
}


