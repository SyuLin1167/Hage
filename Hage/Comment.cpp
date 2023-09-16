#include"DxLib.h"
#include "Comment.h"

void Comment::Load()
{
	CommentImg = LoadGraph("HageImg/Comment.png");
}

void Comment::Init()
{
	CommentFlag = true;
}

void Comment::Main(int num1,int num2,Player*player,Enemy*enemy,Game*game)
{
	SetFontSize(24);
	if (CommentFlag)
	{
		DrawGraph(0, 825, CommentImg, TRUE);
		if (LockFlag)
		{
			if (num1 == num2)
			{
				LockFlag = false;
			}
			else
			{
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "鍵がかかっている");				//得点表示
			}
		}
		else
		{
			switch (num1)
			{
			case 0:

				if (num2 == 0)
				{
					player->Img = player->Normal;
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "あれ？\nまだ誰も来てない？");				//得点表示
				}
				break;
			case 1:
				if (num2 == 0)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "用具室のカギを手に入れた");				//得点表示
				}
				break;
			case 3:
				if (num2 == 0)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "自習室のカギを手に入れた");				//得点表示
				}
				break;
			case 4:
				if (num2 == 4)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "正面玄関のカギを手に入れた");				//得点表示
				}
				break;
			}
			if (num2 == 3)
			{
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "............あれ...？\n何か.......いる.......？");				//得点表示
			}
			if (num1 > 4)
			{
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "化け物は校舎の外までは追ってこなかった...。\nあれから、何もなかったかのように日常生活を過ごしている...。\nアレが何だったのか...今でもわからない。");				//得点表示
			}
		}

		if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN))
		{
			CommentFlag = false;
			LockFlag = false;
			if (enemy->DrawFlag)
			{
				enemy->enemy = true;
			}
			if (num1 > 4)
			{
				game->Status = CLEAR;
			}
		}
	}
}


