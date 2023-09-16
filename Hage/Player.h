#pragma once


//------------------------------------//
//�v���C���[�ϐ��E�֐�
//------------------------------------//
const int FIRST_PLAYER_POSITION_X = 1300;										//�v���C���[�̏���X���W
const int FIRST_PLAYER_POSITION_Y = 400;										//�v���C���[�̏���Y���W
const int FIRST_PLAYER_SPEED = 6;												//�v���C���[�̏������x
const int PW = 32;																//�v���C���[�̕�(48/1.5)
const int PH = 42;																//�v���C���[�̍���(64/1.5)

class Player
{
public:
	//..................�摜����.................//
	int Img;																	//�v���C���[�摜
	int ImgNum = 0;																//�摜�ԍ�
	int WalkSound;																//����
	bool isSoundFlag = false;													//�����̃t���O
	int Normal;																	//�v���C���[�ҋ@�摜
	int NormalUp;																//�v���C���[�ҋ@�摜(��)
	int NormalDown;																//�v���C���[�ҋ@�摜(��)
	int Walk[12];																//�v���C���[�ړ��A�j���[�V����
	int WalkUp[8];																//�v���C���[�ړ��A�j���[�V����(��)
	int WalkDown[8];															//�v���C���[�ړ��A�j���[�V����(��)
	int Timer;																	//�v���C���[�̃A�j���[�V�����^�C�}�[
	int Frame12;																//12�R�}�̃A�j���[�V�����t���[��
	int Frame8;																	//8�R�}�̃A�j���[�V�����t���[��
	bool Reverse = false;														//�v���C���[���]

	//..................�ړ�����.................//
	int X;																		//�v���C���[X���W
	int Y;																		//�v���C���[Y���W
	int Speed;																	//�v���C���[���x
	bool player=false;																//����t���O

	void Init();
	void Load();
	void Main();
	void Draw();
	void GetX(int Gx);
	void SetX(int Sx);
	void GetY(int Gy);
	void SetY(int Sy);
};

