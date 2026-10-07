#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    char chess_piece, start_letter, end_letter; 
    int start_number,end_number;
    int kol_step = 1;//количество шагов
    int pole[8][8]={// поле для вычисления
        {-4,-3,-2,-5,-6,-2,-3,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 4, 3, 2, 5, 6, 2, 3, 4}// Король (K) - 6; Ферзь (Q) - 5; Ладья (R) - 4; Слон (B) - 3; Конь (N) - 2; Пешка (P) - 1. Отрицательные числа - чёрные
    };
   do{ 
 
    for (int row = 0; row < 8; row++) {
        printf("%d ",8-row);
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {// Чередуем цвета: если сумма индексов четная — белая клетка, иначе — черная
                printf("\033[41m");
            } else {
                printf("\033[44m");
            }   
            int pieces = pole[row][col];// Выводим фигуру в зависимости от числа в pole[row][col] (от координат)
            switch (pieces) {//проверка на фигуру
                case 1: printf(" ♟  "); break; 
                case 2: printf(" ♞  "); break; 
                case 3: printf(" ♝  "); break; 
                case 4: printf(" ♜  "); break; 
                case 5: printf(" ♛  "); break; 
                case 6: printf(" ♚  "); break; 
                case -1: printf(" ♙  "); break; 
                case -2: printf(" ♘  "); break; 
                case -3: printf(" ♗  "); break; 
                case -4: printf(" ♖  "); break; 
                case -5: printf(" ♕  "); break; 
                case -6: printf(" ♔  "); break; 
                default: printf("    "); break; 
            }
        
    }
        printf("\033[0m" "\n");// Сбрасываем цвет и переходим на новую строку
    }

    for (int col2 = 0; col2<8;col2++){// расставляем буквы
        printf("   %c",char(col2+97));
    }
    printf("\n\n");

    printf("Введите символ (фигуру), начальные координаты и конечные. Пример: P e2 e4 кол ходов:  ",kol_step);
    if (scanf_s(" %c %c%d %c%d",&chess_piece,1,&start_letter,1,&start_number,&end_letter,1,&end_number)!=5){
        printf("Введите координаты как в примере\n");
        continue;
    }

    int start_vert = start_letter - 'a';       // прикиньте char - char будет int, преобразование символов в цифры и дальгеёшего вычисления по коорд
    int start_gor = 8 - start_number;         // база, если пользователь пишет 6, то координата будет под строкой 2
    int end_vert = end_letter - 'a';         
    int end_gor = 8 - end_number;            

        if (start_vert >= 0 && start_vert < 8 && start_gor >= 0 && start_gor < 8 &&//проверка выхода за доску
            end_gor >= 0 && end_gor < 8 && end_vert >= 0 && end_vert < 8) {
            pole[end_gor][end_vert] = pole[start_gor][start_vert];//меняем координаты - это основа для вывода фигуры, должно присудствовать для пешки, ладьи и тд
            pole[start_gor][start_vert] = 0;
            
            kol_step += 1; // счётчик хода (шагов)
        } else {
            printf("Неверные координаты доски!\n");//для оленей, которые думают, что я делаю с нейронке, вся логика продумывается мной! И да у меня бомбит, потому что я сидел 2 часа и пытался, сделать так, чтобы шахматы ходили. Вобщем пиздец братья и сёстры
            // P.s вместо аваций меня обвиняют в бездумном вайбкодинге, обидно:(
        }
    }while(kol_step<4);//число шагов, ходов
    return 0;
}   
//♚♛♜♝♞♟ - фигуры    
//♔♕♖♗♘♙