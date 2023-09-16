#include"DxLib.h"
#include"Player.h"

//------------------------------------//
//�v���C���[������
//------------------------------------//
void Player::Init()
{
	X =FIRST_PLAYER_POSITION_X;																//�����ʒuX���W
	Y =FIRST_PLAYER_POSITION_Y;																//�����ʒuY���W
	Speed = FIRST_PLAYER_SPEED;																//�������x
}

//------------------------------------//
//�v���C���[�ǂݍ���
//------------------------------------//
void Player::Load()
{
	//�ҋ@�摜�ǂݍ���//
	Normal = LoadGraph("HageImg/Player/PlayerNomal.png");
	NormalUp= LoadGraph("HageImg/Player/PlayerNomalUp.png");
	NormalDown= LoadGraph("HageImg/Player/PlayerNomalDown.png");

	//�ړ��摜�����ǂݍ���//
	LoadDivGraph("HageImg/Player/PlayerWalk.png", 12, 12, 1, 48, 64, Walk);
	LoadDivGraph("HageImg/Player/PlayerWalkUp.png", 8, 8, 1, 48, 64, WalkUp);
	LoadDivGraph("HageImg/Player/PlayerWalkDown.png", 8, 8, 1, 48, 64, WalkDown);

	WalkSound = LoadSoundMem("HageSound/Walk.mp3");
}

//------------------------------------//
//�v���C���[���[�`��
//------------------------------------//
void Player::Main()
{
	if (!player)
	{
		//--���ړ��Œ�~������--//
		if (ImgNum == 0)
		{
			Img = Normal;																		//�摜��ҋ@�摜(������)��
		}
		//--���ړ��Œ�~������--//
		if (ImgNum == 1)
		{
			Img = NormalDown;																	//�摜��ҋ@�摜(������)��
		}
		//--��ړ��Œ�~������--//
		if (ImgNum == 2)
		{
			Img = NormalUp;																		//�摜��ҋ@�摜(�����)��
		}

		///���L�[�������ꂽ��///
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Reverse = true;																		//�摜�͔��]
			Img = Walk[Frame12];																//�摜���ړ��摜��
			X += Speed;																			//�E�Ɉړ�����
			ImgNum = 0;
		}
		///���L�[�������ꂽ��///
		else if (CheckHitKey(KEY_INPUT_LEFT))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Reverse = false;																	//�摜�͔��]���Ȃ�
			Img = Walk[Frame12];																//�摜���ړ��摜��
			X -= Speed;																			//���Ɉړ�����
			ImgNum = 0;
		}
		///���L�[�������ꂽ��///
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Img = NormalDown;
			Img = WalkDown[Frame8];																//�摜���ړ��摜��
			Y += Speed;																			//���Ɉړ�����
			ImgNum = 1;
		}
		///���L�[�������ꂽ��///
		else if (CheckHitKey(KEY_INPUT_UP))
		{
			if (!isSoundFlag)
			{
				PlaySoundMem(WalkSound, DX_PLAYTYPE_LOOP);
				isSoundFlag = true;
			}
			Img = NormalUp;
			Img = WalkUp[Frame8];																//�摜���ړ��摜��
			Y -= Speed;																			//��Ɉړ�����
			ImgNum = 2;
		}
		///�ҋ@����///
		else
		{
			isSoundFlag = false;																//sound�t���O�𗧂ĂȂ�
			StopSoundMem(WalkSound);															//sound���~�߂�
		}
	}
}

//------------------------------------//
//�v���C���[�`��
//------------------------------------//
void Player::Draw()
{
	Timer = GetNowCount();																	//���ݎ������擾

	///�^�C�}�[��90�Ŋ����ăt���[�����Ŋ��邱�ƂŃR�}�����o��///
	Frame12 = Timer / 90 % 12;
	Frame8 = Timer / 90 % 8;
	if (!player)
	{
		DrawRotaGraph(X, Y, 1.5f, 0, Img, TRUE, Reverse);										//�v���C���[�`��
	}
}

//------------------------------------//
//�v���C���[����E�����W
//------------------------------------//
//....................����...................//
void Player::GetX(int Gx)
{
	X = Gx;
}
void Player::SetX(int Sx)
{
	X += Sx;
}
//....................�E��...................//
void Player::GetY(int Gy)
{
	Y = Gy;
}
void Player::SetY(int Sy)
{
	Y += Sy;
}


