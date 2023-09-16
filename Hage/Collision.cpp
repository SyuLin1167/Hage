#include"DxLib.h"
#include"math.h"
#include"Collision.h"

FILE* Cfp;
Collision::Collision()
{
	//------------------------------------//
	//ファイル読み込み
	//------------------------------------//
	LoadDivGraph("HageImg/collisioncheck.png", 6, 6, 1,
		COLLISION_TILE_WIDTH, COLLISION_TILE_HEIGHT, BoxHandle);	//タイル画像を読み込む

	fopen_s(&Cfp, FileName, "r");								//fopen_s関数でcsvファイルを読み取り形式で開く
	if (Cfp == NULL)											//filePointerが空の場合は
	{
		DebugBreak();											//デバッグを中止する
	}

	memset(Buffer, 0, sizeof(Buffer));							//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

	while (1)
	{
		while (1)
		{
			Marker = fgetc(Cfp);								//fgetc関数でfilepointerから文字を読んでMarkerに格納
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
	fclose(Cfp);												//ファイルを閉じる

	//------------------------------------//
	//サウンド読み込み
	//------------------------------------//
	LockSound = LoadSoundMem("HageSound/LockSound.mp3");
	DoorSound = LoadSoundMem("HageSound/DoorSound.mp3");

}


Collision::~Collision()
{
																		//デストラクターには何も書かない

}
void Collision::Init()
{
	FileNum = 0;
	FileNum2 = 0;
}

void Collision::PlayerColBox(int num, Player* player, Comment* comment,Item*item,Enemy*enemy)
{

	//------------------------------------//
	//当たり判定
	//------------------------------------//
	//プレイヤー左上右下座標//
	int PlayerLX = (player->X - PW / 2) + COLLISION_WINDOW_X * FileNum;
	int PlayerLY = (player->Y + PH/4 ) + COLLISION_WINDOW_Y * FileNum2;
	int PlayerRX = (player->X + PW / 2) + COLLISION_WINDOW_X * FileNum;
	int PlayerRY = (player->Y + PH) + COLLISION_WINDOW_Y * FileNum2;

	//エネミー左上右下座標//
	int EnemyLX = (enemy->X - EW / 2) + COLLISION_WINDOW_X * FileNum;
	int EnemyLY = (enemy->Y - EH / 4) + COLLISION_WINDOW_Y * FileNum2;
	int EnemyRX = (enemy->X + EW / 2) + COLLISION_WINDOW_X * FileNum;
	int EnemyRY = (enemy->Y + EH) + COLLISION_WINDOW_Y * FileNum2;

	//左上右下添え字//
	int idLX = PlayerLX / COLLISION_TILE_WIDTH;
	int idLY = PlayerLY / COLLISION_TILE_HEIGHT;
	int idRX = PlayerRX / COLLISION_TILE_WIDTH;
	int idRY = PlayerRY / COLLISION_TILE_HEIGHT;

	int LenghX = (abs(PlayerRX - EnemyLX) > abs(EnemyRX - PlayerLX)) ? PlayerRX - EnemyLX : EnemyRX - PlayerLX;
	int LenghY = (abs(PlayerRY - EnemyLY) > abs(EnemyRY - PlayerLY)) ? PlayerRY - EnemyLY : EnemyRY - PlayerLY;

	if (idLY < 0 || idRY < 0)
	{
		return;
	}
	int DifferenceLengthX = player->X - enemy->X;										//プレイヤーとの距離
	int DifferenceLengthY = player->Y - enemy->Y;
	switch (FileNum)
	{
	case 0:
		abs(item->ItemNum) < abs(1) ? item->ItemFlag = true : item->ItemFlag = false;
		NumX_1 = -480;
		if (FileNum2 == 1)
		{
			abs(item->ItemNum) < abs(3) ? item->ItemFlag = true : item->ItemFlag = false;
			if (item->ItemNum == 4)
			{
				enemy->X = 800;
				enemy->Y = 800;
				enemy->DrawFlag = true;
				enemy->enemy = true;
				item->ItemNum = 5;
			}
		}
		break;
	case 1:
		NumX_1 = -480;
		NumY_1 = 510;
		NumY_2 = -950;
		break;
	case 2:
		if (!player->player)
		{
			item->ItemFlag = true;
		}
		break;
	case 3:
		NumX_1 = 270;
		if (PlayerLY > 540)
		{
			NumY_2 = -250;
		}
		else
		{
			NumY_2 = -950;
			if (item->ItemNum == 3)
			{
				enemy->X = 1200;
				enemy->Y = 950;
				enemy->DrawFlag = true;
				enemy->enemy = true;
			}
		}
		break;
	case 4:
		abs(item->ItemNum) < abs(4) ? item->ItemFlag = true : item->ItemFlag = false;
		break;
	}
	if (item->ItemNum <= 1&&FileNum==3&&!enemy->enemy)
	{
		player->isSoundFlag = true;
		enemy->DrawFlag = true;
		comment->CommentFlag = true;
	}
	if (FileNum2 == 1 && FileNum > 0)
	{
		comment->CommentFlag = true;
		StopSoundMem(enemy->RunBgm);
	}

	for (int iy = idLY; iy < idRY + 1; iy++)
	{
		for (int ix = idLX; ix < idRX + 1; ix++)
		{

			//ブロック左上右下座標//
			int blockLX = ix * COLLISION_TILE_WIDTH;
			int blockLY = iy * COLLISION_TILE_HEIGHT;
			int blockRX = blockLX + COLLISION_TILE_WIDTH;
			int blockRY = blockLY + COLLISION_TILE_HEIGHT;

			// 衝突したのでめり込みを戻す（リアクション）
			int dx1 = blockLX - PlayerRX;
			int dx2 = blockRX - PlayerLX;
			int dy1 = blockLY - PlayerRY;
			int dy2 = blockRY - PlayerLY;

			int dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
			int dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;


			// そこはブロックか？
			if (cell[ix][iy] == BoxHandle[1])
			{
				//本当に当たっているか？
				if (PlayerLX <= blockRX && blockLX <= PlayerRX &&
					PlayerLY <= blockRY && blockLY <= PlayerRY)
				{
					if (abs(dx) < abs(dy))
					{
						player->SetX(dx);
					}
					else
					{
						player->SetY(dy);
					}
				}
			}
			if (cell[ix][iy] == BoxHandle[2])
			{
				if (item->ItemNum<FileNum||(item->ItemNum<4&&FileNum2==1))
				{
					player->isSoundFlag = true;
					PlaySoundMem(LockSound, DX_PLAYTYPE_BACK);
					if (abs(dx) < abs(dy))
					{
						player->SetX(dx);
					}
					else
					{
						player->SetY(dy);
					}
					comment->LockFlag = true;
					comment->CommentFlag = true;
					WaitTimer(100);
				}
				else
				{
					PlaySoundMem(DoorSound, DX_PLAYTYPE_BACK);
					FileNum++;
					if (abs(dx) < abs(dy))
					{
						player->SetX(NumX_1);
					}
					else
					{
						player->SetY(NumY_1);
					}
					if (enemy->enemy)
					{
						if (abs(dx) < abs(dy))
						{
							abs(LenghX) >abs(LenghY) ? enemy->GetX(player->X-LenghX) : enemy->GetX(player->X-LenghY);
							enemy->GetY(player->Y);
						}
						else
						{
							enemy->GetX(player->X);
							abs(LenghX) > abs(LenghY) ? enemy->GetY(player->Y+LenghX) : enemy->GetY(player->Y+LenghY);
						}
					}
					ClearDrawScreen();
					WaitTimer(300);
				}
			
			}
			if (cell[ix][iy] == BoxHandle[3])
			{
				PlaySoundMem(DoorSound, DX_PLAYTYPE_BACK);
				FileNum--;
				if (abs(dx) < abs(dy))
				{
					player->SetX(-NumX_1);
				}
				else
				{
					player->SetY(-NumY_1);
				}
				if (enemy->enemy)
				{
					if (abs(dx) < abs(dy))
					{
						
						abs(LenghX) > abs(LenghY) ? enemy->GetX(player->X+LenghX) : enemy->GetX(player->X+LenghY);
						enemy->GetY(player->Y);
					}
					else
					{
						enemy->GetX(player->X);
						abs(LenghX) > abs(LenghY) ? enemy->GetY(player->Y- LenghX) : enemy->GetY(player->Y- LenghY);
					}
				}
				ClearDrawScreen();
				WaitTimer(300);
			}
			if (FileNum == 5)
			{
				FileNum2++;
				FileNum = 0;
			}
			else if (FileNum < 0)
			{
				FileNum2--;
				switch (FileNum2)
				{
				case 0:
					FileNum = 3;
					break;
				}
			}
		}
	}
	//プレイヤー左上右下座標//
	int PlayerLX_2 = (player->X-PW*2) + COLLISION_WINDOW_X * FileNum;
	int PlayerLY_2 = (player->Y - PH / 4) + COLLISION_WINDOW_Y * FileNum2;
	int PlayerRX_2 = (player->X+PW*2) + COLLISION_WINDOW_X * FileNum;
	int PlayerRY_2 = (player->Y+PH) + COLLISION_WINDOW_Y * FileNum2;


	//左上右下添え字//
	int idLX_2 = PlayerLX_2 / COLLISION_TILE_WIDTH;
	int idLY_2 = PlayerLY_2 / COLLISION_TILE_HEIGHT;
	int idRX_2 = PlayerRX_2 / COLLISION_TILE_WIDTH;
	int idRY_2 = PlayerRY_2 / COLLISION_TILE_HEIGHT;

	if (idLY_2 < 0 || idRY_2 < 0)
	{
		return;
	}

	for (int iy = idLY_2; iy < idRY_2 + 1; iy++)
	{
		for (int ix = idLX_2; ix < idRX_2 + 1; ix++)
		{

			//ブロック左上右下座標//
			int blockLX_2 = ix * COLLISION_TILE_WIDTH;
			int blockLY_2 = iy * COLLISION_TILE_HEIGHT;
			int blockRX_2 = blockLX_2 + COLLISION_TILE_WIDTH;
			int blockRY_2 = blockLY_2 + COLLISION_TILE_HEIGHT;

			// 衝突したのでめり込みを戻す（リアクション）
			int dx_1 = blockLX_2 - PlayerRX_2;
			int dx_2 = blockRX_2 - PlayerLX_2;
			int dy_1 = blockLY_2 - PlayerRY_2;
			int dy_2 = blockRY_2 - PlayerLY_2;

			int dx_ = (abs(dx_1) < abs(dx_2)) ? dx_1 : dx_2;
			int dy_ = (abs(dy_1) < abs(dy_2)) ? dy_1 : dy_2;

			if (cell[ix][iy] == BoxHandle[4])
			{
				FileNum += 2;
				if (abs(dx_) < abs(dy_))
				{
				}
				else
				{
					player->SetY(NumY_2);
				}
				if (enemy->enemy)
				{
					if (abs(dx_) < abs(dy_))
					{
					}
					else
					{
						enemy->GetX(player->X);
						
						abs(LenghX) > abs(LenghY) ? enemy->GetY(player->Y- LenghX) : enemy->GetY(player->Y - LenghY);

					}
				}
				ClearDrawScreen();
				WaitTimer(300);
			}

			if (cell[ix][iy] == BoxHandle[5])
			{
				FileNum -= 2;
				if (abs(dx_) < abs(dy_))
				{
				}
				else
				{

					player->SetY(-NumY_2);
				}
				if (enemy->enemy)
				{
					if (abs(dx_) < abs(dy_))
					{
					}
					else
					{
						enemy->GetX(player->X);
						
						abs(LenghX) > abs(LenghY) ? enemy->GetY(player->Y + LenghX) : enemy->GetY(player->Y + LenghY);
					}
				}
				ClearDrawScreen();
				WaitTimer(300);
			}
		}
	}
}

void Collision::EnemyColBox(Enemy* enemy)
{
	//------------------------------------//
	//当たり判定
	//------------------------------------//
	//エネミー左上右下座標//
	int EnemyLX = (enemy->X - EW / 2) + COLLISION_WINDOW_X*FileNum;
	int EnemyLY = (enemy->Y + EH / 4) + COLLISION_WINDOW_Y*FileNum2;
	int EnemyRX = (enemy->X + EW / 2) + COLLISION_WINDOW_X*FileNum;
	int EnemyRY = (enemy->Y + EH) + COLLISION_WINDOW_Y*FileNum2;

	//左上右下添え字//
	int idLX = EnemyLX / COLLISION_TILE_WIDTH;
	int idLY = EnemyLY / COLLISION_TILE_HEIGHT;
	int idRX = EnemyRX / COLLISION_TILE_WIDTH;
	int idRY = EnemyRY / COLLISION_TILE_HEIGHT;

	if (idLY < 0 || idRY < 0)
	{
		return;
	}

	for (int iy = idLY; iy < idRY + 1; iy++)
	{
		for (int ix = idLX; ix < idRX + 1; ix++)
		{

			//ブロック左上右下座標//
			int blockLX = ix * COLLISION_TILE_WIDTH;
			int blockLY = iy * COLLISION_TILE_HEIGHT;
			int blockRX = blockLX + COLLISION_TILE_WIDTH;
			int blockRY = blockLY + COLLISION_TILE_HEIGHT;

			// 衝突したのでめり込みを戻す（リアクション）
			int dx1 = blockLX - EnemyRX;
			int dx2 = blockRX - EnemyLX;
			int dy1 = blockLY - EnemyRY;
			int dy2 = blockRY - EnemyLY;

			int dx = (abs(dx1) < abs(dx2)) ? dx1 : dx2;
			int dy = (abs(dy1) < abs(dy2)) ? dy1 : dy2;

			if (cell[ix][iy] == BoxHandle[0])
			{
				if (enemy->enemy)
				{
					enemy->DrawFlag = true;
				}
			}
			// そこはブロックか？
			if (cell[ix][iy] == BoxHandle[1])
			{
				//本当に当たっているか？
				if (EnemyLX <= blockRX && blockLX <= EnemyRX &&
					EnemyLY <= blockRY && blockLY <= EnemyRY)
				{
					if (abs(dx) < abs(dy))
					{
						enemy->Num = -1;
					}
					else
					{
						enemy->Num = 1;
					}
				}
			}
			if (cell[ix][iy] == BoxHandle[6])
			{
				//本当に当たっているか？
				if (EnemyLX <= blockRX && blockLX <= EnemyRX &&
					EnemyLY <= blockRY && blockLY <= EnemyRY)
				{
					if (enemy->enemy)
					{
						enemy->DrawFlag=false;
					}
				}
			}
		}
	}
}