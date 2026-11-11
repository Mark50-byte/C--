#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);// не нужная дичь, если всё запускается, но у меня не запускается как нужно без этого:(
    SetConsoleOutputCP(CP_UTF8);
    
    char start_letter, end_letter; // начальные и конечные горизантальные координаты, а также фигура
    int start_number,end_number;// начальные и конечные вертикальные координаты
    int kol_step = 1;//количество шагов
    int w_king_moved = 0, w_rook_l_moved = 0, w_rook_r_moved = 0;//флаги для рокировки
    int b_king_moved = 0, b_rook_l_moved = 0, b_rook_r_moved = 0;
    
    int pole[8][8]={// поле для вычисления (поправил местами коней и слонов)
        {-4,-2,-3,-5,-6,-3,-2,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 4, 2, 3, 5, 6, 3, 2, 4}// Король (K) - 6; Ферзь (Q) - 5; Ладья (R) - 4; Слон (B) - 3; Конь (N) - 2; Пешка (P) - 1. Отрицательные числа - чёрные
    };
   do{ 
 
    for (int row = 0; row < 8; row++) {// строки
        printf("%d ",8-row);//раставляем числа здесь мы вычитаем, потому что на доске цифры идут сверху вниз, короче наубывание
        for (int col = 0; col < 8; col++) {// столбец
            if ((row + col) % 2 == 0) {// Чередуем цвета: если сумма индексов четная — белая клетка, иначе — черная
                printf("\033[41m");//наш цвет
            } else {
                printf("\033[44m");//наш цвет
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
        printf("\033[0m" "\n");// Сбрасываем цвет и переходим на новую строку иначе у нас весь терминал будет в цвете. absolute sinema
    }

    for (int col2 = 0; col2<8;col2++){// расставляем буквы
        printf("   %c",col2+97);// так как это чар, а ему соотвествует числовое значение в таблице, точнее номер, мы можем с ним выполнять операции сложения и тд
    }
    printf("\n\n");// just space

    if (kol_step % 2 != 0) {
        printf("Ход %d (Белые). ", kol_step);
    } else {
        printf("Ход %d (Чёрные). ", kol_step);
    }
    printf("Введите символ (фигуру), начальные координаты и конечные. Пример: e2 e4  \n");
    if (scanf(" %c%d %c%d",&start_letter,&start_number,&end_letter,&end_number)!=4){// проверяем сколько здесь символов, должно быть 4, в других случаях прог будет просить корректный ввод
        while (getchar() != '\n'); // очищаем буфер ввода от мусора
        printf("Введите координаты как в примере\n");
        continue;
    }

    int start_vert = 8 - start_number;// база, если пользователь пишет 6, то координата будет под строкой 2 и поэтому мы вычитаем потому что у нас идёт массив с 0 и до 8, а цифры раставлены в обратном порядке, так что приходиться вычитать.     
    int start_gor = start_letter - 'a';// преобразовываем в число, у каждого символа есть номер в спец таблице, с ними можно производить разные действия          
    int end_vert = 8 - end_number;// база, если пользователь пишет 6, то координата будет под строкой 2 и поэтому мы вычитаем потому что у нас идёт массив с 0 и до 8, а цифры раставлены в обратном порядке, так что приходиться вычитать.          
    int end_gor = end_letter - 'a';// преобразовываем в число, у каждого символа есть номер в спец таблице, с ними можно производить разные действия            
        if (start_vert >= 0 && start_vert < 8 && start_gor >= 0 && start_gor < 8 && end_gor >= 0 && end_gor < 8 && end_vert >= 0 && end_vert < 8){//проверка выхода за доску  
            int piece = pole[start_vert][start_gor];// по начальным координатам записываем цифру, которая соотвествует нашей фигуре, 1 - пешка и тд
            int saved_end_piece = pole[end_vert][end_gor];//переменная нужная для отката хода, если король под ударом, то игрок не сможет ходить, пока не уберёт из под удара короля
            if (piece == 0) {
                printf("пустая клетка\n");
                continue;
            }
            int my_side, enemy_side;// служат для определения знаков фигур, то есть если белый ходит, то в моё поле записывется значение 1, 
            if (piece > 0) {
            my_side = 1;
            enemy_side = -1;
            } else {
            my_side = -1;
            enemy_side = 1;
            }
            int castling = 0;// флаг рокировки


            if (kol_step%2!=0 && piece <0){// т.к счётчик начинается с 1 мы проверяем чётное ли число или нет, при чётном должны ходить белые иначе чёрные
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
                if  (piece==1){// белый?
                    difference = -1;//ход белых (т. к. они идут вверх значит мы вычитаем)
                    st_posion = 6;//начальная на доске позиция, точнее в массиве для белых пешек
                }else{
                    difference = 1;//ход чёрных (т. к. они идут вверх значит мы складываем)
                    st_posion = 1;//начальная на доске позиция, точнее в массиве для чёрных пешек
                }
                int flag = 0;//флаг, проверяющий правильно сделан ход или нет
                if (difference_x==0 && difference_y==difference){//проверка на ход
                    if (pole[end_vert][end_gor]==0){// проверка на свободное место впереди на 1 клетку
                        flag = 1;// наш флаг, если всё ок
                    }else{
                        printf("в конечной точке стоит фигура\n");// если своя или чужая фигура
                        continue;// штука, точнее оператор, который позволяет пользователю бесконечно ошибаться и при этом не считать это за ход
                    }
                }else if (difference_x==0 && difference_y==difference*2 && st_posion==start_vert){//проверка на 2 хода/ st_posion==start_vert проверка что в начальной позиции   
                    if (pole[end_vert][end_gor]==0 && pole[start_vert+difference][start_gor]==0){
                        flag = 1;// наш флаг, если всё ок
                    }else{
                        printf("в конечной точке стоит фигура или на её пути стоит фигура\n");// если своя или чужая фигура
                        continue;// штука, точнее оператор, который позволяет пользователю бесконечно ошибаться и при этом не считать это за ход
                    }
                }else if(difference_y == difference &&(difference_x==1 || difference_x==-1)){//проверка для рубки
                    if((piece==1 && pole[end_vert][end_gor]<0)||(piece==-1 && pole[end_vert][end_gor]>0)){//проверка рубки вперёд и противоположной фигуры
                        flag = 1;// наш флаг, если всё ок
                    }else{
                        printf("Там стоит твоя фигура или пусто\n");// если попали по своим, то есть наша фигура там стоит
                        continue;// штука, точнее оператор, который позволяет пользователю бесконечно ошибаться и при этом не считать это за ход
                    }
                }
                if (flag==1){//вывод фигуры, если всё ок
                    pole[end_vert][end_gor]=piece;
                    pole[start_vert][start_gor]=0;
                    int number;// нужна для упрощения, чтобы пользователь мог ввести цифру и вместо пешки была другая фигура
                    if (piece == 1 && end_vert == 0) {// для белых
                        printf("впешите фигуру, которую хотите: 2 - конь, 3 - слон, 4 - ладья, 5 - ферзь\n");
                        scanf_s(" %d",&number);
                        while (number <= 1 || number >= 6) {// можно сделать и continue, но из-за путаницы решил через while (из-за огромного количества условий в условиях, я начал путать скобки, хоть скобок стало меньше, всё равно иногда путаю)
                        printf("no-no-no! Введите число от 2 до 5: ");
                        scanf_s(" %d", &number);
                        }
                        pole[end_vert][end_gor] = number;// заменяет пешку другой фигурой
                    }else if (piece == -1 && end_vert == 7) {// для чёрных
                        printf("впешите фигуру, которую хотите: -2 - конь, -3 - слон, -4 - ладья, -5 - ферзь\n");
                        scanf_s(" %d",&number);// игррок вписывает цифру фигуры
                        while (number >= -1 || number <= -6) {// можно сделать и continue, но из-за путаницы решил через while
                        printf("no-no-no! Введите число от -2 до -5: ");
                        scanf_s(" %d", &number);// игррок вписывает цифру фигуры
                        }
                        pole[end_vert][end_gor] = number; // заменяет пешку другой фигурой
                    }
                }else{
                    printf("неверный ход\n");// если не получилось ввести нормально
                    continue;
                }

            }else if (piece == 4 || piece== -4){//проверка ладьи
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                int flag = 1;
                if ((difference_x==0 && difference_y!=0) || (difference_x!=0 && difference_y==0)){//определяем, что ладья движется только в одну сторону
                int step_x = (difference_x > 0) - (difference_x < 0); // Определяем направление движения, то есть если ось х, то будет 1 или -1, взависимости от направления, вверх или вниз
                int step_y = (difference_y > 0) - (difference_y < 0); // Определяем направление движения, то есть если ось у, то будет 1 или -1, взависимости от направления, вверх или вниз
                int cur_x = start_gor + step_x;// проверяем на ход влево-вправо, есть ли там фигура
                int cur_y = start_vert + step_y;// проверяем на ход вперёд-назад, есть ли там фигура
                while (cur_x!=end_gor || cur_y!=end_vert){// идём до конеч коорд, этот цикл нужен для проверки траектории
                    if(pole[cur_y][cur_x]!=0){// если стоит не 0, то есть фигура
                        flag = 0;
                        printf("нельзя перепрыгнуть фигуру, ладья так не умеет\n");
                        break;
                    }
                    cur_x+=step_x;// идём по х, то есть просчитываем шаги
                    cur_y+=step_y;// идём по у, то есть просчитываем шаги
                }
                if (flag == 0) {
                    continue;
                }
                if (flag==1){// проверка нет ли там нашей фигуры
                    int end_kletka = pole[end_vert][end_gor];// коорды конечной точки
                    if (end_kletka==0 || (end_kletka >0 && piece==-4)||(end_kletka <0 && piece==4)){//проверка фигуры и свободной клетки
                        flag = 1;
                    }else{
                        printf("friendly fier\n");// если попали по своим, то есть наша фигура там стоит
                        flag = 0;
                        continue;
                    }
                }
                }else{
                    printf("ладья так не умеет\n");// если не получилось ввести нормально
                    continue;
                }
                if (flag==1){// перемещаем в кон координату
                    pole[end_vert][end_gor]=piece;
                    pole[start_vert][start_gor]=0;
                }
            }else if(piece==3 || piece==-3){//слон, аналогичный код ладье, на удивление
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                int flag = 1;
                if (abs(difference_x)==abs(difference_y) && difference_x != 0){
                int step_x = (difference_x > 0) - (difference_x < 0); // Определяем направление движения, то есть если ось х, то будет 1 или -1, взависимости от направления, вверх или вниз
                int step_y = (difference_y > 0) - (difference_y < 0); // Определяем направление движения, то есть если ось у, то будет 1 или -1, взависимости от направления, вверх или вниз
                int cur_x = start_gor + step_x;// проверяем на ход влево-вправо, есть ли там фигура
                int cur_y = start_vert + step_y;// проверяем на ход вперёд-назад, есть ли там фигура
                while (cur_x!=end_gor || cur_y!=end_vert ){// идём до тех пор, пока не дойдем до заданой точки игроком
                    if(pole[cur_y][cur_x]!=0){//стоит фигура
                        flag = 0;//не ок
                        printf("нельзя перепрыгнуть фигуру, слон так не умеет\n");// если не получилось ввести нормально
                        break;
                    }
                    cur_x+=step_x;// вычитаем или складываем на 1, зависит от направления
                    cur_y+=step_y;// вычитаем или складываем на 1, зависит от направления
                }
                if (flag == 0) {
                    continue;
                }
                if (flag==1){
                    int end_kletka = pole[end_vert][end_gor];
                    if (end_kletka==0 || (end_kletka >0 && piece==-3)||(end_kletka <0 && piece==3)){
                        flag = 1;
                    }else{
                        printf("friendly fier\n");// если попали по своим, то есть наша фигура там стоит
                        flag = 0;
                        continue;
                    }
                }
                }else{
                    printf("слон так не умеет\n");// если не получилось ввести нормально
                    continue;
                }
                if (flag==1){
                    pole[end_vert][end_gor]=piece;
                    pole[start_vert][start_gor]=0;
                }
            }else if(piece==5 || piece==-5){// ферзь
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                int flag = 1;
                if ((abs(difference_x)==abs(difference_y)|| (difference_x==0 && difference_y!=0) || (difference_x!=0 && difference_y==0)) && !(difference_x == 0 && difference_y == 0)){
                int step_x = (difference_x > 0) - (difference_x < 0); // Определяем направление движения, то есть если ось х, то будет 1 или -1, взависимости от направления, вверх или вниз
                int step_y = (difference_y > 0) - (difference_y < 0); // Определяем направление движения, то есть если ось у, то будет 1 или -1, взависимости от направления, вверх или вниз
                int cur_x = start_gor + step_x;// проверяем на ход влево-вправо, есть ли там фигура
                int cur_y = start_vert + step_y;// проверяем на ход вперёд-назад, есть ли там фигура
                while (cur_x!=end_gor || cur_y!=end_vert ){
                    if(pole[cur_y][cur_x]!=0){
                        flag = 0;
                        printf("нельзя перепрыгнуть фигуру, ферзь так не умеет\n");// если не получилось ввести нормально
                        break;
                    }
                    cur_x+=step_x;// просчитываем ход, добав 1 или -1, если по вертик
                    cur_y+=step_y;// аналогично описанию выше, только по горизонтале
                }
                if (flag == 0) {
                    continue;
                }
                if (flag==1){
                    int end_kletka = pole[end_vert][end_gor];
                    if (end_kletka==0 || (end_kletka >0 && piece==-5)||(end_kletka <0 && piece==5)){
                        flag = 1;
                    }else{
                        printf("friendly fier\n");// если попали по своим, то есть наша фигура там стоит
                        flag = 0;
                        continue;
                    }
                }
                }else{
                    printf("ферзь так не умеет\n");// если не получилось ввести нормально
                    continue;
                }
                if (flag == 1) {
                pole[end_vert][end_gor] = piece;
                pole[start_vert][start_gor] = 0;
                }
            }else if(piece==6 || piece==-6){//король
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                if (abs(difference_x)<=1 && abs(difference_y)<=1 && !(difference_x ==0 && difference_y==0)) {
                    int end_kletka = pole[end_vert][end_gor];
                    if (end_kletka==0 || (end_kletka>0 && piece==-6) || (end_kletka<0 && piece==6)){
                        pole[end_vert][end_gor] = piece;
                        pole[start_vert][start_gor] = 0;
                    }else{
                        printf("friendly fier\n");// если попали по своим, то есть наша фигура там стоит
                        continue;
                    }
                }
// проверка рекита
                else if (difference_y == 0 && abs(difference_x) == 2) {// служит для проверки хода короля на 2 хода, когда он идёт строго по горизонтале 
                    int row, king_moved;// определяем строку(нужно для понимания для какого короля совершается ход, то есть рокировка), а вторая переменная является флагом(проверка движения короля, ходил он или нет до этого)
                    if (piece == 6) {// белый
                        row = 7;//строка 7
                        king_moved = w_king_moved;// записываем для белого флаг, ходил ли он или нет(0 или 1)
                    } else {
                        row = 0;// аналогично белому
                        king_moved = b_king_moved;
                    }
                    if (start_vert == row && start_gor == 4 && king_moved == 0) {// проверяем на месте ли король, в той ли он точке где был в начале игры
                        int start_attacked = 0;// снова флаг, который при 1, означает помеху, то есть шах от соперника
                        int dx_c[4] = {0, 0, -1, 1}, dy_c[4] = {-1, 1, 0, 0};// ладья и ферзь, проверка ходов вверх, вниз, влево, вправо
                        for (int i = 0; i < 4; i++) {
                            int r = row + dy_c[i], c = 4 + dx_c[i];// проверяем сразу шаг, не считая клетку короля, мы от него идём в поиски ферзя и ладьи, почему 4? Потому что они стоят на 4 столбике
                            while (r >= 0 && r < 8 && c >= 0 && c < 8) {// диапозон
                            if (pole[r][c] != 0) {// проверка на нахождения фигуры в 1 из 4 направ
                                int p_col;// цвет 
                                if (pole[r][c] > 0) {// проверка чёрный или белый
                                    p_col = 1;  
                                }else { 
                                    p_col = -1; 
                                }
                                if (p_col == enemy_side && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)) {
                                start_attacked = 1;//под боем незя рокера делать
                                }    
                                break;
                            }
                            r += dy_c[i]; c += dx_c[i];// если нет помехи считаем дальше, до конца границ
                            }
                        }
                        int dax_c[4] = {-1, 1, -1, 1}, day_c[4] = {-1, -1, 1, 1};// слон ферзь, аналог  выше только по диоганали
                        for (int i = 0; i < 4; i++) {
                            int r = row + day_c[i], c = 4 + dax_c[i], steps = 1;
                            while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                if (pole[r][c] != 0) {
                                int p_col;
                                if (pole[r][c] > 0) { 
                                    p_col = 1; 
                                } else { 
                                    p_col = -1; 
                                }
                                if (p_col == enemy_side) {
                                        if (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5) {//слон и ферзь
                                        start_attacked = 1;
                                        }
                                        if (abs(pole[r][c]) == 1 && steps == 1 && ((enemy_side == 1 && r > row) || (enemy_side == -1 && r < row))){ // пешка
                                            start_attacked = 1;
                                        }
                                    }
                                    break;
                                }
                                r += day_c[i]; 
                                c += dax_c[i]; 
                                steps+=1;// нужно для пешки, означает, что близко только на 1 клетку, если станет на 2 значит можно сделать рокера
                            }
                        }

                        int kx_c[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, ky_c[8] = {-1, -2, -2, -1, 1, 2, 2, 1};// конь, тоже самре, что и выше, только мы проверяем 8 ходов
                        for (int i = 0; i < 8; i++) {
                            int r = row + ky_c[i], c = 4 + kx_c[i];
                            if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] != 0) {
                                int p_col;
                                if (pole[r][c] > 0) { 
                                    p_col = 1; 
                                } else { 
                                    p_col = -1; 
                                }
                                if (p_col == enemy_side && abs(pole[r][c]) == 2) {
                                start_attacked = 1;
                                }
                            }
                        }
                        if (start_attacked == 0) {//если нам ничего не угрожает
                        // Короткая рокировка (вправо)
                        if (end_gor == 6) {
                            int rook_moved;// ход ладьи при рекете
                            if (piece == 6) { 
                                rook_moved = w_rook_r_moved; // флаг, при котором ладья сидела и никуда не рыпалась, то есть не ходила(белая)
                            } else { 
                                rook_moved = b_rook_r_moved; //чёрная, аналог выше
                            }
                
                            if (rook_moved == 0 && pole[row][7] == 4 * my_side && pole[row][5] == 0 && pole[row][6] == 0) {// проверяем, что меж королём и ладьёй никого и что ладья не ходила, 4 * my_side - это в зависимосити от очереди игроков приобретает - или +, т.к бел сим чёр
                                int mid_attacked = 0;
                                for (int i = 0; i < 4; i++) {
                                    int r = row + dy_c[i], c = 5 + dx_c[i];
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int p_col;
                                            if (pole[r][c] > 0) { 
                                                p_col = 1; 
                                            } else { 
                                                p_col = -1; 
                                            }
                                            if (p_col == enemy_side && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)){ 
                                                mid_attacked = 1;//сделали 1 раз и хватит
                                            }
                                            break;
                                        }
                                        r += dy_c[i]; 
                                        c += dx_c[i];//просчитываем
                                    }
                                }
                                for (int i = 0; i < 4; i++) {
                                    int r = row + day_c[i];
                                    int c = 5 + dax_c[i]; 
                                    int steps = 1;
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int p_col;
                                            if (pole[r][c] > 0) { 
                                                p_col = 1; 
                                            } else { 
                                                p_col = -1; 
                                            }
                                            if (p_col == enemy_side) {
                                                if (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5){
                                                    mid_attacked = 1;  
                                                } 
                                                if (abs(pole[r][c]) == 1 && steps == 1 && ((enemy_side == 1 && r > row) || (enemy_side == -1 && r < row))){
                                                    mid_attacked = 1;
                                                } 
                                            }
                                            break;
                                        }
                                        r += day_c[i]; 
                                        c += dax_c[i]; 
                                        steps+=1;
                                    }
                                }
                                for (int i = 0; i < 8; i++) {
                                    int r = row + ky_c[i], c = 5 + kx_c[i];
                                    if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] != 0) {
                                        int p_col;
                                        if (pole[r][c] > 0) { 
                                            p_col = 1; 
                                        } else { 
                                            p_col = -1; 
                                        }
                                        if (p_col == enemy_side && abs(pole[r][c]) == 2) {
                                            mid_attacked = 1;
                                        }
                                    }
                                }

                                if (mid_attacked == 0) {
                                    pole[row][6] = piece;// ставим короля
                                    pole[row][4] = 0;// обнуляем старые коорд
                                    pole[row][5] = 4 * my_side;// ставим ладью
                                    pole[row][7] = 0;
                                    castling = 1;//пишим что всё тип топ
                                }
                            }
                        }
                        // Длинная рокировка (влево) аналогично выше только на 1 клетку проверки больше
                        else if (end_gor == 2) {
                            int rook_moved;
                            if (piece == 6) { 
                                rook_moved = w_rook_l_moved; 
                            } else { 
                                rook_moved = b_rook_l_moved; 
                            }

                            if (rook_moved == 0 && pole[row][0] == 4 * my_side && pole[row][1] == 0 && pole[row][2] == 0 && pole[row][3] == 0) {
                                int mid_attacked = 0;
                                for (int i = 0; i < 4; i++) {
                                    int r = row + dy_c[i], c = 3 + dx_c[i];
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int p_col;
                                            if (pole[r][c] > 0) { 
                                                p_col = 1; 
                                            } else { 
                                                p_col = -1; 
                                            }
                                            if (p_col == enemy_side && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)) {
                                                mid_attacked = 1;
                                            }
                                            break;
                                        }
                                        r += dy_c[i]; 
                                        c += dx_c[i];
                                    }
                                }
                                for (int i = 0; i < 4; i++) {
                                    int r = row + day_c[i]; 
                                    int c = 3 + dax_c[i]; 
                                    int steps = 1;
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int p_col;
                                            if (pole[r][c] > 0) { 
                                                p_col = 1; 
                                            } else { 
                                                p_col = -1; 
                                            }
                                            if (p_col == enemy_side) {
                                                if (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5) {
                                                    mid_attacked = 1;
                                                }
                                                if (abs(pole[r][c]) == 1 && steps == 1 && ((enemy_side == 1 && r > row) || (enemy_side == -1 && r < row))){ 
                                                    mid_attacked = 1;
                                                }
                                            }
                                            break;
                                        }
                                        r += day_c[i]; 
                                        c += dax_c[i]; 
                                        steps+=1;
                                    }
                                }
                                for (int i = 0; i < 8; i++) {
                                    int r = row + ky_c[i]; 
                                    int c = 3 + kx_c[i];
                                    if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] != 0) {
                                        int p_col;
                                        if (pole[r][c] > 0) { 
                                            p_col = 1; 
                                        } else { 
                                            p_col = -1; 
                                        }
                                        if (p_col == enemy_side && abs(pole[r][c]) == 2) {
                                            mid_attacked = 1;
                                        }
                                    }
                                }

                                if (mid_attacked == 0) {
                                    pole[row][2] = piece;
                                    pole[row][4] = 0;
                                    pole[row][3] = 4 * my_side;
                                    pole[row][0] = 0;
                                    castling = 1;
                                }
                            }
                        }
                    }
                }

                    if (castling == 0) {
                        printf("Рокировка невозможна!\n");
                        continue;
                    }   
                }else{
                printf("король так не умеет\n");
                    continue;
                }

            }else if(piece==2 || piece==-2){// Horse
                int difference_x = end_gor-start_gor;//разница по горизантали
                int difference_y = end_vert-start_vert;//разница по вертикали
                if ((abs(difference_x)==2 && abs(difference_y)==1) || (abs(difference_x)==1 && abs(difference_y)==2)){//буква г, чтобы не просчитывать каждую легче взять по модолю. Иначе нужно было бы перебирать -2 и 1, 2 и -1 и т.д
                    int end_kletka = pole[end_vert][end_gor];// конечная клетка, куда встанет фигура
                    if (end_kletka==0 || (end_kletka>0 && piece==-2) || (end_kletka<0 && piece==2)){// проверяем для белого коня и чёрного конечную клетку, соотвествует она условию или нет
                        pole[end_vert][end_gor] = piece;// заменяем просчитаную клетку на фигуру
                        pole[start_vert][start_gor] = 0;// заменяем начальную клетку на 0
                    }else{
                        printf("friendly fier\n");// если попали по своим, то есть наша фигура там стоит
                        continue;
                    }
                }else{
                    printf("конь так не умеет\n");// если не получилось ввести нормально
                    continue;
                }
            }
            // шах и откат хода, в случае шаха
            
            int king, emenem;// король и перемен эменем не репер, а значение которое позволяет проверять противополож фигуры, типо для белого короля - чёрные 
            int k_r = 10;// коорд короля, но в начале можно вывести любые, я взял 10, можно 12, -1 и тд, кроме 0-7
            int k_c = 10;// коорд короля, но в начале можно вывести любые, я взял 10, можно 12, -1 и тд, кроме 0-7
            if (kol_step%2!=0){
                king = 6;// Mr.White
            }else{
                king = -6;// чёрный
            }
            if (king ==6){// проверка короля
                emenem =-1;// если белый король, значит противник чёрный, и проверять будем только чёрных
            }else{
                emenem = 1;// если чёрный король, значит противник белый, и проверять будем только белый
            }
            for (int r = 0; r < 8; r++) {// проверяем где находится король по строке
                for (int c = 0; c < 8; c++) {// проверяем где находится король по столбу
                    if (pole[r][c] == king) { // ищем короля и если находим идём дальше
                        k_r = r; // находим строку
                        k_c = c; // находим столбик
                        break; 
                    }
                }
            }
            int shah=0;
            if (k_r!=10){//проверяем есть ли король в этой клетке
                // Направления для ладьи/ферзя (прямые)
                int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};//всего 4 варианта вниз, вверх, влево, вправо
                for (int i = 0; i < 4; i++) {// так как всего 4 направления мы проверяем каждое
                    int r = k_r + dy[i];// траектория по y, строкам
                    int c = k_c + dx[i];// траектория по x, столбцам
                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {// ищем пока не найдем фигуру или же просто пройдем весь маршрут и не обнаружим угрозы
                        if (pole[r][c] != 0) {// смотрим на клетку и спрашиваем, есть ли там фигура
                            int piece_color;// пременная отвечающая за цвет, чтобы просчитывать толь фигуры соперника а не все (короче чтобы не делать себе же шах)
                            if (pole[r][c] > 0) {// проверка больше ли число отвечающее за фигуру, если да то белые, иначе чёрные
                                piece_color = 1;  // фигура белая
                            } else {
                                piece_color = -1; // фигура черная
                            } 
                            if (piece_color == emenem && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)) {//проверяем цвет фигуры и саму фигуру (ладья это или ферзь)
                                shah = 1;// наш флаг
                            }
                            break;
                        }
                        r += dy[i]; // взависимости от направления мы будем вычитать -1(алгебраическое сложение) или складывать соотвественно упрёмся в условие выхода из цикла, смещение по у строка
                        c += dx[i];// взависимости от направления мы будем вычитать -1(алгебраическое сложение) или складывать соотвественно упрёмся в условие выхода из цикла, смещение по х столбец
                    }
                }
                // Направления для слона/ферзя/пешки (диагонали)
                int dax[4] = {-1, 1, -1, 1}, day[4] = {-1, -1, 1, 1};//всего 4 варианта вниз по диоганал влево и вправо, вверх по диоганал влево и вправо
                for (int i = 0; i < 4; i++) {// так как всего 4 направления мы проверяем каждое
                    int r = k_r + day[i];// траектория по y, строкам
                    int c = k_c + dax[i];// траектория по x, столбцам
                    int steps = 1;//переменная отвечающая за расстояние пешки
                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {// ищем пока не найдем фигуру или же просто пройдем весь маршрут и не обнаружим угрозы
                        if (pole[r][c] != 0) {// смотрим на клетку и спрашиваем, есть ли там фигура
                            int piece_color;// пременная отвечающая за цвет, чтобы просчитывать толь фигуры соперника а не все (короче чтобы не делать себе же шах)
                            if (pole[r][c] > 0) {// проверка больше ли число отвечающее за фигуру, если да то белые, иначе чёрные
                                piece_color = 1;  // фигура белая
                            } else {
                                piece_color = -1; // фигура черная
                            } 
                            if (piece_color == emenem && (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5)){ // проверяем цвет и слона с ферзём
                                shah = 1;// наш флаг
                            }
                            if (piece_color == emenem && abs(pole[r][c]) == 1 && steps == 1 && ((emenem == 1 && r > k_r) || (emenem == -1 && r < k_r))) {// проверяем цвет и пешку, а ёще, что не мало важно, идёт проверка хода на 1 иначе была проверка как у слона и чтобы пешка противополож проверяла ход вперёд
                                shah = 1;// наш флаг
                            }
                            break;
                        }
                        r += day[i]; 
                        c += dax[i]; 
                        steps+=1;//
                    }
                }
                // Направления для коня
                int kx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, ky[8] = {-1, -2, -2, -1, 1, 2, 2, 1};// всего 8 комбинаци, то есть направлений
                for (int i = 0; i < 8; i++) {// не нужно никаких вайлов, потому что мы буквально можем походить на 8 разных клеток
                    int r = k_r + ky[i];// траектория по y, строкам
                    int c = k_c + kx[i];// траектория по x, столбцам
                    int piece_color;
                    if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                        if (pole[r][c] > 0 ){
                            piece_color = 1;  // фигура белая
                        }else{
                            piece_color = -1; // фигура черная
                        }
                        if (piece_color == emenem && abs(pole[r][c]) == 2){
                            shah = 1;
                        }
                    }
                }
                // Проверка сближения королей (чтобы короли не вставали вплотную друг к другу)
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) {// не считаем клетку короля
                            continue;
                        }
                        int r = k_r + dr;
                        int c = k_c + dc;// перебираем вокруг короля 
                        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                            if (pole[r][c] == -king) {// проверка двух корол
                                shah = 1;// чтобы не столкнулись короли, так то понятно, что не шах, но так проще, чем создавать доп переменную
                            }
                        }
                    }
                }
            }

            // Если наш король оказался под шахом — откатываем ход обратно, это для рокировки
            if (shah == 1) {
                pole[start_vert][start_gor] = piece;
                pole[end_vert][end_gor] = saved_end_piece;// для этого нужна была переменая сейв, чтобы обратно поставить фигуру
                if (castling == 1) {
                    if (end_gor == 6) {
                        pole[start_vert][7] = 4 * my_side;
                        pole[start_vert][5] = 0;
                    } else if (end_gor == 2) {
                        pole[start_vert][0] = 4 * my_side;
                        pole[start_vert][3] = 0;
                    }
                }
                printf("Нельзя оставлять своего короля под шахом! Сделайте другой ход.\n");
                continue;
            }

            
            if (piece == 6) { 
                w_king_moved = 1; 
            }
            if (piece == -6) { 
                b_king_moved = 1; 
            }
            if (piece == 4 && start_vert == 7 && start_gor == 0) { // в данном случае проверяем рокер лево, там где даб правую, чтобы можно было ходить в любой момент
                w_rook_l_moved = 1; 
            }
            if (piece == 4 && start_vert == 7 && start_gor == 7) { 
                w_rook_r_moved = 1; 
            }
            if (piece == -4 && start_vert == 0 && start_gor == 0) { 
                b_rook_l_moved = 1; 
            }
            if (piece == -4 && start_vert == 0 && start_gor == 7) { 
                b_rook_r_moved = 1; 
            }

            //мат, проверка
            int enemy_king;
            if (enemy_side == 1) {
                enemy_king = 6;
            } else {
                enemy_king = -6;
            }
            int ek_r = 10, ek_c = 10;// будующие коорд соперника
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if (pole[r][c] == enemy_king) {
                        ek_r = r;//запись коорд соперника
                        ek_c = c;
                        break;
                    }
                }
            }
            int enemy_shah = 0;// для соперника просчитываем, до этого была проверка своего короля, чтобы ты не мог попасть под шах, а так аналогично выше
            if (ek_r != 10) {
                int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
                for (int i = 0; i < 4; i++) {
                    int r = ek_r + dy[i], c = ek_c + dx[i];
                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                        if (pole[r][c] != 0) {
                            int piece_color;
                            if (pole[r][c] > 0) { piece_color = 1; } else { piece_color = -1; }
                            if (piece_color == my_side && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)) {
                                enemy_shah = 1;
                            }
                            break;
                        }
                        r += dy[i]; c += dx[i];
                    }
                }
                int dax[4] = {-1, 1, -1, 1}, day[4] = {-1, -1, 1, 1};
                for (int i = 0; i < 4; i++) {
                    int r = ek_r + day[i], c = ek_c + dax[i], steps = 1;
                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                        if (pole[r][c] != 0) {
                            int piece_color;
                            if (pole[r][c] > 0) { piece_color = 1; } else { piece_color = -1; }
                            if (piece_color == my_side && (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5)) {
                                enemy_shah = 1;
                            }
                            if (piece_color == my_side && abs(pole[r][c]) == 1 && steps == 1 && ((my_side == 1 && r > ek_r) || (my_side == -1 && r < ek_r))) {
                                enemy_shah = 1;
                            }
                            break;
                        }
                        r += day[i]; c += dax[i]; steps += 1;
                    }
                }
                int kx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, ky[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
                for (int i = 0; i < 8; i++) {
                    int r = ek_r + ky[i], c = ek_c + kx[i];
                    if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] != 0) {
                        int piece_color;
                        if (pole[r][c] > 0) { piece_color = 1; } else { piece_color = -1; }
                        if (piece_color == my_side && abs(pole[r][c]) == 2) {
                            enemy_shah = 1;
                        }
                    }
                }
            }

            //проверка мат это или пат
            int has_legal_moves = 0;
            for (int r1 = 0; r1 < 8; r1++) {
                for (int c1 = 0; c1 < 8; c1++) {
                    int p = pole[r1][c1];
                    if (p == 0) continue;
                    int p_side;
                    if (p > 0) { 
                        p_side = 1; 
                    } else { 
                        p_side = -1; 
                    }
                    if (p_side != enemy_side) continue;// так можно оказывается, я не знал :(

                    // Пробуем походить этой фигурой на любую клетку доски (r2, c2)
                    for (int r2 = 0; r2 < 8; r2++) {
                        for (int c2 = 0; c2 < 8; c2++) {
                            if (r1 == r2 && c1 == c2) {
                            continue;
                            }
                            
                            int target = pole[r2][c2];
                            if (target != 0) {
                                int t_side;
                                if (target > 0) { 
                                    t_side = 1; 
                                } else { 
                                    t_side = -1; 
                                }
                                if (t_side == enemy_side) {
                                    continue;
                                } // своих не бьём
                            }

                            int dx_m = c2 - c1;
                            int dy_m = r2 - r1;
                            int can_move = 0;

                            if (abs(p) == 1) { // пешка соперника
                                int dir, st_r;
                                if (p == 1) { 
                                    dir = -1; 
                                    st_r = 6; 
                                } else { 
                                    dir = 1; 
                                    st_r = 1; 
                                }
                                if (dx_m == 0 && dy_m == dir && target == 0) { 
                                    can_move = 1; 
                                }
                                else if (dx_m == 0 && dy_m == dir * 2 && r1 == st_r && target == 0 && pole[r1 + dir][c1] == 0) { 
                                    can_move = 1; 
                                }
                                else if (abs(dx_m) == 1 && dy_m == dir && target != 0) { 
                                    can_move = 1; 
                                }
                            } else if (abs(p) == 2) { // конь соперника
                                if ((abs(dx_m) == 2 && abs(dy_m) == 1) || (abs(dx_m) == 1 && abs(dy_m) == 2)) { 
                                    can_move = 1; 
                                }
                            } else if (abs(p) == 6) { // король соперника
                                if (abs(dx_m) <= 1 && abs(dy_m) <= 1) { 
                                    can_move = 1; 
                                }
                            } else if (abs(p) == 4 || abs(p) == 3 || abs(p) == 5) { // ладья, слон, ферзь
                                int ok_dir = 0;
                                if (abs(p) == 4 && (dx_m == 0 || dy_m == 0)) ok_dir = 1;
                                if (abs(p) == 3 && abs(dx_m) == abs(dy_m)) ok_dir = 1;
                                if (abs(p) == 5 && (dx_m == 0 || dy_m == 0 || abs(dx_m) == abs(dy_m))) ok_dir = 1;
                                if (ok_dir == 1) {
                                    int sx = (dx_m > 0) - (dx_m < 0);
                                    int sy = (dy_m > 0) - (dy_m < 0);
                                    int cx = c1 + sx, cy = r1 + sy;
                                    int blocked = 0;
                                    while (cx != c2 || cy != r2) {
                                        if (pole[cy][cx] != 0) { blocked = 1; break; }
                                        cx += sx; cy += sy;
                                    }
                                    if (blocked == 0) can_move = 1;
                                }
                            }

                            if (can_move == 1) {
                                // Делаем пробный ход соперника
                                pole[r2][c2] = p;
                                pole[r1][c1] = 0;

                                // Ищем короля соперника после пробного хода
                                int tk_r = 10, tk_c = 10;
                                for (int rr = 0; rr < 8; rr++) {
                                    for (int cc = 0; cc < 8; cc++) {
                                        if (pole[rr][cc] == enemy_king) { tk_r = rr; tk_c = cc; break; }
                                    }
                                }

                                // Проверяем, остался ли король соперника под шахом
                                int still_shah = 0;
                                int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
                                for (int i = 0; i < 4; i++) {
                                    int r = tk_r + dy[i], c = tk_c + dx[i];
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int pc;
                                            if (pole[r][c] > 0) { pc = 1; } else { pc = -1; }
                                            if (pc == my_side && (abs(pole[r][c]) == 4 || abs(pole[r][c]) == 5)) still_shah = 1;
                                            break;
                                        }
                                        r += dy[i]; c += dx[i];
                                    }
                                }
                                int dax[4] = {-1, 1, -1, 1}, day[4] = {-1, -1, 1, 1};
                                for (int i = 0; i < 4; i++) {
                                    int r = tk_r + day[i], c = tk_c + dax[i], steps = 1;
                                    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                                        if (pole[r][c] != 0) {
                                            int pc;
                                            if (pole[r][c] > 0) { pc = 1; } else { pc = -1; }
                                            if (pc == my_side && (abs(pole[r][c]) == 3 || abs(pole[r][c]) == 5)) still_shah = 1;
                                            if (pc == my_side && abs(pole[r][c]) == 1 && steps == 1 && ((my_side == 1 && r > tk_r) || (my_side == -1 && r < tk_r))) still_shah = 1;
                                            break;
                                        }
                                        r += day[i]; c += dax[i]; steps += 1;
                                    }
                                }
                                int kx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, ky[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
                                for (int i = 0; i < 8; i++) {
                                    int r = tk_r + ky[i], c = tk_c + kx[i];
                                    if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] != 0) {
                                        int pc;
                                        if (pole[r][c] > 0) { pc = 1; } else { pc = -1; }
                                        if (pc == my_side && abs(pole[r][c]) == 2) still_shah = 1;
                                    }
                                }
                                for (int dr = -1; dr <= 1; dr++) {
                                    for (int dc = -1; dc <= 1; dc++) {
                                        if (dr == 0 && dc == 0) continue;
                                        int r = tk_r + dr, c = tk_c + dc;
                                        if (r >= 0 && r < 8 && c >= 0 && c < 8 && pole[r][c] == -enemy_king) still_shah = 1;
                                    }
                                }

                                // Откатываем пробный ход назад
                                pole[r1][c1] = p;
                                pole[r2][c2] = target;

                                if (still_shah == 0) {
                                    has_legal_moves = 1;
                                    break;
                                }
                            }
                        }
                        if (has_legal_moves == 1) break;
                    }
                }
                if (has_legal_moves == 1) break;
            }

            if (has_legal_moves == 0) {
                if (enemy_shah == 1) {
                    printf("\n");
                    if (my_side == 1) {
                        printf("ШАХ И МАТ! ПОБЕДИЛИ БЕЛЫЕ!\n");
                    } else {
                        printf("ШАХ И МАТ! ПОБЕДИЛИ ЧЁРНЫЕ!\n");
                    }
                    printf("\n");
                } else {
                    printf("\n");
                    printf("ПАТ! НИЧЬЯ!\n");
                    printf("\n");
                }
                break; // завершаем партию
            }

            if (enemy_shah == 1) {
                Beep(750, 300);
                printf("!!! ШАХ КОРОЛЮ !!!\n");// вывод предупреждения шаха
            }

            kol_step+=1; // передаём ход следующему игроку!
        
        }else {
            printf("Неверные координаты доски!\n");
        }
    }while(kol_step<21);
    if (kol_step == 21) { // если игра прервалась не из-за мата или пата
    printf("\nНичья! Победила дружба\n");
    }

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
    return 0;
} 

//♚♛♜♝♞♟ - фигуры    
//♔♕♖♗♘♙
