#include"DxLib.h"
#include "Item.h"

FILE* Tfp;
Item::Item()
{
	//------------------------------------//
	//ファイル読み込み
	//------------------------------------//
	LoadDivGraph("HageImg/Item.png", 8, 8, 1, 64, 64, ItemImg);
	LoadDivGraph("HageImg/collisioncheck.png", 6, 6, 1,
		ITEM_TILE_WIDTH, ITEM_TILE_HEIGHT, BoxHandle);			//タイル画像を読み込む

	fopen_s(&Tfp, FileName, "r");								//fopen_s関数でcsvファイルを読み取り形式で開く
	if (Tfp == NULL)											//filePointerが空の場合は
	{
		DebugBreak();											//デバッグを中止する
	}

	memset(Buffer, 0, sizeof(Buffer));							//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

	while (1)
	{
		while (1)
		{
			Marker = fgetc(Tfp);								//fgetc関数でfilepointerから文字を読んでMarkerに格納
			if (Marker == EOF)
			{
				EofFlag = true;									//EndOfFileを検出して
				break;											//ループを抜ける
			}
			if (Marker != ',' && Marker != '\n')				//区切りか改行でない場合
			{
				strcat_s(Buffer, (const char*)&Marker);			//strcat_s関数でbufferに連結し、const char関数で書き換える
			}
			else
			{
				Num = atoi(Buffer);								//atoi関数でbufferをint型に直して、ローカル変数numに代入する
				cell[ColumnNum][RawNum] = BoxHandle[Num];		//num番目のチップ画像のハンドルを取得
				memset(Buffer, 0, sizeof(Buffer));				//bufferをリセット
				break;											//区切りか改行なのでループを抜ける
			}
		}
		if (EofFlag)											//1マップ分になったら
		{
			RawNum = 0;											//行を初期化する
			break;												//ループを抜ける
		}
		if (Marker == ',')										//区切りを検出したら
		{
			ColumnNum++;										//列の数を増やす
		}
		if (Marker == '\n')										//改行だったら
		{
			RawNum++;											//行を増やす
			ColumnNum = 0;										//列を初期化する
		}
	}
	fclose(Tfp);												//ファイルを閉じる

}


Item::~Item()
{
	//デストラクターには何も書かない
}

void Item::Init()
{
	ItemNum = 0;
	PicUpSound = LoadSoundMem("HageSound/PickUp.mp3");
}

void Item::ItemBox(int num,int num2,Player* player,Enemy*enemy,Comment* comment)
{
	//------------------------------------//
	//当たり判定
	//------------------------------------//
	//プレイヤー左上右下座標//
	int PlayerLX = player->X - PW;
	int PlayerLY = player->Y - PH / 4;
	int PlayerRX = player->X + PW;
	int PlayerRY = player->Y + PH;

	//左上右下添え字//
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

			//ブロック左上右下座標//
			int blockLX = ix * ITEM_TILE_WIDTH;
			int blockLY = iy * ITEM_TILE_HEIGHT;
			int blockRX = blockLX + ITEM_TILE_WIDTH;
			int blockRY = blockLY + ITEM_TILE_HEIGHT;


			// 衝突したのでめり込みを戻す（リアクション）
			int dx1 = blockLX - PlayerRX;
			int dx2 = blockRX - PlayerLX;
			int dy1 = blockLY - PlayerRY;
			int dy2 = blockRY - PlayerLY;

			int dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
			int dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;

			if (ItemFlag)
			{
				// そこはブロックか？
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
			
				// そこはブロックか？
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



