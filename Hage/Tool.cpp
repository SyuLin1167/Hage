#include"DxLib.h"
#include"Tool.h"
#include"Collision.h"


	FILE* fp;																					//ファイルのポインタを宣言
	Tool::Tool()
	{

			LoadDivGraph("HageImg/Tool.png", 8, 8, 1, 64, 64, Handle);	//タイル画像を読み込む
			fopen_s(&fp, ToolFileName, "r");																//fopen_s関数でTool.csvを読み取り形式で開く
			if (fp == NULL)																			//filePointerが空の場合は
			{
				DebugBreak();																					//デバッグ中止
			}

			memset(Buffer, 0, sizeof(Buffer));																	//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

			while (1)
			{
				while (1)
				{
					Pack = fgetc(fp);										//fgetc関数でfilepointerから文字を読んでcharacterPackに格納
					if (Pack == EOF)
					{
						EofFlag = true;														//EndOfFileを検出して
						break;																//ループを抜ける
					}
					if (Pack != ',' && Pack != '\n')						//区切りか改行でなければ
					{
						strcat_s(Buffer, (const char*)&Pack);						//strcat_s関数でbufferに連結し、const char関数で書き換える
					}
					else
					{
						Num = atoi(Buffer);													//atoi関数でbufferをint型に直して、ローカル変数numに代入
						ToolCell[ColumnNum][RawNum] = Handle[Num];		//num番目のチップ画像のハンドルを取得
						memset(Buffer, 0, sizeof(Buffer));									//bufferをリセット
						break;																//区切りか改行なのでループを抜ける
					}
				}
				if (EofFlag)																//1マップ分になったら
				{
					break;																	//ループを抜ける
				}
				if (Pack == ',')													//区切りを検出したら
				{
					ColumnNum++;															//列の数を増やす
				}
				if (Pack == '\n')													//改行だったら
				{
					RawNum++;																//行を増やす
					ColumnNum = 0;															//列を0にする
				}
			}
			fclose(fp);															//ファイルを閉じる

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

