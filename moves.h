#include "snack.h"
#include "wall.h"
struct snack* head_of_snack;
struct wall* head_of_wall;
COORD address_of_food;
int mark_of_food;
void creat_food(){                             //随机生成食物，并在界面打印 
	struct wall* w;
	int ok;
	srand((unsigned int)time(NULL));
	for(;;){
		address_of_food.X=rand()%Wideth+1;
		address_of_food.Y=rand()%Longth+1;
		for(w=head_of_wall,ok=1;w!=NULL;w=w->next)
			if(w->address_X==address_of_food.X&&w->address_Y==address_of_food.Y){                    //判断食物是否与某个墙壁重合，若重合则重新生成 
				ok=0;
			}
		if(ok==1)
			break;
		}
	HANDLE hwnd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hwnd,address_of_food);
	printf(body);
	mark_of_food=1;
}
int dead_of_snack(){                                                  //判断蛇是否死亡 
	int i;
	struct wall* w;
	struct snack* p;
	if(head_of_snack->x==0||head_of_snack->x==Wideth+1||head_of_snack->y==0||head_of_snack->y==Longth+1)             //若蛇越过边界，则死亡 
		return(1);
	for(w=head_of_wall;w!=NULL;w=w->next)                                            //若蛇撞到随机生成的墙壁，则蛇死亡 
		if(w->address_X==head_of_snack->x&&w->address_Y==head_of_snack->y)
				return (1);
	for(p=head_of_snack->next;p!=NULL;p=p->next){                         
		if(p->x==head_of_snack->x&&p->y==head_of_snack->y)                           //若蛇头撞到身体，则死亡 
			return(1);
		}
	return(0);			
}
void game_start(){                              //游戏开始函数，包括一些初始化 
	COORD coord;
	print_border();                   //打印游戏界面边界 
	head_of_wall=creat_wall();         //随机生成障碍墙体 
	print_wall(head_of_wall);            //打印障碍墙体 
	head_of_snack=creat_snack();           //初始化一条蛇 
	creat_food();                           //随机生成食物并打印 
	HANDLE hwnd=GetStdHandle(STD_OUTPUT_HANDLE);                //打印说明文字 
	coord.X=Wideth+2;
	coord.Y=0;
	SetConsoleCursorPosition(hwnd,coord);
	printf("------游戏说明-------"); 
	coord.X=Wideth+2;
	coord.Y=1;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--0:墙壁");
	coord.X=Wideth+2;
	coord.Y=2;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--1:蛇头");
	coord.X=Wideth+2;
	coord.Y=3;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--#:蛇的身体和食物");
	coord.X=Wideth+2;
	coord.Y=4;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--移动键：上W 左A 下S 右D");
}
void control_snack(){                               //游戏过程中蛇的运动 
	int kb;
	while(1){
		if(mark_of_food==0)
			creat_food();
		print_snack(head_of_snack);            //打印蛇 
		if(dead_of_snack()){
			printf("You Die！\n");                 //判断蛇是否死亡，若死亡退出循环，游戏结束 
			break;
		}
		Sleep(speed*1000);                           //蛇的移动间隔时间 
		wipe_snack(head_of_snack);                   //从屏幕上擦除蛇 
		if(kbhit()){
			kb=getch();
			switch(kb){
				case UP:
					head_of_snack=snack_turn(head_of_snack,kb);
					break; 
				case DOWN:
					head_of_snack=snack_turn(head_of_snack,kb);                 //判断键盘是否有输入，若有就调用转向函数，否则保持运动方向 
					break;
				case LEFT:
					head_of_snack=snack_turn(head_of_snack,kb);
					break;
				case RIGHT:
					head_of_snack=snack_turn(head_of_snack,kb);
					break;
			}
		}
		else
			head_of_snack=snack_turn(head_of_snack,head_of_snack->direction);
		switch(head_of_snack->direction){                                                                  //判断蛇是否能吃到食物 
			case UP:
				if(head_of_snack->x==address_of_food.X&&head_of_snack->y-1==address_of_food.Y){
					head_of_snack=catch_snack(head_of_snack,address_of_food);
					mark_of_food=0;	
				}
			case DOWN:
				if(head_of_snack->x==address_of_food.X&&head_of_snack->y+1==address_of_food.Y){
					head_of_snack=catch_snack(head_of_snack,address_of_food);
					mark_of_food=0;	
				}
			case LEFT:
				if(head_of_snack->x-1==address_of_food.X&&head_of_snack->y==address_of_food.Y){
					head_of_snack=catch_snack(head_of_snack,address_of_food);
					mark_of_food=0;	
				}
			case RIGHT:
				if(head_of_snack->x+1==address_of_food.X&&head_of_snack->y==address_of_food.Y){
					head_of_snack=catch_snack(head_of_snack,address_of_food);
					mark_of_food=0;	
				}
		}
	}
}
