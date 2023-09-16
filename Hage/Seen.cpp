#include"DxLib.h"
#include"Seen.h"

void Game::Load()
{
	TitleImg = LoadGraph("HageImg/Title.png");
	SelectImg = LoadGraph("HageImg/Select.png");
	OverImg = LoadGraph("HageImg/GameOver.png");
	ClearImg = LoadGraph("HageImg/GameClear.png");
	TitleBgm = LoadSoundMem("HageSound/HageBgm.mp3");
	SelectSound= LoadSoundMem("HageSound/SelectBgm.mp3");
	EnterSound= LoadSoundMem("HageSound/EnterBgm.mp3");
}

void Game::Init()
{
		PlaySoundMem(TitleBgm, DX_PLAYTYPE_LOOP);
}
void Game::Title()
{

	DrawGraph(Img_X, Img_Y, TitleImg, FALSE);													//îwåiï\é¶
	DrawGraph(SelectY/2, SelectY*8, SelectImg, TRUE);	//îwåiï\é¶
	

	if (CheckHitKey(KEY_INPUT_DOWN) && SelectY < 125)
	{
		PlaySoundMem(SelectSound, DX_PLAYTYPE_BACK);
		SelectY += SelectNum;
	}
	if (CheckHitKey(KEY_INPUT_UP) && SelectY > 101)
	{
		PlaySoundMem(SelectSound, DX_PLAYTYPE_BACK);
		SelectY -= SelectNum;
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		PlaySoundMem(EnterSound, DX_PLAYTYPE_BACK);
		StopSoundMem(TitleBgm);
		if (SelectY == 101)
		{
			Status = PLAY;
		}
		else if (SelectY == 125)
		{
			Status = QUIT;
		}
		else
		{
			Status = SAVE;
		}
	}
	WaitTimer(100);
}

void Game::Over()
{
	DrawGraph(Img_X, Img_Y, OverImg, FALSE);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		Status = INIT;
	}
}

void Game::Clear()
{
	DrawGraph(Img_X, Img_Y, ClearImg, FALSE);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		Status = INIT;
	}
}