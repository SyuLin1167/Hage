#pragma once

//------------------------------------//
// ”wŒi•Ï”EŠÖ”
// -----------------------------------//
#define BackGroundNum 5
#define BackGroundNum2 2

const int FIRST_BACKGROUND_X = 0;
const int FIRST_BACKGROUND_Y = 0;

class BackGround
{
public:
	const char* Filename;
	int Filenum = 1;
	int Img;
	int X;
	int Y;

	void Init();
	void Load();
	void Main(int num,int num2);
	void Draw(int num,int num2);
};