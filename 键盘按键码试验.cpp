#include <stdio.h>
#include <windows.h>
#include <conio.h>
main(){
	int kb;
	while(1){
		Sleep(1000);
		if(kbhit()){
			kb=getch();
			printf("-----%d------\n",kb);
		}
		else
			printf("£°Œﬁ ‰»Î£°\n");
	}
}
