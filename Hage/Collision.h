#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Comment.h"
#include"Item.h"

//------------------------------------//
//�R���W�����ϐ��E�֐�
//------------------------------------//
#define COLLISION_TILE_WIDTH 64													//�^�C���̕�
#define COLLISION_TILE_HEIGHT 64												//�^�C���̍���
#define COLLISION_TILE_NUM_X 150												//���̃^�C����
#define COLLISION_TILE_NUM_Y 36													//�c�̃^�C����
#define COLLISION_WINDOW_X 1920													//�E�B���h�E�̕�
#define COLLISION_WINDOW_Y 1080													//�E�B���h�E�̍���

class Collision
{
public:
	//..............�t�@�C���ǂݍ���.............//
	const char* FileName = "Collision.csv";										//�ǂݍ��݃t�@�C��
	int LockSound;																//�����������Ă���Ƃ��̃T�E���h
	int DoorSound;																//�������o���肷��Ƃ��̃T�E���h
	int BoxHandle[7];															//�摜�n���h��
	int Marker;																	//�}�[�J�[
	int RawNum = 0;																//�s
	int ColumnNum = 0;															//��
	int Num;																	//�n���h���ԍ�
	char Buffer[10];															//�o�b�t�@�[
	bool EofFlag = false;														//Eof�t���O
	int cell[COLLISION_TILE_NUM_X][COLLISION_TILE_NUM_Y];						//�c�Ɖ��̃}�b�v�`�b�v��

	//..............�����蔻�菈��..............//
	int FileNum;																//�t�@�C���ԍ�
	int FileNum2;																//�t�@�C���ԍ�����2
	int NumX_1;																	//X���W����1
	int NumY_1;																	//Y���W����1
	int NumX_2;																	//X���W����2
	int NumY_2;																	//Y���W����2
	int NumX_3;																	//X���W����3
	int NumY_3;																	//Y���W����3
	int NumX_4;																	//X���W����4
	int NumY_4;																	//Y���W����4

	Collision();
	~Collision();
	void Init();
	void PlayerColBox(int num, Player* playe, Comment* coomment, Item* item, Enemy* enemy);
	void EnemyColBox(Enemy* enemy);
};


