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
#define _CRT_SECURE_NO_WARNINGS
#define ESC 27
#define ENTER 13
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h>
void fillSubString(int);                                                    // аргумент - положение в исходной строке
int stringCmp(int);                                                         // сравнение подстроки с инвертированным фрагментом исходной строки
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
    printf("\nВаша строка: ");
    showString(str, length);                                                // вывод строки
    printf("\nДлина строки - %d\n", length);
    //destructor();
    printf("\nНажми ENTER...\n");
    int i, compareResult, 
        found = 0;
    for (i = 0; i <= length - 2*lengthSS; i++)
    {
        do
        {
            fillSubString(i);
            showString(subStr, lengthSS);
            printf("|");
            compareResult = stringCmp(i);
            if (compareResult)
            {
                lengthSS++;
                found++;                                                    // увеличиваем счётчик совпадений
                printf("\nНайден инвертированный фрагмент (%d)!\n", found);
            }
        } while (compareResult);

        lengthSS = 3;
    }
    printf("\nНажми ESC...\n");
    while (_getch() != ESC);
    return 0;
}

int stringCmp(int begin)													// сравнение подстроки с инвертированным
{                                                                           // фрагментом исходной строки
    int count = 0;                                                          // количество совпадения символов
    char *reset = str,
        *resetSS = subStr;                                                  // запомним начальный адрес подстроки
    str += begin + lengthSS;                                                // сдвиг указателя в исходной строке на длину подстроки
    do
    {
        if (!(lengthSS - count))
        {
            str = reset;
            subStr = resetSS;
            return count;
        }
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
    } while (str - reset < length);
    str = reset;
    subStr = resetSS;
    return 0;
}

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

int enterString()                                                           // посимвольный ввод строки 
{
    int i;
    for (i = 0; i < length; i++, str++)
    {
        *str = _getch();
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

void showString(char *string, int stringLength)                             // вывод строки (аргументы, строка и её длина)
{
    int i;
    for (i = 0; i < stringLength; i++)
    {
        printf("%c", *string++);
    }
    return;
}

void destructor()
{
    free(str);
    free(subStr);
    return;
}
