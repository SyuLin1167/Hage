#pragma once
#include"Player.h"
#include"Seen.h"

//------------------------------------//
//�G�l�~�[�ϐ��E�֐�
//------------------------------------//
const int FIRST_ENEMY_POSITION_X = 1000;										//�G�l�~�[�̏���X���W
const int FIRST_ENEMY_POSITION_Y = 750;											//�G�l�~�[�̏���Y���W
const int FIRST_ENEMY_SPEED = 5;												//�G�l�~�[�̏������x
const int EW = 32;																//�G�l�~�[�̕�(48/1.5)
const int EH = 42;																//�G�l�~�[�̍���(62/1.5)

class Enemy
{
public:
	//..................�摜����.................//
	int Img;																	//�G�l�~�[�摜
	int Normal;																	//�G�l�~�[�ҋ@�摜
	int Walk;																	//�G�l�~�[�ړ��摜
	int WalkUp;																	//�G�l�~�[�ړ��摜(��)
	int WalkDown;																//�G�l�~�[�ړ��摜(��)
	bool Reverse = false;														//�G�l�~�[���]
	bool DrawFlag = false;														//�G�l�~�[�`��t���O
	int RunBgm;
	bool isSoundFlag = false;

	//..................�ړ�����.................//
	int X;																		//�G�l�~�[X���W
	int Y;																		//�G�l�~�[Y���W
	int Speed;																	//�G�l�~�[���x
	int Num = -1;																//�G�l�~�[�ԍ�
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

