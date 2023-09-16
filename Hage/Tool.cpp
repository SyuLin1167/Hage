#include"DxLib.h"
#include"Tool.h"
#include"Collision.h"


	FILE* fp;																					//�t�@�C���̃|�C���^��錾
	Tool::Tool()
	{

			LoadDivGraph("HageImg/Tool.png", 8, 8, 1, 64, 64, Handle);	//�^�C���摜��ǂݍ���
			fopen_s(&fp, ToolFileName, "r");																//fopen_s�֐���Tool.csv��ǂݎ��`���ŊJ��
			if (fp == NULL)																			//filePointer����̏ꍇ��
			{
				DebugBreak();																					//�f�o�b�O���~
			}

			memset(Buffer, 0, sizeof(Buffer));																	//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

			while (1)
			{
				while (1)
				{
					Pack = fgetc(fp);										//fgetc�֐���filepointer���當����ǂ��characterPack�Ɋi�[
					if (Pack == EOF)
					{
						EofFlag = true;														//EndOfFile�����o����
						break;																//���[�v�𔲂���
					}
					if (Pack != ',' && Pack != '\n')						//��؂肩���s�łȂ����
					{
						strcat_s(Buffer, (const char*)&Pack);						//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
					}
					else
					{
						Num = atoi(Buffer);													//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ��
						ToolCell[ColumnNum][RawNum] = Handle[Num];		//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
						memset(Buffer, 0, sizeof(Buffer));									//buffer�����Z�b�g
						break;																//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
					}
				}
				if (EofFlag)																//1�}�b�v���ɂȂ�����
				{
					break;																	//���[�v�𔲂���
				}
				if (Pack == ',')													//��؂�����o������
				{
					ColumnNum++;															//��̐��𑝂₷
				}
				if (Pack == '\n')													//���s��������
				{
					RawNum++;																//�s�𑝂₷
					ColumnNum = 0;															//���0�ɂ���
				}
			}
			fclose(fp);															//�t�@�C�������

	}

	Tool::~Tool()
	{

	}

	void Tool::View(int num,int num2)
	{
		TileX =-WINDOW_X*num;
		TileY = -WINDOW_Y * num2;
		for (i = 0; i < TILE_NUM_X; i++)
		{
			for (j = 0; j < TILE_NUM_Y; j++)
			{
				DrawExtendGraph(i * TILE_WIDTH + TileX, j * TILE_HEIGHT + TileY, (i + 1) * TILE_WIDTH + TileX, (j + 1) * TILE_HEIGHT + TileY, ToolCell[i][j], TRUE);
			}
		}
	}

