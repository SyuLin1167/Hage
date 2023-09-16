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
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "�����������Ă���");				//���_�\��
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
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "����H\n�܂��N�����ĂȂ��H");				//���_�\��
				}
				break;
			case 1:
				if (num2 == 0)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "�p��̃J�M����ɓ��ꂽ");				//���_�\��
				}
				break;
			case 3:
				if (num2 == 0)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "���K���̃J�M����ɓ��ꂽ");				//���_�\��
				}
				break;
			case 4:
				if (num2 == 4)
				{
					DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "���ʌ��ւ̃J�M����ɓ��ꂽ");				//���_�\��
				}
				break;
			}
			if (num2 == 3)
			{
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "............����...�H\n����.......����.......�H");				//���_�\��
			}
			if (num1 > 4)
			{
				DrawFormatString(TextX, TextY, GetColor(255, 255, 255), "�������͍Z�ɂ̊O�܂ł͒ǂ��Ă��Ȃ�����...�B\n���ꂩ��A�����Ȃ��������̂悤�ɓ��퐶�����߂����Ă���...�B\n�A�������������̂�...���ł��킩��Ȃ��B");				//���_�\��
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


