#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    char chess_piece, start_letter, end_letter; 
    int start_number,end_number;
    int kol = 1;
    
    
// поле для вычисления 
    int pole[8][8]={
        {-4,-3,-2,-5,-6,-2,-3,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {4,3,2,5,6,2,3,4}
    };// Король (K) - 6; Ферзь (Q) - 5; Ладья (R) - 4; Слон (B) - 3; Конь (N) - 2; Пешка (P) - 1

    for (int row = 0; row < 8; row++) {
        printf("%d ",8-row);
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {// Чередуем цвета: если сумма индексов четная — белая клетка, иначе — черная
                printf("\033[40m");
            } else {
                printf("\033[47m");
            }
            if (row==1)// street for black
                printf("\033[30m ♟  ");
            else if (row==0 && col == 0 || row==0 && col==7)
                printf("\033[30m ♜  ");
            else if (row==0 && col==1 || row==0 && col==6)
                printf("\033[30m ♞  ");
            else if (row==0 && col==2 || row==0 && col==5)
                printf("\033[30m ♝  ");
            else if (row==0 && col==3)
                printf("\033[30m ♛  ");
            else if (row==0 && col==4)
                printf("\033[30m ♚  ");

            else if (row==6)// street for white
                printf("\033[37m ♟  ");
            else if (row==7 && col == 0 || row==7 && col==7)
                printf("\033[37m ♜  ");
            else if (row==7 && col==1 || row==7 && col==6)
                printf("\033[37m ♞  ");
            else if (row==7 && col==2 || row==7 && col==5)
                printf("\033[37m ♝  ");
            else if (row==7 && col==3)
                printf("\033[37m ♛  ");
            else if (row==7 && col==4)
                printf("\033[37m ♚  ");
            
            else
            printf("    ");// Выводим 4 пробела, чтобы клетка получилась квадратной 
        }
        
        
        printf("\033[0m" "\n");// Сбрасываем цвет и переходим на новую строку
    }

    for (int col2 = 0; col2<8;col2++){// расставляем буквы
        printf("   %c",char(col2+97));
    }
    // printf("Введите символ(фигуру), число и букву без пробела). Пример: B1f\n");
    // scanf_s("%c%d%c",&chess_piece,&number,&letter);
    

    return 0;
}   
//♚♛♜♝♞♟ - фигуры    
