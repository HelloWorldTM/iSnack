#include <windows.h>
#include <stdio.h>
#include <conio.h>

void loopout(HANDLE hwnd,COORD coord)
{
    SetConsoleCursorPosition(hwnd, coord);             //���ô��ڹ���λ�� 
    printf("1");
}

int main()
{
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);                //��ȡ��ǰ���ڵľ�� 
    COORD coord;                                                  //COORD���͵Ĺ������Ľṹ��  
    coord.X = 0;
    coord.Y = 0;
    loopout(hwnd, coord);

    SetConsoleCursorPosition(hwnd,coord);
    while (1)
    {
    	//Sleep(1000);
    	kb=getch();
        switch(kb)
        {
        case 13://���»س�������
            system("cls");
            break;
        case 0xE0:
            switch (getch()) 
            {
                case 72://��
                    coord.Y--;
                    loopout(hwnd, coord);
                    break;

                case 80://�� 
                    coord.Y++;
                    loopout(hwnd, coord);
                    break;
                case 97://��
                    coord.X--;
                    loopout(hwnd, coord);
                    break;
                case 100://��
                    coord.X++;
                    loopout(hwnd, coord);
                    break;
            }
        }
    }
    //getchar();
    return 0;
}

