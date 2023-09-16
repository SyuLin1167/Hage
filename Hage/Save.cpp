#include"DxLib.h"
#include "Save.h"

void Save::Load()
{
	SaveImg= LoadGraph("HageImg/Menu.png");
	SelectImg = LoadGraph("HageImg/Select.png");
	EscSound = LoadSoundMem("HageSound/EscapeSound.mp3");
}

void Save::GameSave(Game* game, Player* player, Enemy* enemy, Collision* collision, Item* item,Comment*comment)
{

	if (save)
	{
		DrawGraph(ImgX, ImgY, SaveImg, TRUE);													//îwåiï\é¶
		DrawGraph(53, SelectY, SelectImg, TRUE);	//îwåiï\é¶


		if (CheckHitKey(KEY_INPUT_DOWN) && SelectY < 179)
		{
			PlaySoundMem(game->SelectSound, DX_PLAYTYPE_BACK);
			SelectY += Select_Num;
		}
		if (CheckHitKey(KEY_INPUT_UP) && SelectY > 35)
		{
			PlaySoundMem(game->SelectSound, DX_PLAYTYPE_BACK);
			SelectY -= Select_Num;
		}
		if (CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_SPACE))
		{
			if (SelectY == 35)
			{
				PlaySoundMem(EscSound, DX_PLAYTYPE_BACK);
				save = false;
			}
			else if (SelectY == 179)
			{
				PlaySoundMem(game->EnterSound, DX_PLAYTYPE_BACK);
				save = false;
				game->Status = INIT;
			}
			else
			{
				PlaySoundMem(game->EnterSound, DX_PLAYTYPE_BACK);
				PlayerX = player->X;
				PlayerY = player->Y;
				EnemyX = enemy->X;
				EnemyY = enemy->Y;
				EnemyFlag = enemy->enemy;
				EnemyDrawFlag = enemy->DrawFlag;
				FileNum = collision->FileNum;
				FileNum2 = collision->FileNum2;
				ItemNum = item->ItemNum;
				CommentFlag = comment->CommentFlag;
			}
		}
		WaitTimer(100);
	}
}

void Save::LoadData(Game* game, Player* player, Enemy* enemy, Collision* collision, Item* item,Comment*comment)
{
	player->X = PlayerX;
	player->Y = PlayerY;
	enemy->X = EnemyX;
	enemy->Y=EnemyY;
	enemy->enemy = EnemyFlag;
	enemy->DrawFlag=EnemyDrawFlag;
	collision->FileNum=FileNum;
	collision->FileNum2=FileNum2;
	item->ItemNum = ItemNum;
	comment->CommentFlag = CommentFlag;

	game->Status = PLAY;
}