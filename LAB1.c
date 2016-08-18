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
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h>
#define STR_SIZE    60
#define ESC         27
#define ENTER       13
#define EXIT_CODE   -1

typedef char* string;
void memFree(string, string);                                               // освобождение памяти из-под строк
void gotoxy(int, int);
void showString(string, int);                                               // аргументы - строка и её длина
void fillSubString(string, int, string, int);
void init(string, int);
string stringCmp(string, string, int);                                 // аргумент - положение в исходной строке
int enterString(string, int);                                               // ввод строки
///-------------------------------------------------------------------------
int main()
{
    SetConsoleTitleA("LAB1 by vk.com/KIVINEW");
    setlocale(LC_ALL, "russian");
    string str;										                        // исходная строка
    string fragment;                                                        // подстрока фрагмента для поиска совпадений
    int length = STR_SIZE;													// длина строки
    int lengthFrag = 3;                                                     // минимальная длина фрагмента
    str = (string) malloc(length * sizeof(char));						    // память для исходной строки
    fragment = (string) malloc(length / 2 * sizeof(char));                  // память для подстроки вдвое меньше
    init(str, length);
    init(fragment, length / 2);
    printf("Введи строку (ESC - выход):  ");
    length = enterString(str, length);                                      // ввод строки вернёт её длину
    if (length == EXIT_CODE)
    {
        memFree(str, fragment);
        return 0;
    }
    system("cls");
    printf("\nВаша строка: ");
    showString(str, length);                                                // вывод строки
    int i = 0,
        flag = 0;
    string resultFragment = NULL,
        lastFragment = NULL;
    do                                                                      // цикл по всей введённой строке
    {
        do                                                                  // цикл
        {
            fillSubString(str, i, fragment, lengthFrag);
            resultFragment = stringCmp(str + i, fragment, lengthFrag);      // функция возвращает указатель на фрагмент
            if (resultFragment)
            {
                lengthFrag++;                                               // увеличиваем длину фрагмента для следующей проверки
                lastFragment = resultFragment;
                flag = 1;
            }
            else
            {
                if (lengthFrag > 3)
                {
                    lengthFrag--;
                    fillSubString(str, i, fragment, lengthFrag);
                }
                resultFragment = flag?lastFragment:NULL;
                flag = 0;
            }
        } while (flag);
        if (resultFragment)
        {
            printf("\n\nСовпадение: ");
            showString(str + i, lengthFrag);
            printf(" ---> ");
            showString(resultFragment, lengthFrag);
            i += lengthFrag;
        }
        lengthFrag = 3;
    } while (i++ <= length - 2 * lengthFrag);// нужно пересмотреть это условие, т.к. lengthFrag изменяется в теле цикла !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    printf("\n\nНажми ENTER...");
    while (_getch() != ENTER);
    system("cls");
    return main();                                                          // зацикливание программы (выход по ESC)
}
// поиск сегмента строки, совпадающего с инвертированной подстрокой
string stringCmp(string str, string fragment, int lengthFrag)
{
    int count = 0;                                                          // количество совпадений символов
    string resetFragment = fragment;                                        // сохраним начальный адрес подстроки
    str += lengthFrag;                                                      // сдвиг указателя в исходной строке на длину подстроки
    do
    {
        if (*fragment == *str)
        {   /// при совпадении символов 
            str++;
            fragment++;                                                     // сдвигаются указатели обеих строк
            count++;                                                        // и количество совпадений увеличивается.
            continue;                                                       // следующая итерация
        }
        else
        {   /// при несовпадении символов
            fragment = resetFragment;                                       // сброс указателя на фрагмент
            if (count >= lengthFrag)                                        // если ранее найдено полное совпадение фрагмента
            {                                                               // ...
                return str - count;                                         // ...то его и возвращаем
            }
            count = 0;                                                      // обнуляем количество совпадений
        }
        str++;                                                              // сдвиг относительно начала строки
    } while (*str && *fragment);                                            // проверка на выход за пределы строки
    return count >= lengthFrag?str - count:NULL;                            // если совпадение полное вернём указатель, иначе - NULL
}
// создание подстроки путём присваивания инвертированного фрагмента исходной строки
void fillSubString(string str, int begin, string fragment, int lengthFrag)
{
    int i = 1, invert;
    do
    {
        invert = begin + lengthFrag - i;
        *fragment++ = *(str + invert);                                      // присваиваем подстроке инвертированный фрагмент исходной строки
    } while (i++ < lengthFrag);
    fragment -= lengthFrag;
    return;
}
// инициализация пустых строк
void init(string str, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        *str++ = '\0';
    }
    return;
}
// посимвольный ввод строки 
int enterString(string str, int length)                                     // возвращает длину введённой строки
{                                                                           // ввод невизуальных символов игнорируется
    int i = 0;
    do
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
    } while (i++ < length && str++);
    str -= i;
    return i;
}
// вывод строки (аргументы: строка и её длина)
void showString(string str, int length)
{
    if (str)
    {
        int i;
        for (i = 0; i < length; i++)
        {
            printf("%c", *str++);
        }
    }
    return;
}
// освободить память из под строк
void memFree(string str, string fragment)
{
    free(str);
    free(fragment);
    return;
}

void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}
