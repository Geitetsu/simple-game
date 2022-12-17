int get_hit_key_controll (void);

int KeyBoardControll (void) {

int cc = 1;

for (;;) {
	printf("=========Geitetsu's Game=========\n\n\n");

	if (cc == 1) {
		printf(" ->");
	}
	printf("  1. Tetris\n");

	if (cc == 2) {
		printf(" ->");
	}
	printf("  2. Music Game Trainer\n");

	if (cc == 0) {
		printf(" ->");
	}
	printf("   About\n");

	if (cc == -1) {
		printf(" ->");
	}
	printf("   Exit\n");
}
	
}