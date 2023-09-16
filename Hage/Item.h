#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Comment.h"

//------------------------------------//
//�R���W�����ϐ��E�֐�
//------------------------------------//
#define ITEM_TILE_WIDTH 64													//�^�C���̕�
#define ITEM_TILE_HEIGHT 64													//�^�C���̍���
#define ITEM_TILE_NUM_X 90													//���̃^�C����
#define ITEM_TILE_NUM_Y 18													//�c�̃^�C����
#define ITEM_WINDOW_X 1920													//�E�B���h�E�̕�
#define ITEM_WINDOW_Y 1080													//�E�B���h�E�̍���

class Item
{
public:
	//..............�t�@�C���ǂݍ���.............//
	const char* FileName = "Item.csv";										//�ǂݍ��݃t�@�C��
	int BoxHandle[6];														//�摜�n���h��
	int Marker;																//�}�[�J�[
	int RawNum = 0;															//�s
	int ColumnNum = 0;														//��
	int Num;																//�n���h���ԍ�
	char Buffer[10];														//�o�b�t�@�[
	bool EofFlag = false;													//Eof�t���O
	int cell[ITEM_TILE_NUM_X][ITEM_TILE_NUM_Y];								//�c�Ɖ��̃}�b�v�`�b�v��

	//..............�����蔻�菈��..............//
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

