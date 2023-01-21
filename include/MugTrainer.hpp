/*
	±àÂë £º GB18030
	Encoding : GB18030
*/

int Block_MUG_trainer[20] = {0};

unsigned int seed = time (0);
unsigned int seed_up = 1;

int  initial_MUG_trainer      (void);
int get_hit_MUG_trainer      (int, int);
void fail_MUG_trainer         (int, int, int, int, int);
void print_screen_MUG_trainer (int, int, int);

void MugTrainer (void) {
	system("title MUG Trainer");
	
	int KNumber, TM;
	int Hit = 0;
	int HighHit = 0;
	int HighHit_s = 0;
	int Now_Block = 0;
	bool Finish = false;
	bool First = true;
	bool Exit_MUG_trainwer = false;
	
	KNumber = initial_MUG_trainer();

for (;;) {
	if (Finish) {
		int t = time(0) - TM;
		int Hit_s = 0;

		Finish = false;
		First = true;

		if (HighHit < Hit - 1) {
			HighHit = Hit - 1;
		}

		if (t > 0) {
			Hit_s = (Hit - 1) / t;
			if (HighHit_s < Hit_s) {
				HighHit_s = Hit_s;
			}
		}

		fail_MUG_trainer(Hit - 1, t, HighHit, HighHit_s, Hit_s);

		Hit = 0;
		Now_Block = 0;
		TM = time(0);
	} else {
		print_screen_MUG_trainer(KNumber, Now_Block, Hit);
		int f = get_hit_MUG_trainer(KNumber, Now_Block);

		switch (f) {
			case 0 :
				Finish = true;
				break;
			case -1:
				Exit_MUG_trainwer = true;
				break;
		}

		if (Exit_MUG_trainwer) {
			break;
		}

		if (First) {
			TM = time(0);
			First = false;
		}

		if (Now_Block < 19) {
			++Now_Block;
		} else {
			Now_Block = 0;
		}

		++Hit;
	}
}
}

int initial_MUG_trainer (void) {
	int re;

	for (;;) {
		system("cls");
		printf("  4K ~ 9K MUG Trainer\n");
		printf("\n\n  Keys: ");
		scanf ("%d", &re);

		if (re >= 4 and re <= 9) {
			break;
		} else {
			printf("  Only support 4K ~ 7K!!!\n");
			system("pause");
		}
	}

	for (int i = 0; i < 20; ++i) {
		srand(seed);
		seed = seed + seed_up;
		++seed_up;

		Block_MUG_trainer[i] = rand() % re;
	}

	return re;
}

void fail_MUG_trainer (int Hit_in, int t_in, int HighHit_in, int HighHit_s_in, int Hit_s_in) {
	system("cls");

	printf("  Highest   Hits : %d\n", HighHit_in);
	printf("  Highest hits/s : %d\n", HighHit_s_in);

	printf("\n\n\n %d blocks you have hit!\n", Hit_in);
	printf(" %ds you used.\n", t_in);

	if (t_in > 0) {
		printf("\n\n\n  hits/s : %d\n\n\n", Hit_s_in);
	}

	system("pause");
}

void print_screen_MUG_trainer (int KNumber_in, int Now_Block_in, int Hit_in) {
	system("cls");
	printf("                        hits: %d\n", Hit_in);

	for (int i = Now_Block_in - 1; i >= 0; i = i - 1) {
		printf("\n                     |");
		for (int j = 0; j < Block_MUG_trainer[i]; ++j)
		{
			printf("   ");
		}
		printf(" ¡ö");
		for (int j = Block_MUG_trainer[i] + 1; j < KNumber_in; ++j)
		{
			printf("   ");
		}
		printf("|");
	}

	for (int i = 19; i >= Now_Block_in; i = i - 1) {
		printf("\n                     |");
		for (int j = 0; j < Block_MUG_trainer[i]; ++j)
		{
			printf("   ");
		}
		printf(" ¡ö");
		for (int j = Block_MUG_trainer[i] + 1; j < KNumber_in; ++j)
		{
			printf("   ");
		}
		printf("|");
	}

	printf("\n                     |");
	for (int i = 1; i <= KNumber_in; i++) {
		printf(" 0%d", i);
	}
	printf("|");
}

int get_hit_MUG_trainer (int KNumber_in, int Now_Block_in) {
	int ch;
	int k = 0;
	for (;;) {
		if (_kbhit()) {
			ch = _getch();
			switch (KNumber_in) {
				case 1 :
					if (ch == 32) {
						k = 1;
					}
					if (ch == 27) {
						k = -1;
					}
					break;
				case 4 :
					switch (ch) {
						case 100 :
							k = 1;
							break;
						case 102 :
							k = 2;
							break;
						case 106 :
							k = 3;
							break;
						case 107 :
							k = 4;
							break;
						case 27 :
							k = -1;
							break;
					}
					break;
			}
		}

		if (k != 0) {
			break;
		}
	}

	if (k == Block_MUG_trainer[Now_Block_in] + 1) {
		srand(seed);
		seed = seed + seed_up;
		++seed_up;

		Block_MUG_trainer[Now_Block_in] = rand() % KNumber_in;

		return 1;
	}
	else if (k == -1) {
		return -1;
	}
	else {
		return 0;
	}
}
