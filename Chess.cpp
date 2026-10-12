#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    char start_letter, end_letter; // начальные и конечные горизантальные координаты, а также фигура
    int start_number,end_number;// начальные и конечные вертикальные координаты
    int kol_step = 1;//количество шагов

    int pole[8][8]={// поле для вычисления
        {-4,-3,-2,-5,-6,-2,-3,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 1, 1, 1, 1, 1, 1, 1},
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
                case 1: printf(" ♟  "); break; //1 case 1: printf(" 1  "); break;
                case 2: printf(" ♞  "); break; //2 case 1: printf(" 2  "); break;
                case 3: printf(" ♝  "); break; //3 case 1: printf(" 3  "); break;
                case 4: printf(" ♜  "); break; //4 case 1: printf(" 4  "); break;
                case 5: printf(" ♛  "); break; //5 case 1: printf(" 5  "); break;
                case 6: printf(" ♚  "); break; //6 case 1: printf(" 6  "); break;
                case -1: printf(" ♙  "); break; //-1 case 1: printf(" -1  "); break;
                case -2: printf(" ♘  "); break; //-2 case 1: printf(" -2  "); break;
                case -3: printf(" ♗  "); break; //-3 case 1: printf(" -3  "); break;
                case -4: printf(" ♖  "); break; //-4 case 1: printf(" -4  "); break;
                case -5: printf(" ♕  "); break; //-5 case 1: printf(" -5  "); break;
                case -6: printf(" ♔  "); break; //-6 case 1: printf(" -6  "); break;
                default: printf("    "); break; 
            }
        
    }
        printf("\033[0m" "\n");// Сбрасываем цвет и переходим на новую строку
    }

    for (int col2 = 0; col2<8;col2++){// расставляем буквы
        printf("   %c",col2+97);
    }
    printf("\n\n");

    printf("Введите символ (фигуру), начальные координаты и конечные. Пример: e2 e4  \n");
    if (scanf_s("%c%d %c%d",&start_letter,1,&start_number,&end_letter,1,&end_number)!=4){
        printf("Введите координаты как в примере\n");
        continue;
    }

    int start_vert = 8 - start_number;// база, если пользователь пишет 6, то координата будет под строкой 2      
    int start_gor = start_letter - 'a';// преобразовываем в число          
    int end_vert = 8 - end_number;          
    int end_gor = end_letter - 'a';           
        if (start_vert >= 0 && start_vert < 8 && start_gor >= 0 && start_gor < 8 && end_gor >= 0 && end_gor < 8 && end_vert >= 0 && end_vert < 8){//проверка выхода за доску  
            int piece = pole[start_vert][start_gor];

            if (kol_step%2!=0 && piece <0){
                printf("сейчас ход белых\n");
                continue;
            }
            if (kol_step%2==0 && piece >0){
                printf("сейчас ход чёрных\n");
                continue;
            }
            if (piece ==1 || piece ==-1){//проверка пешек
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                int difference;//ход, то есть разница которая получается, взависимости от вычитания координат, у белых всегда -, а у чёрных +.
                int st_posion;//нач поз
                if  (piece==1){
                    difference = -1;//ход белых (т. к. они идут вверх значит мы вычитаем)
                    st_posion = 6;//начальная на доске позиция, точнее в массиве для белых пешек
                }else{
                    difference = 1;//ход чёрных (т. к. они идут вверх значит мы складываем)
                    st_posion = 1;//начальная на доске позиция, точнее в массиве для чёрных пешек
                }
                int flag = 0;//флаг, проверяющий правильно сделан ход или нет
                if (difference_x==0 && difference_y==difference){//проверка на ход
                    if (pole[end_vert][end_gor]==0){
                        flag = 1;
                    }else{
                        printf("в конечной точке стоит фигура\n");
                        continue;
                    }
                }else if (difference_x==0 && difference_y==difference*2 && st_posion==start_vert){//проверка на 2 хода
                    if (pole[end_vert][end_gor]==0 && pole[start_vert+difference][start_gor]==0){
                        flag = 1;
                    }else{
                        printf("в конечной точке стоит фигура или на её пути стоит фигура\n");
                        continue;
                    }
                }else if(difference_y == difference &&(difference_x==1 || difference_x==-1)){//проверка для рубки
                    if((piece==1 && pole[end_vert][end_gor]<0)||(piece==-1 && pole[end_vert][end_gor]>0)){
                        flag = 1;
                    }else{
                        printf("Там стоит твоя фигура\n");
                        continue;
                    }
                }
                if (flag==1){//вывод фигуры, если всё ок
                    pole[end_vert][end_gor]=piece;
                    pole[start_vert][start_gor]=0;
                    kol_step += 1; // счётчик хода (шагов)
                }else{
                    printf("неверный ход\n");
                    continue;
                }

            }else if (piece == 4 || piece== -4){//проверка ладьи
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                int flag = 1;
                if ((difference_x==0 && difference_y!=0) || (difference_x!=0 && difference_y==0)){//определяем, что ладья движется только в одну сторону
                int step_x = (difference_x > 0) - (difference_x < 0); // Определяем направление движения, то есть если ось х, то будет 0
                int step_y = (difference_y > 0) - (difference_y < 0); // Определяем направление движения, то есть если ось у, то будет 1 или -1, взависимости от направления, вверх или вниз
                int cur_x = start_gor + step_x;// проверяем на ход влево-вправо, есть ли там фигура
                int cur_y = start_vert + step_y;// проверяем на ход вперёд-назад, есть ли там фигура
                while (cur_x!=end_gor || cur_y!=end_vert){
                    if(pole[cur_y][cur_x]!=0){
                        flag = 0;
                        printf("нельзя перепрыгнуть фигуру, ладья так не умеет\n");
                        break;
                    }
                    cur_x+=step_x;
                    cur_y+=step_y;
                }
                if (flag==1){
                    int end_kletka = pole[end_vert][end_gor];
                    if (end_kletka==0 || (end_kletka >0 && piece==-4)||(end_kletka <0 && piece==4)){
                        flag = 1;
                    }else{
                        printf("friendly fier\n");
                        flag = 0;
                    }
                }
                }
                if (flag==1){
                    pole[end_vert][end_gor]=piece;
                    pole[start_vert][start_gor]=0;
                    kol_step+=1;
                }
            }else if (piece==0){
                printf("пустая клетка\n");
            }
        
        }else {
            printf("Неверные координаты доски!\n");
        }
   }while(kol_step<6);//число шагов, ходов
    return 0;
} 

//♚♛♜♝♞♟ - фигуры    
//♔♕♖♗♘♙