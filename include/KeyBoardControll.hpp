int get_hit_key_controll (void);

int KeyBoardControll (void) {

int re = 1;
bool Exit_kbc = false;

for (;;) {
	system("cls");
	printf("=========Geitetsu's Game=========\n\n\n");

	if (re == 1) {
		printf(" ->");
	}
	else {printf("   ");}
	printf("  1. Tetris\n");

	if (re == 2) {
		printf(" ->");
	}
	else {printf("   ");}
	printf("  2. Music Game Trainer\n\n\n");

	if (re == 0) {
		printf(" ->");
	}
	else {printf("   ");}
	printf("   About\n");

	if (re == -1) {
		printf(" ->");
	}
	else {printf("   ");}
	printf("   Exit\n");

	switch (get_hit_key_controll()) {
		case -1 :
			if (re == -1) {
				Exit_kbc = true;
			}
			re = -1;
			break;
		case 100 :
			Exit_kbc = true;
			break;
		case 101 :
			switch (re) {
				case 2 :
					re = 1;
					break;
				case 0 :
					re = 2;
					break;
				case -1 :
					re = 0;
					break;
			}
			break;
		case 102 :
			switch (re) {
				case 1 :
					re = 2;
					break;
				case 2 :
					re = 0;
					break;
				case 0 :
					re = -1;
					break;
			}
			break;
		case 1 :
			re = 1;
			break;
		case 2 :
			re = 2;
			break;
	}

	if (Exit_kbc) {
		break;
	}
}
	return re;
}

int get_hit_key_controll (void) {
	int ch;
	bool k_224 = false;
	int k = 0;
	for (;;) {
		if (_kbhit()) {
			ch = _getch();
			if (k_224) {
				k_224 = false;
				switch (ch) {
					case 72 :
						k = 101;
						break;
					case 80 :
						k = 102;
						break;
					case 75 :
						k = 101;
						break;
					case 77 :
						k = 102;
						break;
				}
			} else {
				switch (ch) {
					case 27 :	// Esc
						k = -1;
						break;
					case 49 :	// 1
						k = 1;
						break;
					case 50 :	// 2
						k = 2; 
						break;
					case 13 :	// Enter
						k = 100;
						break;
					case 119 :
						k = 101;
						break;
					case 115 :
						k = 102;
						break;
					case 97 :
						k = 101;
						break;
					case 100 :
						k = 102;
						break;
					case 224 :
						k_224 = true;
						break;
				}
			}
		}

		if (k != 0 and k != 224) {
			break;
		}
	}
	return k;
}
