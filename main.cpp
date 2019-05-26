#include "moves.h" 
main(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);     
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);                  	/*隐藏控制台光标*/         
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	game_start();
	control_snack();
}

