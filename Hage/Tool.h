#pragma once


//------------------------------------//
//�}�b�v�ϐ��E�֐�
//------------------------------------//
#define TILE_WIDTH 64															//�^�C���̕�
#define TILE_HEIGHT 64															//�^�C���̍���
#define TILE_NUM_X 900															//�^�C���̉������̐�
#define TILE_NUM_Y 17															//�^�C���̏c�����̐�
#define WINDOW_X 1920
#define WINDOW_Y 1080

class Tool
{
public:
const char* ToolFileName = "Tool.csv";
	int Handle[8];										//�^�C���G�̑���
	int Width;
	int Height;
	int TileX;																		//�w�i�摜�̍��WX
	int TileY;
	int Pack;																	//�������i�[����ϐ�
	int RawNum = 0;																//�������̃^�C���i���o�[
	int ColumnNum = 0;															//�c�����̃^�C���i���o�[
	int i;																		//for���J�E���^�[
	int j;
	int Num;																	//�^�C���ԍ�
	char Buffer[10];															//������ϐ�
	bool EofFlag = false;														//eof���o�t���O
	int ToolCell[TILE_NUM_X][TILE_NUM_Y];															//�^�C���p�\����
	Tool();
	~Tool();
	void View(int num,int num2);
};

