int get_hit_key_controll (void);

int ChooseMenu (void) {
	bool Exit_Key_Controller = false;
	int Point_At = 0;
	int longth = 5;
	int re;

	while (Exit_Key_Controller == false) {
		system("cls");
		printf("\n\n   ========GeiTetsu's Game========\n\n\n");

		for (int i = 0; i < longth; ++i) {
			if (i == Point_At) {
				printf("     =>  ");
			} else {
				printf("         ");
			}

			switch (i) {
				case 0 :
					printf("Tetris\n");
					break;
				case 1 :
					printf("MUG Trainer\n");
					break;
				case 2 :
					printf("Sudo\n\n\n");
					break;
				case 3 :
					printf("About\n");
					break;
				case 4 :
					printf("Exit\n");
					break;
			}
		}

		if (get_hit_key_controll() == -1) {
			Exit_Key_Controller = true;
			re = -1;
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
