#include "Game.hpp"

//extern'd in tools.hpp
int SCRWIDTH = 400; //1366
int SCRHEIGHT = 500; //768
int RADIUS = 5;
int GRIDX = 10;
int GRIDY = 10;

int main(int argc, char *argv[]) {
	srand(time(0));
	if (argc > 2) {
		GRIDX = atoi(argv[1]);
		GRIDY = atoi(argv[2]);
		//RADIUS = max(1, int (min((SCRWIDTH/MATRIX_X)/2, (SCRHEIGHT/ MATRIX_Y)/2)*0.8));
	}
	Game myGame;
	if(myGame.init()) {
		myGame.setScene(new myScene(myGame));

		myGame.run();
	}
	return 0;
}
