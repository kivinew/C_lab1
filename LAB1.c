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
void memFree(char*, char*);                                                 // освобождение памяти из-под строк
void gotoxy(int, int);
void showString(char *, int);                                               // аргументы - строка и её длина
void fillSubString(char *, int, char *, int);
char* stringCmp(char *, int, char*, int);                                   // аргумент - положение в исходной строке
int enterString(char*, int);                                                // ввод строки
///-------------------------------------------------------------------------

int main()
{
    SetConsoleTitleA("LAB1 by vk.com/KIVINEW");
    setlocale(LC_ALL, "russian");
    char *str;										                        // исходная строка
    char *subStr;                                                           // подстрока фрагмента для поиска совпадений
    int length = 40;														// длина строки
    int lengthSS = 3;                                                       // длина подстроки
    str = (char*) malloc(length * sizeof(char));						    // память для исходной строки
    subStr = (char*) malloc(length / 2 * sizeof(char));                     // память для подстроки вдвое меньше
    init(str, length);
    init(subStr, lengthSS);
    printf("Введите строку:\t");
    length = enterString(str, length);                                      // ввод строки вернёт её длину
    if (length == EXIT_CODE)
    {
        memFree(str, subStr);
        return 0;
    }
    printf("\nВаша строка: ");
    showString(str, length);                                                // вывод строки
    int i,
        found = 0;
    char *compareResult;
    for (i = 0; i <= length - 2 * lengthSS; i++)
    {
        do
        {
            fillSubString(str, i, subStr, lengthSS);
            compareResult = stringCmp(str, length - i, subStr, lengthSS);
            if (compareResult)
            {
                gotoxy(13 + i, 2 + found);
                showString(str + i, lengthSS);
                printf(" ---> ");
                showString(subStr, lengthSS);
                found++;                                                    // увеличиваем счётчик совпадений
                lengthSS++;                                                 // и длину фрагмента для следующей проверки
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
char* stringCmp(char *str, int length, char *subStr, int lengthSS)
{
    int count = 0, shift;                                                   // количество совпадения символов
    char *reset = str,                                                      // сохраним начальный адрес строки
        *resetSS = subStr;                                                  // и начальный адрес подстроки
    str += lengthSS;                                                        // сдвиг указателя в исходной строке на длину подстроки
    if (lengthSS > 3)                                                       // если уже найдено 
    {                                                                       // совпадение трёх символов
        shift = lengthSS - 3;                                               // то сдвигаем указатель строки на эти три символа
        str += shift;
        subStr += shift;
    }
    do
    {
        if (*subStr == *str)
        {   // при совпадении символов 
            subStr++;                                                       // 
            count++;                                                        // и количество совпавших символов
        }                                                                   // увеличивается
        else
        {   // при несовпадении символов
            subStr = resetSS;                                               // сброс указателя подстроки в начало
            if (count >= 3)                                                 // если ранее найдено полное совпадение фрагмента
            {                                                               //
                return str;                                                 // то его и возвращаем
            }
            count = 0;                                                      // обнуляем количество совпадений
        }
        // сдвиг относительно начала строки

        if (str - reset > length)                                           // проверка на выход за пределы строки
        {
            subStr = resetSS;
            if (count < 3)
            {
                count = 0;
                str = NULL;
            }
            return str;
        }
        str++;
    } while (lengthSS - count != 0);                                        // проверка на выход за пределы подстроки
    //subStr = resetSS;
    return str - count;
}
// создание подстроки путём присваивания инвертированного фрагмента исходной строки
void fillSubString(char *str, int begin, char *subStr, int lengthSS)		// заполнение дополнительного массива
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
int enterString(char *str, int length)
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
void memFree(char *str, char *subStr)
{
    free(str);
    free(subStr);
    return;
}

void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}
