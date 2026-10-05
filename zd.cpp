#include <stdio.h>
#include <windows.h>

int main()
{
    // Настройка кодировки для корректного вывода UTF-8 символов фигур в Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    char chess_piece; 
    char start_letter, dest_letter; 
    int start_number, dest_number;
    int kol = 1; // Счетчик полуходов (1-20)
    
    // ИСПРАВЛЕНО: Явно указан размер массива [8][8] и добавлен знак равенства
    int pole[8][8] = {
        {-4,-3,-2,-5,-6,-2,-3,-4}, // Ряд 8 (индекс 0)
        {-1,-1,-1,-1,-1,-1,-1,-1}, // Ряд 7 (индекс 1)
        {0,0,0,0,0,0,0,0},         // Ряд 6
        {0,0,0,0,0,0,0,0},         // Ряд 5
        {0,0,0,0,0,0,0,0},         // Ряд 4
        {0,0,0,0,0,0,0,0},         // Ряд 3
        {1,1,1,1,1,1,1,1},         // Ряд 2 (индекс 6)
        {4,3,2,5,6,2,3,4}          // Ряд 1 (индекс 7)
    };

    do {
        // --- 1. ОТРИСОВКА ДОСКИ НА ОСНОВЕ МАССИВА POLE ---
        printf("\n");
        for (int row = 0; row < 8; row++) {
            printf("%d ", 8 - row); // Вывод номера ряда перед доской
            
            for (int col = 0; col < 8; col++) {
                // Чередуем фоновые цвета клеток
                if ((row + col) % 2 == 0) {
                    printf("\033[40m"); // Черный фон
                } else {
                    printf("\033[47m"); // Белый/серый фон
                }

                // Задаем цвет самой фигуры (31m - красный для черных, 34m - синий для белых)
                if (pole[row][col] < 0) printf("\033[31m"); 
                if (pole[row][col] > 0) printf("\033[34m");

                // Выводим фигуру в зависимости от числа в pole[row][col]
                int abs_piece = (pole[row][col] < 0) ? -pole[row][col] : pole[row][col];
                
                switch (abs_piece) {
                    case 1: printf(" ♟  "); break; // Пешка
                    case 2: printf(" ♞  "); break; // Конь
                    case 3: printf(" ♝  "); break; // Слон
                    case 4: printf(" ♜  "); break; // Ладья
                    case 5: printf(" ♛  "); break; // Ферзь
                    case 6: printf(" ♚  "); break; // Король
                    default: printf("    "); break; // Пустая клетка (0)
                }
            }
            printf("\033[0m\n"); // Сброс цвета в конце строки
        }

        // Вывод букв под доской
        printf("  ");
        for (int col2 = 0; col2 < 8; col2++) {
            printf("  %c ", (char)(col2 + 'a'));
        }
        printf("\n\n");

        // --- 2. ОЧЕРЕДЬ ХОДА И ВВОД ДАННЫХ ---
        int is_white_turn = (kol % 2 != 0);
        printf("--- ХОД №%d (Ходят %s) ---\n", (kol + 1) / 2, is_white_turn ? "БЕЛЫЕ" : "ЧЕРНЫЕ");
        printf("Введите ход в формате: Фигура Откуда Куда (Пример: P e2 e4 или N b1 c3):\n");
        
        // Считываем фигуру, начальную букву и ряд, конечную букву и ряд
        // Примечание: Если компилируете в Visual Studio, замените scanf на scanf_s
        if (scanf(" %c %c%d %c%d", &chess_piece, &start_letter, &start_number, &dest_letter, &dest_number) != 5) {
            printf("Ошибка ввода! Попробуйте еще раз.\n");
            // Очистка буфера вручную для совместимости
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        // --- 3. ПЕРЕВОД КООРДИНАТ В ИНДЕКСЫ МАССИВА ---
        int from_col = start_letter - 'a';
        int from_row = 8 - start_number;
        int to_col = dest_letter - 'a';
        int to_row = 8 - dest_number;

        // Проверка выхода за границы доски
        if (from_col < 0 || from_col > 7 || from_row < 0 || from_row > 7 ||
            to_col < 0 || to_col > 7 || to_row < 0 || to_row > 7) {
            printf("Ошибка: Координаты выходят за пределы доски!\n");
            continue;
        }

        // Проверка: есть ли фигура в начальной клетке
        if (pole[from_row][from_col] == 0) {
            printf("Ошибка: Клетка %c%d пуста!\n", start_letter, start_number);
            continue;
        }

        // Проверка: ходит ли игрок своими фигурами
        if ((is_white_turn && pole[from_row][from_col] < 0) || (!is_white_turn && pole[from_row][from_col] > 0)) {
            printf("Ошибка: Вы не можете ходить фигурами соперника!\n");
            continue;
        }

        // Проверка рубки своих фигур
        if (pole[to_row][to_col] != 0) {
            if ((is_white_turn && pole[to_row][to_col] > 0) || (!is_white_turn && pole[to_row][to_col] < 0)) {
                printf("Ошибка: Нельзя рубить свои же фигуры!\n");
                continue;
            } else {
                printf("!!! Фигура срублена !!!\n");
            }
        }

        // --- 4. ПЕРЕМЕЩЕНИЕ ФИГУРЫ В МАССИВЕ ---
        pole[to_row][to_col] = pole[from_row][from_col]; // Переносим фигуру на новую клетку
        pole[from_row][from_col] = 0;                    // Старую клетку очищаем

        kol++; // Переходим к следующему полуходу

    } while (kol <= 20);

    printf("Игра завершена! Сделано 20 полуходов.\n");
    return 0;
}
