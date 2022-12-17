/*
	Tetris
	ver 1.0

	**编码：GB18030
	**Encoding : GB18030
*/

bool tetris_judge      (void);
//  Determine whether the game is over, that is,
//  whether the bottom line of BlockNext overlaps with the top line of Stage
//  True for Not Ended, False for Ended

bool hit_bottom      (void);
//  Determine if the block has fallen to the bottom
//  At the same time, judge whether there is an excess, assign a value to ex, and the excess is true
//  If it hits the bottom, it is true, if it does not hit the bottom, it is false



void initialize_tetris (void);
//  Initialize the game, print the start interface, and produce the first BlockNextID at the same time

void tetris_over       (void);
//  print end screen

void new_tetris        (void);
//  Clear Stage, Block, BlockNext and generate BlockNextID
//  Let the Score return to zero



void print_stage     (void);
//  Print out the game screen, including the score, the highest score

int  get_kbhit       (void);
//  Get the keyboard pressed, if not pressed, return 0



void block_change    (void);
//  Make a decision, if by changing the block
//  Change BlockChangeID at the same time

void block_move      (int);
//  Make a decision, if by changing the box Locate

void clean_block     (void);
//  Clear the falling blocks for easy judgment

void add_block       (void);
//  Add the block back to the Stage


void clean_line      (void);
//  Judging whether it can be eliminated, but also adding points, changing the highest score

void get_new_block   (void);
//  Let the next block ID replace the current one, generate the next one, let BlockID[1] return to zero, and then assign values to Block and BlockNext
//  At the same time, move the bottom line of the Block to the top line of the Stage
//  Loacte returns {0,3}



int Stage[20][10]   = {{0}};
int Block[4][4]     = {{0}};
int BlockNext[4][4] = {{0}};

int BlockNextID     = 0;
int BlockID[2]      = {0,0};
int Locate[2]       = {0,3};

int BlockStyle[76][4] =
{

	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},

	{0,0,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{0,1,1,1},
	{0,1,0,0},

	{0,0,0,0},
	{0,1,1,0},
	{0,0,1,0},
	{0,0,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{0,0,1,0},
	{1,1,1,0},

	{0,0,0,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,1,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,1},

	{0,0,0,0},
	{0,1,1,0},
	{0,1,0,0},
	{0,1,0,0},

	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,0},
	{0,0,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},

	{0,0,0,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,1,0,0},

	{0,0,0,0},
	{0,0,0,0},
	{0,0,1,1},
	{0,1,1,0},

	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,1,0},

	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,1,0,0},

	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,0},
	{0,1,0,0},

	{0,0,0,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,0,1,0},

	{0,0,0,0},
	{0,0,0,0},
	{0,0,1,0},
	{0,1,1,1},

	{0,0,0,0},
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0}
};
//The relationship corresponding to the block is in BlockID difference.png

//BlockID reference BlockID.png
//The red square in BlockID.png is the location of the Locate point

int Score           = 0;
int HighScore       = 0;
int Prehs           = 0;
bool ex             = false;

int Seed            = time(0);

int language        = 0;
// 0 = English
// 1 = 简体中文
// 2 = 繁体中文

int ScoreMode       = 0;

bool DoNotStop      = false;

int t               = 0;



int Tetris (void) {
	int TimeNow = time(0);
	int key;//119是W，115是S，97是A，100是D，32是空格，27是Esc，114是R
	bool stop = false;
	bool Judge = true;//先让这里为真
	bool pd = false;

	initialize_tetris();//初始化，说明游戏信息
	get_new_block();
	get_new_block();
	add_block();//加入第一个方块
	t = time(0);

	for (;;) {
		key = get_kbhit();//获取键盘信息

		if (Judge) {
			bool kick = false;//为真时说明发生有效改变，这时才刷新屏幕

			if (key == 27) {
				break;//退出游戏
			}
			else if (key == 32) {
				stop = true;//暂停
				DoNotStop = true;
			}
			else if (key == 114) {
				Judge = false;//按R重开，算作游戏结束
			}
			else if (key == 119) {
				int Change = BlockID[1];

				clean_block();
				block_change();//改变方块
				add_block();

				if (Change != BlockID[1]) {
					kick = true;//这时发生了有效改变
				}
			}
			else if (key == 115 or key == 97 or key == 100) {

				int Move1 = Locate[0];
				int Move2 = Locate[1];

				clean_block();
				block_move(key);//左右移动或向下加速
				add_block();

				if (Move1 != Locate[0] or Move2 != Locate[1]) {
					kick = true;//只在有效移动后刷新
				}
			}

			if (kick) {
				print_stage();//刷新屏幕
			}

			if (time(0) >= TimeNow + 1 and stop == false and Judge) {
				//每秒进行一次

				TimeNow = time(0);

				clean_block();
				pd = hit_bottom();//碰底判定
				add_block();

				if (pd) {
					int PreScore = Score;
					clean_line();

					if (PreScore < Score) {
						Judge = true;
					} else {
						Judge = tetris_judge();
					}

					if (Judge) {
						get_new_block();//碰底后加入BlockNext，并生成新的
						add_block();
					}
				} else {
					clean_block();
					block_move(115);//没碰底就向下移
					add_block();
				}
				print_stage();
			}
			else if (stop and Judge) {
				int t1 = time(0);

				print_stage();//游戏暂停

				if (language == 0) {
					printf("\nGAME STOP NOW\n");
				}
				else if (language == 1) {
					printf("\n游戏暂停\n");
				}

				HighScore = Prehs;//这里使暂停后记录最高分无效

				system("pause");//按键后继续

				int t2 = time(0);
				t = t - t1 + t2;//减去暂停的时间

				stop = false;//退出暂停
			}

		} else {
			tetris_over();//输出结束画面
			new_tetris();//进行新游戏

			get_new_block();
			get_new_block();
			add_block();

			Judge = true;
			pd = false;
			DoNotStop = false;
			t = time(0);
		}
	}

	return 0;
}



void initialize_tetris (void) {
	//Switch encoding to GBK
	system("title Tetris");
	system("cls");

	printf("\n Welcome to Tetris!\n");
	printf("\n\n\n    Language\n\n\n");
	printf("   0  English\n");
	printf("   1  简体中文\n");
	printf("\n>>> ");
	scanf("%d", &language);

	system("cls");
	printf("\n Welcome to Tetris!\n");

	if (language == 0) {
		printf("\n\n\n    Score Mode\n\n\n");
		printf("   0  Traditional\n");
		printf("   1  New\n");
	}
	else if (language == 1) {
		system("title 俄罗斯方块");
		printf("\n\n\n   记分模式\n\n\n");
		printf("   0  传统\n");
		printf("   1  累进\n");
	}

	printf("\n>>> ");
	scanf("%d", &ScoreMode);

	//randomly generated
	srand(Seed);
	BlockNextID = rand() % 7 + 1;
	Seed++;

	//输出说明信息
	system("cls");

	if (language == 0) {
		printf("\n Recommend Font And Size: Raster Fonts 10x20");
		printf("\n\n\n   Space : Stop\n");
		printf("   R     : ReStart\n\n");
		printf("   W     : Change Block\n");
		printf("   S     : Accelerated Descent\n");
		printf("   A     : Lift\n");
		printf("   D     : Right\n\n");
		printf("   Esc   : Exit Game\n");
		printf("\n\n**Encoded with GB18030\n\n");
	}
	else if (language == 1) {
		printf("\n 推荐字体和大小： Raster Fonts 10x20");
		printf("\n\n\n   空格       暂停\n");
		printf("      R       Remake\n\n");
		printf("      W       改变方块\n");
		printf("      S       加速下降\n");
		printf("      A       左移\n");
		printf("      D       右移\n\n");
		printf("    Esc       退出游戏\n");
		printf("\n\n**编码 GB18030\n\n");
	}

	system("pause");
}

int get_kbhit (void) {
	int ch = 0;
	if (_kbhit()) {
		ch = _getch();
	}
	return ch;
	//读取键盘，但不做判断
}

void print_stage (void) {
	system ("cls");
	printf (" ┏━━━━━━━━━━┓\n");

	for (int i = 0; i <= 19; i++) {
		printf (" ┃");

		for (int j = 0; j <= 9; j++) {
			if (Stage[i][j] == 1) {
				printf("■");
			} else {
				printf("  ");
			}
		}

		printf ("┃");

		if (i == 1) {
			if (language == 0) {
				if (ScoreMode == 0) {
					printf("  Traditional");
				} else {
					printf("  New");
				}
			}
			else if (language == 1) {
				if (ScoreMode == 0) {
					printf("  传统");
				} else {
					printf("  累进");
				}
			}
		}
		else if (i == 3) {
			printf("      NEXT");
		}
		else if (i == 4) {
			printf("  ┏━━━━┓");
		}
		else if (i >= 5 and i <= 8) {
			printf("  ┃");
			for (int k = 0; k <= 3; k++) {
				if (BlockNext[i-5][k] == 1) {
					printf("■");
				} else {
					printf("  ");
				}
			}
			printf("┃");
		}
		else if (i == 9) {
			printf("  ┗━━━━┛");
		}
		else if (i == 11) {
			int tt = time(0) - t;
			if (language == 0) {
				printf("         Time: %ds", tt);
			}
			else if (language == 1) {
				printf("   时  间： %ds", tt);
			}
		}
		else if (i == 12) {
			if (language == 0) {
				printf("        Score: %d", Score);
			}
			else if (language == 1) {
				printf("   得  分： %d", Score);
			}
		}
		else if (i == 13) {
			if (language == 0) {
				printf("   High Score: %d", HighScore);
			}
			else if (language == 1) {
				printf("   最高分： %d", HighScore);
			}
		}
		printf("\n");
	}

	printf(" ┗━━━━━━━━━━┛\n");
}

void tetris_over (void) {
	system("cls");

	int tt = time(0) - t;
	printf("\n\n  GAME OVER\n");

	if (language == 0) {
		if (ScoreMode == 0) {
			printf("\n  Traditional");
		} else {
			printf("\n  New");
		}

		printf("\n\n       Stop: ");

		if (DoNotStop) {
			printf("Yes");
		} else {
			printf("No");
			Prehs = HighScore;
		}

		printf("    \n       Time: %ds", tt);
		printf("\n\n\n      Score: %d", Score);
		printf("\n  HighScore: %d\n\n\n", HighScore);
	}
	else if (language == 1) {
		if (ScoreMode == 0) {
			printf("\n  传统");
		} else {
			printf("\n  累进");
		}

		printf("\n\n        暂  停：");

		if (DoNotStop) {
			printf("是");
		} else {
			printf("否");
			Prehs = HighScore;
		}
		
		printf("\n        时  间： %ds", tt);
		printf("\n\n\n        得  分： %d", Score);
		printf("\n        最高分： %d\n\n\n", HighScore);
	}
	system("pause");
}

void new_tetris (void) {
	for (int i = 0; i <= 19; i++) {
		for (int j = 0; j <= 9; j++) {
			Stage[i][j] = 0;
		}
	}
	//清空Stage

	srand(Seed);
	BlockNextID = rand() % 7 + 1;
	Seed++;
	//随机生成

	Score = 0;
}

void clean_block (void) {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (Block[i][j] == 1) {
				int a = Locate[0] + i - 3;
				int b = Locate[1] + j;
				//确定对应的位置
				//这里locate对应的位置是方块的左下角
				if (a >= 0 and a <= 19 and b >= 0 and b <= 9) {
					Stage[a][b] = 0;
				}
			}
		}
	}
}

void add_block (void) {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (Block[i][j] == 1) {
				int a = Locate[0] + i - 3;
				int b = Locate[1] + j;
				//同clean_block
				if (a >= 0 and a <= 19 and b >= 0 and b <= 9) {
					Stage[a][b] = 1;
				}
			}
		}
	}
}

void clean_line (void) {
	int once = true;
	int sc = 0;
	for (int i = 19; i >= 0; i = i - 1) {
		int sum = 0;
		for (int j = 0; j <= 9; j++) {
			if (Stage[i][j] == 1) {
				sum++;
			}
		}
		if (sum == 10) {
			int a = i;
			i = i + 1;
			sc++;
			if (a != 0) {
				for (a; a >= 1; a = a - 1) {
					for (int j = 0; j <= 9; j++) {
						Stage[a][j] = Stage[a-1][j];
					}
				}
				if (once) {
					once = false;
					for (int j = 0; j <= 9; j++) {
						Stage[0][j] = 0;
					}
				}
			} else {
				for (int j = 0; j <= 9; j++) {
					Stage[a][j] = 0;
				}
			}
		}
	}

	if (ScoreMode == 0) {
		Score = Score + sc;
	}
	else if (ScoreMode == 1) {
		int k = 1;
		for (int i = 1; i <= sc; i++) {
			Score = Score + k;
			k = k * 2;
		}
	}

	if (Score > HighScore) {
		HighScore = Score;
	}
	
	if (DoNotStop) {
		HighScore = Prehs;
	}
}

bool tetris_judge (void) {
	bool re = true;
	if (BlockID[0] == 1 and BlockID[1] == 1) {
		for (int i = 3; i <= 6; i ++) {
			if (Stage[0][i] == 1) {
				re = false;
				break;
			}
		}
	}
	else if (ex) {
		//方块有超出的情况
		ex = false;
		re = false;
	} else {
		if (Stage[0][4] == 1 and BlockNext[3][1] == 1) {
			re = false;
		}
		if (Stage[0][5] == 1 and BlockNext[3][2] == 1) {
			re = false;
		}
	}
	//剩下两种都是无法放进去的情况
	//超出在hit_bottom里判断并通过ex返回
	return re;
}

void get_new_block (void) {
	Locate[0]  = 0;
	Locate[1]  = 3;
	BlockID[0] = BlockNextID;
	BlockID[1] = 0;
	srand(Seed);
	BlockNextID = rand() % 7 + 1;
	Seed++;

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			Block[i][j] = BlockNext[i][j];
		}
	}

	int a[6] = {2,4,4,2,2,4};
	int b = 0;

	for (int i = 0; i <= BlockNextID - 2; i ++) {
		b = b + a[i];
	}

	b = b * 4;

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			BlockNext[i][j] = BlockStyle[i+b][j];
		}
	}
}

void block_move (int Move) {
	//115是S，97是A，100是D

	bool JudgeA = true;

	if (Move == 115) {
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 3; j++) {
				if (Block[i][j] == 1) {
					int a = Locate[0] + i - 2;
					int b = Locate[1] + j;
					if (a > 19 or b < 0 or b > 9) {
						JudgeA = false;
						break;
					}
					else if (Stage[a][b] == 1) {
						JudgeA = false;
						break;
					}
				}
			}
			if (JudgeA == false) {
				break;
			}
		}
		if (JudgeA) {
			Locate[0]++;
		}
	} else {
		int k = 0;
		if (Move == 97) {
			k = -1;
		}
		else if (Move == 100) {
			k = 1;
		}
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 3; j++) {
				if (Block[i][j] == 1) {
					int a = Locate[0] + i - 3;
					int b = Locate[1] + j + k;
					if (a > 19 or b < 0 or b > 9) {
						JudgeA = false;
						break;
					}
					else if (Stage[a][b] == 1) {
						JudgeA = false;
						break;
					}
				}
			}
		}
		if (JudgeA) {
			Locate[1] = Locate[1] + k;
		}
	}
}

void block_change (void) {
	int a[7] = {2,4,4,2,2,4,1};
	int b = 0;
	int c = BlockID[0] - 1;
	int bk[4][4] = {{0}};
	bool JudgeB = true;
	for (int i = 0; i <= BlockID[0] - 2; i++) {
		b = b + a[i];
	}
	if (BlockID[1] + 1 < a[c]) {
		b = (b + BlockID[1] + 1) * 4;
	} else {
		b = b * 4;
	}
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			bk[i][j] = BlockStyle[i+b][j];
		}
	}
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (bk[i][j] == 1) {
				int a = Locate[0] + i - 3;
				int b = Locate[1] + j;
				if (a > 19 or b < 0 or b >9) {
					JudgeB = false;
					break;
				}
				else if (Stage[a][b] == 1){
					JudgeB = false;
					break;
				}
			}
		}
		if (JudgeB == false) {
			break;
		}
	}
	if (JudgeB) {
		if (BlockID[1] + 1 < a[c]) {
			BlockID[1]++;
		} else {
			BlockID[1] = 0;
		}
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 3; j++) {
				Block[i][j] = bk[i][j];
			}
		}
	}
}

bool hit_bottom (void) {
	bool re = false;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (Block[i][j] == 1) {
				int a = Locate[0] + i - 2;
				int b = Locate[1] + j;
				if (Stage[a][b] == 1 or a > 19) {
					re = true;
					break;
					if (a < 1) {
						ex = true;
					}
				}
			}
		}
		if (re) {
			break;
		}
	}
	return re;
}
