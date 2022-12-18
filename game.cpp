#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#include <MugTrainer.hpp>
#include <Tetris.hpp>
#include <KeyBoardControll.hpp>
#include <About.hpp>

int main () {

for (;;) {
	system("title Game");

	int Choice;
	bool Exit = false;

	Choice = KeyBoardControll();

	switch (Choice) {
		case -1 :
			Exit = true;
			break;
		case 1 :
			Tetris();
			break;
		case 2 :
			MugTrainer();
			break;
		case 0 :
			About();
			break;
	}

	if (Exit) {
		break;
	}
}
	return 0;
}