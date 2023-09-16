#include"DxLib.h"
#include"BackGround.h"

BackGround BackGroundFile[BackGroundNum2][BackGroundNum];
void BackGround::Init()
{
	X = FIRST_BACKGROUND_X;
	Y = FIRST_BACKGROUND_Y;
}

void BackGround::Load()
{
	BackGroundFile[0][0].Filename = "HageImg/Map/ClassRoom.png";
	BackGroundFile[0][1].Filename = "HageImg/Map/Corridor1.png";
	BackGroundFile[0][2].Filename = "HageImg/Map/Floor.png";
	BackGroundFile[0][3].Filename = "HageImg/Map/Corridor2.png";
	BackGroundFile[0][4].Filename = "HageImg/Map/Floor2.png";
	BackGroundFile[1][0].Filename = "HageImg/Map/Entrance.png";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			BackGroundFile[i][j].Img = LoadGraph(BackGroundFile[i][j].Filename);
		}
	}
}

void BackGround::Main(int num,int num2)
{
	BackGroundFile[num][num2].Img;
}

void BackGround::Draw(int num,int num2)
{
	DrawGraph(X, Y, BackGroundFile[num][num2].Img, TRUE);
}