#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#include <MugTrainer.hpp>
#include <Tetris.hpp>
#include <ChooseMenu.hpp>
#include <About.hpp>
#include <Sudo.hpp>

int main () {

for (;;) {
	system("title Game");

	int Choice;
	bool Exit = false;

	Choice = ChooseMenu();

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
		case 3 :
			Sudo();
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