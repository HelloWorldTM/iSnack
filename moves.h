#include "snack.h"
#include "wall.h"
struct snack* head_of_snack;
struct wall* head_of_wall;
COORD address_of_food;
int mark_of_food;
void creat_food(){                             //�������ʳ����ڽ����ӡ 
	struct wall* w;
	int ok;
	srand((unsigned int)time(NULL));
	for(;;){
		address_of_food.X=rand()%Wideth+1;
		address_of_food.Y=rand()%Longth+1;
		for(w=head_of_wall,ok=1;w!=NULL;w=w->next)
			if(w->address_X==address_of_food.X&&w->address_Y==address_of_food.Y){                    //�ж�ʳ���Ƿ���ĳ��ǽ���غϣ����غ����������� 
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
int dead_of_snack(){                                                  //�ж����Ƿ����� 
	int i;
	struct wall* w;
	struct snack* p;
	if(head_of_snack->x==0||head_of_snack->x==Wideth+1||head_of_snack->y==0||head_of_snack->y==Longth+1)             //����Խ���߽磬������ 
		return(1);
	for(w=head_of_wall;w!=NULL;w=w->next)                                            //����ײ��������ɵ�ǽ�ڣ��������� 
		if(w->address_X==head_of_snack->x&&w->address_Y==head_of_snack->y)
				return (1);
	for(p=head_of_snack->next;p!=NULL;p=p->next){                         
		if(p->x==head_of_snack->x&&p->y==head_of_snack->y)                           //����ͷײ�����壬������ 
			return(1);
		}
	return(0);			
}
void game_start(){                              //��Ϸ��ʼ����������һЩ��ʼ�� 
	COORD coord;
	print_border();                   //��ӡ��Ϸ����߽� 
	head_of_wall=creat_wall();         //��������ϰ�ǽ�� 
	print_wall(head_of_wall);            //��ӡ�ϰ�ǽ�� 
	head_of_snack=creat_snack();           //��ʼ��һ���� 
	creat_food();                           //�������ʳ�ﲢ��ӡ 
	HANDLE hwnd=GetStdHandle(STD_OUTPUT_HANDLE);                //��ӡ˵������ 
	coord.X=Wideth+2;
	coord.Y=0;
	SetConsoleCursorPosition(hwnd,coord);
	printf("------��Ϸ˵��-------"); 
	coord.X=Wideth+2;
	coord.Y=1;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--0:ǽ��");
	coord.X=Wideth+2;
	coord.Y=2;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--1:��ͷ");
	coord.X=Wideth+2;
	coord.Y=3;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--#:�ߵ������ʳ��");
	coord.X=Wideth+2;
	coord.Y=4;
	SetConsoleCursorPosition(hwnd,coord);
	printf("--�ƶ�������W ��A ��S ��D");
}
void control_snack(){                               //��Ϸ�������ߵ��˶� 
	int kb;
	while(1){
		if(mark_of_food==0)
			creat_food();
		print_snack(head_of_snack);            //��ӡ�� 
		if(dead_of_snack()){
			printf("You Die��\n");                 //�ж����Ƿ��������������˳�ѭ������Ϸ���� 
			break;
		}
		Sleep(speed*1000);                           //�ߵ��ƶ����ʱ�� 
		wipe_snack(head_of_snack);                   //����Ļ�ϲ����� 
		if(kbhit()){
			kb=getch();
			switch(kb){
				case UP:
					head_of_snack=snack_turn(head_of_snack,kb);
					break; 
				case DOWN:
					head_of_snack=snack_turn(head_of_snack,kb);                 //�жϼ����Ƿ������룬���о͵���ת���������򱣳��˶����� 
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
		switch(head_of_snack->direction){                                                                  //�ж����Ƿ��ܳԵ�ʳ�� 
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
