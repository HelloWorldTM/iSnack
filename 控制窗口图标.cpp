#include <windows.h>
#include <stdio.h>
#include <conio.h>

void loopout(HANDLE hwnd,COORD coord)
{
    SetConsoleCursorPosition(hwnd, coord);             //设置窗口光标的位置 
    printf("1");
}

int main()
{
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);                //获取当前窗口的句柄 
    COORD coord;                                                  //COORD类型的光标坐标的结构体  
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
        case 13://按下回车键清屏
            system("cls");
            break;
        case 0xE0:
            switch (getch()) 
            {
                case 72://上
                    coord.Y--;
                    loopout(hwnd, coord);
                    break;

                case 80://下 
                    coord.Y++;
                    loopout(hwnd, coord);
                    break;
                case 97://左
                    coord.X--;
                    loopout(hwnd, coord);
                    break;
                case 100://右
                    coord.X++;
                    loopout(hwnd, coord);
                    break;
            }
        }
    }
    //getchar();
    return 0;
}

