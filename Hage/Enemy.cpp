#include"DxLib.h"
#include "Enemy.h"

//------------------------------------//
//�G�l�~�[������
//------------------------------------//
void Enemy::Init()
{
	X = FIRST_ENEMY_POSITION_X;																//�����ʒuX���W
	Y = FIRST_ENEMY_POSITION_Y;																//�����ʒuY���W
	Speed = FIRST_ENEMY_SPEED;																//�������x
	enemy = false;
	DrawFlag = false;
	Img = Normal;
}

//------------------------------------//
//�G�l�~�[�ǂݍ���
//------------------------------------//
void Enemy::Load()
{
	//�ҋ@�摜�ǂݍ���//
	Normal=LoadGraph("HageImg/Enemy/HageWalkUp.png");

	//�ړ��摜�����ǂݍ���//
	Walk=LoadGraph("HageImg/Enemy/HageWalk.png");
	WalkUp=LoadGraph("HageImg/Enemy/HageWalkUp.png");
	WalkDown=LoadGraph("HageImg/Enemy/HageWalkDown.png");

	RunBgm = LoadSoundMem("HageSound/RunBgm.mp3");
}

//------------------------------------//
//�G�l�~�[���[�`��
//------------------------------------//
void Enemy::Main(Player* player,Game*game)
{
	Img = Normal;
	if (enemy)
	{
		int CenterX = X + EW / 2;														//�G�l�~�[X���W�̒��S
		int CenterY = Y + EH / 2;														//�G�l�~�[Y���W�̒��S
		int PlayerCenterX = player->X + PW / 2;											//�v���C���[X���W�̒��S
		int PlayerCenterY = player->Y + PH / 2;											//�v���C���[Y���W�̒��S
	
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
		///�v���C���[�Ƃ̓����蔻��///
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
//�G�l�~�[�`��
//------------------------------------//
void Enemy::Draw()
{
	if (DrawFlag)
	{
		DrawRotaGraph(X, Y, 1.5f, 0, Img, TRUE, Reverse);										//�G�l�~�[�`��
	}
}

//------------------------------------//
//�G�l�~�[����E�����W
//------------------------------------//
//....................����...................//
void Enemy::GetX(int Gx)
{
	X = Gx;
}
void Enemy::SetX(int Sx)
{
	X += Sx;
}
//....................�E��...................//
void Enemy::GetY(int Gy)
{
	Y = Gy;
}
void Enemy::SetY(int Sy)
{
	Y += Sy;
}
