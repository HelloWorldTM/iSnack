#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h> 
#define Wideth 50
#define Longth 15
#define block "0"
#define body "#"
#define blank " "
#define UP 115
#define DOWN 119
#define LEFT 97
#define RIGHT 100
#define block_num 10             //����������ɵ�ǽ������ 
struct wall{
	int address_X;
	int address_Y;
	struct wall* next;
};
struct wall* creat_wall(){                                   //��������n��ǽ������ 
	int i;
	struct wall* head=NULL;
	struct wall* p;
	srand((unsigned int)time(NULL));
	for(i=1;i<=block_num;i++){
		p=(struct wall*)malloc(sizeof(struct wall));
		p->address_X=rand()%Wideth+1;
		p->address_Y=rand()%Longth+1;
		p->next=head;
		head=p;
	}
	return head;
}
void print_wall(struct wall* head){                            //��ӡ������ɵ�ǽ 
	COORD coord;
	int i=2;
	struct wall* p;
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	for(p=head;p!=NULL;p=p->next){
		coord.X=p->address_X;
		coord.Y=p->address_Y;
		SetConsoleCursorPosition(hwnd, coord);
		printf(block);
/*		coord.X=Wideth+3;
		coord.Y=i++;
		SetConsoleCursorPosition(hwnd, coord);
		printf("--%d--%d--",p->address_X,p->address_Y);               ����һ�δ�ӡǽ��λ����Ϣ�ĵ��Դ��룡           */
	}
}
void print_border(){                                            //��ӡ��Ϸ�ı߽� 
	COORD coord; 
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	int i,j;
	for(i=0,j=0;j<=Longth+1;j++){
		coord.X=i;
		coord.Y=j;
		SetConsoleCursorPosition(hwnd, coord);
		printf(block);
	}
	for(i=0,j=0;i<=Wideth;i++){
		coord.X=i;
		coord.Y=j;
		SetConsoleCursorPosition(hwnd, coord);
		printf(block);
	}
	for(i=Wideth+1,j=0;j<=Longth+1;j++){
		coord.X=i;
		coord.Y=j;
		SetConsoleCursorPosition(hwnd, coord);
		printf(block);
	}
	for(i=0,j=Longth+1;i<=Wideth+1;i++){
		coord.X=i;
		coord.Y=j;
		SetConsoleCursorPosition(hwnd, coord);
		printf(block);
	}
} 

























