#include <stdlib.h>
#include "vector.h"
#include "functions.h"

int main(){

    struct RingInfo* intRing = Create(&intOne, &intZero, &readInt, &sumInt,
            &minusInt, &multiplyInt, &numbers_multiplyInt, &freeInt, &printInt);

    struct RingInfo* doubleRing = Create(&doubleOne, &doubleZero, &readDouble, &sumDouble,
            &minusDouble, &multiplyDouble, &numbers_multiplyDouble, freeDouble, &printDouble);

    struct RingInfo* complexRing = Create(&complexOne, &complexZero, &readComplex, &sumComplex,
            &minusComplex, &multiplyComplex, &numbers_multiplyComplex, &freeComplex, &printComplex);

    struct Vector** mas = malloc(0);
    int* n = malloc(sizeof(int));
    *n = 0;
    int key = 1; int check; int type; int n1; int n2; int val;

    while (key == 1) {
        printf("\nВведите номер одной из доступных команд: 1 - добавить элемент в конец массив, "
               "2 - удалить элемент из массива, 3 - вывести массив на экран, 4 - вывести скалярное произведение двух "
               "векторов массива, 5 - закончить работу с программой\n");
        do {
            printf("Введите число от 1 до 5: ");
            check = scanf("%d", &type);
            my_flush();
        } while ((check != 1) || (type < 0 || type > 5));

        switch (type) {
            case 1: // добавление элемента
                printf("Введите номер одного из вариантов добавляемого элемента: 1 - единичный вектор, "
                       "2 - введенный вручную вектор, 3 - сумма двух существующих векторов, 4 - разность двух "
                       "существующих векторов, 5 - обратный одному из существующих векторов вектор, 6 - один из "
                       "существующих векторов умноженный на целое число, 7 - векторное произведение двух существующих векторов\n");
                do {
                    printf("Введите число от 1 до 7: ");
                    check = scanf("%d", &type);
                    my_flush();
                } while ((check != 1) || (type < 0 || type > 7));

                switch (type) { // что добавляем
                    case 1: // единичный вектор
                        printf("Введите тип элементов единичного вектора: 1 - целое число, 2 - вещественное число, 3 - комплексное число\n");
                        do {
                            printf("Введите число от 1 до 3: ");
                            check = scanf("%d", &type);
                            my_flush();
                        } while ((check != 1) || (type < 0 || type > 3));

                        switch (type) { // int, double или complex
                            case 1: // int
                                printf("Введите тип единичного вектора: число от 1 до 3\n");
                                do {
                                    printf("Введите число от 1 до 3: ");
                                    check = scanf("%d", &type);
                                    my_flush();
                                } while ((check != 1) || (type < 0 || type > 3));

                                switch (type) {
                                    case 1:
                                        mas = push_back(mas, n, E1(intRing));
                                        break;
                                    case 2:
                                        mas = push_back(mas, n, E2(intRing));
                                        break;
                                    default:
                                        mas = push_back(mas, n, E3(intRing));
                                        break;
                                }
                                break;
                            case 2: // double
                                printf("Введите тип единичного вектора: число от 1 до 3\n");
                                do {
                                    printf("Введите число от 1 до 3: ");
                                    check = scanf("%d", &type);
                                    my_flush();
                                } while ((check != 1) || (type < 0 || type > 3));

                                switch (type) {
                                    case 1:
                                        mas = push_back(mas, n, E1(doubleRing));
                                        break;
                                    case 2:
                                        mas = push_back(mas, n, E2(doubleRing));
                                        break;
                                    default:
                                        mas = push_back(mas, n, E3(doubleRing));
                                        break;
                                }
                                break;
                            default: // complex
                                printf("Введите тип единичного вектора: число от 1 до 3\n");
                                do {
                                    printf("Введите число от 1 до 3: ");
                                    check = scanf("%d", &type);
                                    my_flush();
                                } while ((check != 1) || (type < 0 || type > 3));

                                switch (type) {
                                    case 1:
                                        mas = push_back(mas, n, E1(complexRing));
                                        break;
                                    case 2:
                                        mas = push_back(mas, n, E2(complexRing));
                                        break;
                                    default:
                                        mas = push_back(mas, n, E3(complexRing));
                                        break;
                                }
                                break;
                        }
                        break;
                    case 2: // вводимый с клавиатуры вектор
                        printf("Введите тип элементов вводимого вектора: 1 - целое число, 2 - вещественное число, 3 - комплексное число\n");
                        do {
                            printf("Введите число от 1 до 3: ");
                            check = scanf("%d", &type);
                            my_flush();
                        } while ((check != 1) || (type < 0 || type > 3));

                        switch (type) { // int, double или complex
                            case 1: // int
                                mas = push_back(mas, n, FromKeyboard(intRing));
                                break;
                            case 2: // double
                                mas = push_back(mas, n, FromKeyboard(doubleRing));
                                break;
                            default: // complex
                                mas = push_back(mas, n, FromKeyboard(complexRing));
                                break;
                        }
                        break;
                    case 3: // сумма векторов
                        if (*n < 2){
                            printf("Массив слишком мал, добавьте элементы\n");
                            break;
                        }
                        printf("Введите номера двух элементов массива - векторов одного типа\n");
                        do {
                            printf("Введите номер первого слогаемого в массиве - число от 0 до %d: ", *n - 1);
                            check = scanf("%d", &n1);
                            my_flush();
                        } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                        do {
                            printf("Введите номер второго слогаемого в массиве - число от 0 до %d, кроме %d: ", *n - 1, n1);
                            check = scanf("%d", &n2);
                            my_flush();
                        } while ((check != 1) || (n2 < 0 || n2 > *n - 1 || n2 == n1));

                        if (getRingInfo(mas[n1]) == getRingInfo(mas[n2]))
                            mas = push_back(mas, n, sum(mas[n1], mas[n2]));
                        else{
                            printf("Типы векторов не совпадают, операция невозможна\n");
                            break;
                        }
                        break;
                    case 4: // разность векторов
                        if (*n < 2){
                            printf("Массив слишком мал, добавьте элементы\n");
                            break;
                        }
                        printf("Введите номера двух элементов массива - векторов одного типа\n");
                        do {
                            printf("Введите номер уменьшаемого в массиве - число от 0 до %d: ", *n - 1);
                            check = scanf("%d", &n1);
                            my_flush();
                        } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                        do {
                            printf("Введите номер вычитаемого в массиве - число от 0 до %d, кроме %d: ", *n - 1, n1);
                            check = scanf("%d", &n2);
                            my_flush();
                        } while ((check != 1) || (n2 < 0 || n2 > *n - 1 || n2 == n1));

                        if (getRingInfo(mas[n1]) == getRingInfo(mas[n2]))
                            mas = push_back(mas, n, subtraction(mas[n1], mas[n2]));
                        else{
                            printf("Типы векторов не совпадают, операция невозможна\n");
                            break;
                        }
                        break;
                    case 5: // обратный к вектору
                        if (*n < 1){
                            printf("Массив слишком мал, добавьте элементы\n");
                            break;
                        }
                        do {
                            printf("Введите номер элемента в массиве - число от 0 до %d: ", *n - 1);
                            check = scanf("%d", &n1);
                            my_flush();
                        } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                        mas = push_back(mas, n, minus(mas[n1]));
                        break;
                    case 6: // вектор умноженный на целое число
                        if (*n < 1){
                            printf("Массив слишком мал, добавьте элементы\n");
                            break;
                        }
                        do {
                            printf("Введите номер элемента в массиве - число от 0 до %d: ", *n - 1);
                            check = scanf("%d", &n1);
                            my_flush();
                        } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                        do {
                            printf("Введите целое число - множитель: ");
                            check = scanf("%d", &val);
                            my_flush();
                        } while ((check != 1) || (val > 10000 || val < -10000));

                        mas = push_back(mas, n, multiply(mas[n1], val));
                        break;
                    case 7: // векторное произведение
                        if (*n < 2){
                            printf("Массив слишком мал, добавьте элементы\n");
                            break;
                        }
                        printf("Введите номера двух элементов массива - векторов одного типа\n");
                        do {
                            printf("Введите номер первого множителя в массиве - число от 0 до %d: ", *n - 1);
                            check = scanf("%d", &n1);
                            my_flush();
                        } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                        do {
                            printf("Введите номер второго множителя в массиве - число от 0 до %d, кроме %d: ", *n - 1, n1);
                            check = scanf("%d", &n2);
                            my_flush();
                        } while ((check != 1) || (n2 < 0 || n2 > *n - 1 || n2 == n1));

                        if (getRingInfo(mas[n1]) == getRingInfo(mas[n2]))
                            mas = push_back(mas, n, vector_multiply(mas[n1], mas[n2]));
                        else{
                            printf("Типы векторов не совпадают, операция невозможна\n");
                            break;
                        }
                        break;
                }
                break;
            case 2: // удаление элемента
                if (*n < 1){
                    printf("Массив слишком мал, добавьте элементы\n");
                    break;
                }
                do {
                    printf("Введите номер удаляемого элемента в массиве - число от 0 до %d: ", *n - 1);
                    check = scanf("%d", &n1);
                    my_flush();
                } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                mas = delete(mas, n, n1);
                break;

            case 3: // вывод массива на экран
                print_mas(mas, n);
                break;

            case 4: // скалярное произведение
                if (*n < 2){
                    printf("Массив слишком мал, добавьте элементы\n");
                    break;
                }
                printf("Введите номера двух элементов массива - векторов одного типа\n");
                do {
                    printf("Введите номер первого вектора в массиве - число от 0 до %d: ", *n - 1);
                    check = scanf("%d", &n1);
                    my_flush();
                } while ((check != 1) || (n1 < 0 || n1 > *n - 1));

                do {
                    printf("Введите номер второго вектора в массиве - число от 0 до %d, кроме %d: ", *n - 1, n1);
                    check = scanf("%d", &n2);
                    my_flush();
                } while ((check != 1) || (n2 < 0 || n2 > *n - 1 || n2 == n1));

                if (getRingInfo(mas[n1]) == getRingInfo(mas[n2]))
                    scalar_multiply(mas[n1], mas[n2]);
                else{
                    printf("Типы векторов не совпадают, операция невозможна\n");
                    break;
                }
                break;
            case 5: // окончание работы программы
                key = 0;
                break;
        }
    }



    free_mas(mas, n);
    free(n);
    free(complexRing);
    free(intRing);
    free(doubleRing);
}
