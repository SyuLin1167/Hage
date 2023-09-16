#include"DxLib.h"
#include"Save.h"
#include"Seen.h"
#include"BackGround.h"
#include"Collision.h"
#include"Tool.h"
#include"Item.h"
#include"Player.h"
#include"Enemy.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	//------------------------------------//
	//@brief 基本設定
	//------------------------------------//
	SetGraphMode(Window_Width, Window_Height, Color_Depth);										//ウィンドウサイズとカラー数指定
	ChangeWindowMode(TRUE);																		//ウィンドウモード有効化
	DxLib_Init();																				//ライブラリ初期化
	SetDrawScreen(DX_SCREEN_BACK);																//読み込み開始

	Save* save = new Save();
	Game* game=new Game();
	BackGround* background = new BackGround();
	Collision* collision = new Collision();
	Tool* tool = new Tool();
	Item* item = new Item();
	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Comment* comment = new Comment();

	//------------------------------------//
	//@brief 画像・サウンド読み込み
	//------------------------------------//
	save->Load();
	game->Load();
	background->Load();
	player->Load();
	enemy->Load();
	comment->Load();

	//時間算出//
	int nowTime = GetNowCount();
	int prevTime = nowTime;
	while (1)
	{	
		//------------------------------------//
		//@brief 初期化処理
		//------------------------------------//
		while (!ProcessMessage() && game->Status == INIT)
		{
			ClearDrawScreen();

			//init関数呼び出し//
			game->Init();
			background->Init();
			collision->Init();
			item->Init();
			player->Init();
			enemy->Init();
			comment->Init();

			game->Status = TITLE;									//ゲームタイトル画面へ
			ScreenFlip();											//裏画面の内容を表画面に反映させる
		}

		//------------------------------------//
		//@brief ゲームタイトル
		//------------------------------------//
		while (!ProcessMessage() && game->Status == TITLE)
		{
			ClearDrawScreen();
			game->Title();
			ScreenFlip();
		}
		WaitTimer(300);

		while (!ProcessMessage() && game->Status == SAVE)
		{
			
				ClearDrawScreen();
				save->LoadData(game, player, enemy, collision, item,comment);
			ScreenFlip();
		}
		WaitTimer(100);

		//------------------------------------//
		//@brief プレイ
		//------------------------------------//
		while (!ProcessMessage() && game->Status == PLAY)
		{
			ClearDrawScreen();

			//フレーム時間を算出//
			nowTime = GetNowCount();
			float deltaTime = (nowTime - prevTime) / 1000.0f;


			background->Main(collision->FileNum2,collision->FileNum);
			if (!comment->CommentFlag&&!save->save)
			{
				player->Main();
				enemy->Main(player,game);
				SetFontSize(24);
				DrawFormatString(10, 750, GetColor(255, 255, 255), "操作説明\n");
				DrawFormatString(10, 780, GetColor(25, 255, 25), "移動:十字キー\nアクション:EnterキーorSpaceキー\n");
				DrawFormatString(10, 840, GetColor(25, 255, 255), "メニュー:Escキー\n");
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					save->save = true;
				}
			}
			
		

			background->Draw(collision->FileNum2,collision->FileNum);
			collision->PlayerColBox(item->ItemNum,player,comment,item,enemy);
			collision->EnemyColBox(enemy);
			tool->View(collision->FileNum,collision->FileNum2);
			item->ItemBox(collision->FileNum,collision->FileNum2,player,enemy,comment);
			player->Draw();
			enemy->Draw();
			comment->Main(item->ItemNum,collision->FileNum,player,enemy,game);
			save->GameSave(game, player, enemy, collision, item,comment);
			ScreenFlip();
		}
		WaitTimer(300);
		while (!ProcessMessage() && game->Status ==OVER)
		{
			ClearDrawScreen();
			game->Over();
			ScreenFlip();
		}
		WaitTimer(300);

		while (!ProcessMessage() && game->Status == CLEAR)
		{
			ClearDrawScreen();
			game->Clear();
			ScreenFlip();
		}
		WaitTimer(300);
		if (game->Status == QUIT)
		{
			break;
		}
		if (ProcessMessage() < 0)
		{
			break;
		}
	}
	DxLib_End();
	return 0;
}