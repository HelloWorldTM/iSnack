#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h> 
#define Wideth 50               //��Ϸ����Ŀ�� 
#define Longth 15                //��Ϸ����ĳ��� 
#define block "0"                 //ǽ�� 
#define body "#"             //�ߵ����� 
#define blank " "
#define sfront "1"         //��ͷ 
#define UP 115
#define DOWN 119                //���巽��Ŀ���AScIIֵ 
#define LEFT 97
#define RIGHT 100
#define speed 0.5                              //��ǰ�ߵ�ˢ���ٶȣ���Ϊ��λ 
#define start_long 3                         //�ߵĳ�ʼ�ڵ㳤�� 
struct snack{                               //�����ߵĵ������� 
	int x;
	int y;
	int direction;
	struct snack *next;
};
struct snack* catch_snack(struct snack* head,COORD coord){        //���ߺ�һ���ڵ����ӣ�����ͷָ�� 
	struct snack* p;
	p=(struct snack*)malloc(sizeof(struct snack));
	p->x=coord.X;
	p->y=coord.Y;
	p->direction=head->direction;
	p->next=head;
	head=p;
	return head;
}
struct snack* creat_snack(){               //����һ���ߵ���������ͷָ�� 
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
void print_snack(struct snack* head){                              //��һ�����������Ļ 
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
	printf("==%d==%d==",head->x,head->y);             ����һ�δ�ӡ�ߵ�ͷλ�õĵ��Գ���       */ 
} 
void wipe_snack(struct snack* head){                              //��һ���ߴ���Ļ���� 
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
struct snack* snack_turn(struct snack* head,int dre){                //�ߵ�ת�� 
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





















