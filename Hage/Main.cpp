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
	//@brief ��{�ݒ�
	//------------------------------------//
	SetGraphMode(Window_Width, Window_Height, Color_Depth);										//�E�B���h�E�T�C�Y�ƃJ���[���w��
	ChangeWindowMode(TRUE);																		//�E�B���h�E���[�h�L����
	DxLib_Init();																				//���C�u����������
	SetDrawScreen(DX_SCREEN_BACK);																//�ǂݍ��݊J�n

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
	//@brief �摜�E�T�E���h�ǂݍ���
	//------------------------------------//
	save->Load();
	game->Load();
	background->Load();
	player->Load();
	enemy->Load();
	comment->Load();

	//���ԎZ�o//
	int nowTime = GetNowCount();
	int prevTime = nowTime;
	while (1)
	{	
		//------------------------------------//
		//@brief ����������
		//------------------------------------//
		while (!ProcessMessage() && game->Status == INIT)
		{
			ClearDrawScreen();

			//init�֐��Ăяo��//
			game->Init();
			background->Init();
			collision->Init();
			item->Init();
			player->Init();
			enemy->Init();
			comment->Init();

			game->Status = TITLE;									//�Q�[���^�C�g����ʂ�
			ScreenFlip();											//����ʂ̓��e��\��ʂɔ��f������
		}

		//------------------------------------//
		//@brief �Q�[���^�C�g��
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
		//@brief �v���C
		//------------------------------------//
		while (!ProcessMessage() && game->Status == PLAY)
		{
			ClearDrawScreen();

			//�t���[�����Ԃ��Z�o//
			nowTime = GetNowCount();
			float deltaTime = (nowTime - prevTime) / 1000.0f;


			background->Main(collision->FileNum2,collision->FileNum);
			if (!comment->CommentFlag&&!save->save)
			{
				player->Main();
				enemy->Main(player,game);
				SetFontSize(24);
				DrawFormatString(10, 750, GetColor(255, 255, 255), "�������\n");
				DrawFormatString(10, 780, GetColor(25, 255, 25), "�ړ�:�\���L�[\n�A�N�V����:Enter�L�[orSpace�L�[\n");
				DrawFormatString(10, 840, GetColor(25, 255, 255), "���j���[:Esc�L�[\n");
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