#pragma once
//------------------------------------//
// ŠÂ‹«•Ï”
// -----------------------------------//

const int Window_Width = 1920;
const int Window_Height = 1080;
const int Color_Depth = 32;
const int Img_X = 0;
const int Img_Y = 0;
const int SelectNum = 12;

class Game
{
public:
	int Status;
	int TitleImg;
	int TitleBgm;
	int SelectImg;
	int SelectSound;
	int SelectY = 101;
	int EnterSound;
	int OverImg;
	int ClearImg;

	void Load();
	void Init();
	void Title();
	void Over();
	void Clear();
};


enum
{
	INIT,SAVE,TITLE,PLAY,QUIT,OVER,CLEAR
};
