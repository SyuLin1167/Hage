#include"DxLib.h"
#include "Item.h"

FILE* Tfp;
Item::Item()
{
	//------------------------------------//
	//�t�@�C���ǂݍ���
	//------------------------------------//
	LoadDivGraph("HageImg/Item.png", 8, 8, 1, 64, 64, ItemImg);
	LoadDivGraph("HageImg/collisioncheck.png", 6, 6, 1,
		ITEM_TILE_WIDTH, ITEM_TILE_HEIGHT, BoxHandle);			//�^�C���摜��ǂݍ���

	fopen_s(&Tfp, FileName, "r");								//fopen_s�֐���csv�t�@�C����ǂݎ��`���ŊJ��
	if (Tfp == NULL)											//filePointer����̏ꍇ��
	{
		DebugBreak();											//�f�o�b�O�𒆎~����
	}

	memset(Buffer, 0, sizeof(Buffer));							//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

	while (1)
	{
		while (1)
		{
			Marker = fgetc(Tfp);								//fgetc�֐���filepointer���當����ǂ��Marker�Ɋi�[
			if (Marker == EOF)
			{
				EofFlag = true;									//EndOfFile�����o����
				break;											//���[�v�𔲂���
			}
			if (Marker != ',' && Marker != '\n')				//��؂肩���s�łȂ��ꍇ
			{
				strcat_s(Buffer, (const char*)&Marker);			//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
			}
			else
			{
				Num = atoi(Buffer);								//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ������
				cell[ColumnNum][RawNum] = BoxHandle[Num];		//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
				memset(Buffer, 0, sizeof(Buffer));				//buffer�����Z�b�g
				break;											//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
			}
		}
		if (EofFlag)											//1�}�b�v���ɂȂ�����
		{
			RawNum = 0;											//�s������������
			break;												//���[�v�𔲂���
		}
		if (Marker == ',')										//��؂�����o������
		{
			ColumnNum++;										//��̐��𑝂₷
		}
		if (Marker == '\n')										//���s��������
		{
			RawNum++;											//�s�𑝂₷
			ColumnNum = 0;										//�������������
		}
	}
	fclose(Tfp);												//�t�@�C�������

}


Item::~Item()
{
	//�f�X�g���N�^�[�ɂ͉��������Ȃ�
}

void Item::Init()
{
	ItemNum = 0;
	PicUpSound = LoadSoundMem("HageSound/PickUp.mp3");
}

void Item::ItemBox(int num,int num2,Player* player,Enemy*enemy,Comment* comment)
{
	//------------------------------------//
	//�����蔻��
	//------------------------------------//
	//�v���C���[����E�����W//
	int PlayerLX = player->X - PW;
	int PlayerLY = player->Y - PH / 4;
	int PlayerRX = player->X + PW;
	int PlayerRY = player->Y + PH;

	//����E���Y����//
	int idLX = PlayerLX / ITEM_TILE_WIDTH;
	int idLY = PlayerLY / ITEM_TILE_HEIGHT;
	int idRX = PlayerRX / ITEM_TILE_WIDTH;
	int idRY = PlayerRY / ITEM_TILE_HEIGHT;


	if (idLY < 0 || idRY < 0)
	{
		return;
	}

	for (int iy = idLY; iy < idRY + 1; iy++)
	{
		for (int ix = idLX; ix < idRX + 1; ix++)
		{

			//�u���b�N����E�����W//
			int blockLX = ix * ITEM_TILE_WIDTH;
			int blockLY = iy * ITEM_TILE_HEIGHT;
			int blockRX = blockLX + ITEM_TILE_WIDTH;
			int blockRY = blockLY + ITEM_TILE_HEIGHT;


			// �Փ˂����̂ł߂荞�݂�߂��i���A�N�V�����j
			int dx1 = blockLX - PlayerRX;
			int dx2 = blockRX - PlayerLX;
			int dy1 = blockLY - PlayerRY;
			int dy2 = blockRY - PlayerLY;

			int dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
			int dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;

			if (ItemFlag)
			{
				// �����̓u���b�N���H
				if (cell[ix][iy] == BoxHandle[1])
				{

					if (CheckHitKey(KEY_INPUT_SPACE)|| CheckHitKey(KEY_INPUT_RETURN))
					{
						PlaySoundMem(PicUpSound, DX_PLAYTYPE_BACK);
						ItemNum++;
						ItemFlag = false;
						comment->CommentFlag = true;
						WaitTimer(300);
					}
					
				}
			
				// �����̓u���b�N���H
				if (cell[ix][iy] == BoxHandle[2]&&!player->player)
				{
					if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN))
					{
						if (enemy->enemy&&ItemNum<3)
						{
							ItemNum++;
						}
						ItemFlag = false;
						player->player = true;
						if (!enemy->DrawFlag)
						{
							enemy->enemy = false;
						}
						WaitTimer(300);
					}
				}
				
			}
		}
		if (ItemFlag)
		{
			switch (num2)
			{
			case 0:
				if (num == 0)
				{
					DrawRotaGraph(10 * ITEM_TILE_WIDTH + 32, 7 * ITEM_TILE_HEIGHT, 1, 0, ItemImg[player->Frame8], TRUE, Reverse);
				}
				if (num == 2)
				{
					DrawRotaGraph(17 * ITEM_TILE_WIDTH + 32, 7 * ITEM_TILE_HEIGHT, 1, 0, ItemImg[player->Frame8], TRUE, Reverse);
				}
				if (num == 4)
				{
					DrawRotaGraph(11 * ITEM_TILE_WIDTH + 32, 10 * ITEM_TILE_HEIGHT, 1, 0, ItemImg[player->Frame8], TRUE, Reverse);
				}
				break;
			case 1:
				if (num == 0)
				{
					DrawRotaGraph(10 * ITEM_TILE_WIDTH + 32, 7 * ITEM_TILE_HEIGHT, 1, 0, ItemImg[player->Frame8], TRUE, Reverse);
				}
				break;
			}
		}
		else if (player->player)
		{
			if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN))
			{
				ItemFlag = true;
				player->player = false;
				WaitTimer(300);
			}
			
		}
	}

}



