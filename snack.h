#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h> 
#define Wideth 50               //游戏区域的宽度 
#define Longth 15                //游戏区域的长度 
#define block "0"                 //墙壁 
#define body "#"             //蛇的身体 
#define blank " "
#define sfront "1"         //蛇头 
#define UP 115
#define DOWN 119                //定义方向的控制AScII值 
#define LEFT 97
#define RIGHT 100
#define speed 0.5                              //当前蛇的刷新速度，秒为单位 
#define start_long 3                         //蛇的初始节点长度 
struct snack{                               //构建蛇的单向链表 
	int x;
	int y;
	int direction;
	struct snack *next;
};
struct snack* catch_snack(struct snack* head,COORD coord){        //将蛇和一个节点连接，返回头指针 
	struct snack* p;
	p=(struct snack*)malloc(sizeof(struct snack));
	p->x=coord.X;
	p->y=coord.Y;
	p->direction=head->direction;
	p->next=head;
	head=p;
	return head;
}
struct snack* creat_snack(){               //创建一条蛇的链表，返回头指针 
	struct snack* head;
	COORD coord;
	int i;
	head=(struct snack*)malloc(sizeof(struct snack));
	head->next=NULL; 
	head->direction=RIGHT;
	head->x=Wideth/2;
	head->y=Longth/2;
	for(i=1;i<start_long;i++){
		coord.X=head->x+1;
		coord.Y=head->y;
		head=catch_snack(head,coord);
	} 
	return head;
}
void print_snack(struct snack* head){                              //将一条蛇输出到屏幕 
	struct snack* p;
	p=head;
	HANDLE hwnd=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	for(;p!=NULL;p=p->next){
		if(p==head){
			coord.X=p->x;
			coord.Y=p->y;
			SetConsoleCursorPosition(hwnd,coord);
			printf(sfront);
		}
		else{
			coord.X=p->x;
			coord.Y=p->y;
			SetConsoleCursorPosition(hwnd,coord);
			printf(body);	
		}
	}
/*	coord.X=Wideth+3;
	coord.Y=0;
	SetConsoleCursorPosition(hwnd,coord);
	printf("==%d==%d==",head->x,head->y);             这是一段打印蛇的头位置的调试程序！       */ 
} 
void wipe_snack(struct snack* head){                              //将一条蛇从屏幕擦掉 
	struct snack* p;
	p=head;
	HANDLE hwnd=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	for(;p!=NULL;p=p->next){
		coord.X=p->x;
		coord.Y=p->y;
		SetConsoleCursorPosition(hwnd,coord);
		printf(" ");
	}
}
struct snack* snack_turn(struct snack* head,int dre){                //蛇的转弯 
	struct snack* p;
	COORD coord;
	if(dre==UP&&head->direction==DOWN||dre==DOWN&&head->direction==UP||dre==LEFT&&head->direction==RIGHT||dre==RIGHT&&head->direction==LEFT)
		dre=head->direction;
	switch(dre){
		case UP: coord.X=head->x;coord.Y=head->y+1;head->direction=UP;head=catch_snack(head,coord);break;
		case DOWN: coord.X=head->x;coord.Y=head->y-1;head->direction=DOWN;head=catch_snack(head,coord);break;
		case LEFT: coord.X=head->x-1;coord.Y=head->y;head->direction=LEFT;head=catch_snack(head,coord);break;
		case RIGHT: coord.X=head->x+1;coord.Y=head->y;head->direction=RIGHT;head=catch_snack(head,coord);break;
	}
	for(p=head;p!=NULL;p=p->next)
		if(p->next->next==NULL){
			p->next=NULL;
			break;
		}
	return head;	 
}





















