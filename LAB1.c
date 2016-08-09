/* Кудрявцев И.В. Поток 09.2015. Вариант №5.
Вариант задания реализовать в виде функции, использующей для работы со строкой
только указатели и операции вида *p++, p++ и т.д. Если функция возвращает строку или ее
фрагмент, то это также необходимо сделать через указатель.
Вариант №9.
Функция находит в строке пары инвертированных фрагментов (например, "123apr" и "rpa321")
и возвращает указатель на первый. С помощью функции найти все пары.
Примечание:
функция, производящая поиск некоторого фрагмента переменной размерности,
может либо запоминать эту размерность во внешней переменной, либо отмечать каким-либо
символом окончание этого фрагмента в самой строке.*/
#define ESC         27
#define ENTER       13
#define EXIT_CODE   -1
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h>
void fillSubString(int);                                                    // аргумент - положение в исходной строке
int stringCmp(int);                                                         // сравнение подстроки с фрагментом исходной строки
void destructor();
int enterString();                                                          // ввод строки
void showString(char *, int);                                               // вывод строки (аргументы, строка и её длина)
///-------------------------------------------------------------------------
char *str;										                            // исходная строка
char *subStr;                                                               // подстрока фрагмента для поиска совпадений
int length = 40;															// длина строки
int lengthSS = 3;                                                           // длина подстроки
int main()
{
    SetConsoleTitleA("LAB1 by vk.com/KIVINEW");
    setlocale(LC_ALL, "russian");
    str = (char*) malloc(length * sizeof(char));						    // память для исходной строки
    subStr = (char*) malloc(length / 2 * sizeof(char));                     // память для подстроки вдвое меньше
    printf("Введите строку:\t");
    length = enterString();                                                 // ввод строки
    if (length == EXIT_CODE)
    {
        destructor();
        return 0;
    }
    printf("\nВаша строка: ");
    showString(str, length);                                                // вывод строки
    int i, compareResult, 
        found = 0;
    for (i = 0; i <= length - 2*lengthSS; i++)
    {
        do
        {
            fillSubString(i);
            compareResult = stringCmp(i);
            if (compareResult)
            {
                printf("\nНайден инвертированный фрагмент: ");
                showString(subStr, lengthSS);
                found++;                                                    // увеличиваем счётчик совпадений
                lengthSS++;
            }
        } while (compareResult);
        lengthSS = 3;
    }
    printf("\nНажми ENTER...\n");
    while (_getch() != ENTER);
    system("cls");
    length = 40;
    main();                                                                 // зацикливание программы (выход по ESC)
    return 0;
}
// сравнение инвертированной подстроки с фрагментом исходной строки
int stringCmp(int begin)													
{ 
    int count = 0;                                                          // количество совпадения символов
    char *reset = str,
        *resetSS = subStr;                                                  // запомним начальный адрес подстроки
    str += begin + lengthSS;                                                // сдвиг указателя в исходной строке на длину подстроки
    do
    {
        if (*subStr == *str)                                                
        {   // при совпадении символов 
            str++;                                                          // происходит сдвиг обоих
            subStr++;                                                       // указателей
            count++;                                                        // и количество совпавших символов
        }                                                                   // увеличивается
        else
        {   // при несовпадении символов
            str++;                                                          // сдвигаем указатель в исходной строке
            subStr = resetSS;                                               // сброс указателя подстроки в начало
            count = 0;                                                      // обнуляем количество совпадений
        }
        if (str - reset >= length)
        {
            str = reset;
            subStr = resetSS;
            if (count < 3) count = 0;
            return count;
        }
    } while (lengthSS - count != 0);
    str = reset;
    subStr = resetSS;
    return count;
}
// создание подстроки путём присваивания инвертированного фрагмента исходной строки
void fillSubString(int begin)				                                // заполнение дополнительного массива
{
    int j, shift;
    for (j = 1; j <= lengthSS; j++)
    {
        shift = begin + lengthSS - j;
        *subStr++ = *(str + shift);                                         // присваиваем подстроке инвертированный фрагмент исходной строки
    }
    subStr -= lengthSS;
    return;
}
// посимвольный ввод строки 
int enterString()                                                           
{                                                                           // возвращает длину введённой строки
    int i;                                                                  // ввод невизуальных символов игнорируется
    for (i = 0; i < length; i++, str++)
    {
        *str = _getch();
        if (*str == ESC)
        {
            str -= i;
            return EXIT_CODE;
        }
        if (*str == ENTER) break;
        if (*str < '!')
        {
            str--;
            i--;
            continue;
        }
        printf("%c", *str);
    }
    str -= i;
    return i;
}
// вывод строки (аргументы: строка и её длина)
void showString(char *string, int stringLength)                             
{
    int i;
    for (i = 0; i < stringLength; i++)
    {
        printf("%c", *string++);
    }
    return;
}
// освободить память из под строк
void destructor()
{
    free(str);
    free(subStr);
    return;
}
