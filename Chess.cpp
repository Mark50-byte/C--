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
                printf("\033[41m");
            } else {
                printf("\033[44m");
            }
                // Выводим фигуру в зависимости от числа в pole[row][col]
            int abs_piece = pole[row][col];
         
            switch (abs_piece) {
                case 1: printf(" ♟  "); break; // Пешка
                case 2: printf(" ♞  "); break; // Конь
                case 3: printf(" ♝  "); break; // Слон
                case 4: printf(" ♜  "); break; // Ладья
                case 5: printf(" ♛  "); break; // Ферзь
                case 6: printf(" ♚  "); break; // Король
                case -1: printf(" ♙  "); break; // Пешка
                case -2: printf(" ♘  "); break; // Конь
                case -3: printf(" ♗  "); break; // Слон
                case -4: printf(" ♖  "); break; // Ладья
                case -5: printf(" ♕  "); break; // Ферзь
                case -6: printf(" ♔  "); break; // Король
                default: printf("    "); break; // Пустая клетка (0)
            }
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
//♔♕♖♗♘♙