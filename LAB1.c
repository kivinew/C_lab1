﻿/* Кудрявцев И.В. Поток 09.2015. Вариант №5.
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
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h>

void fill();
int find();
void proc(char []);
void destructor();
void enterString();
int  p;                                                                     // переменная - точка отсчёта
char *str;										                            // исходная строка
char *subStr;                                                               // подстрока фрагмента для поиска совпадений
int length = 40;															// длина подстроки
int main()
{
    SetConsoleTitleA( "LAB1 by vk.com/KIVINEW" ) ;
	setlocale(LC_ALL, "russian");
    str = (char*) malloc(length * sizeof(char));						    // память для исходной строки
    //str = " ";
    subStr = (char*) malloc(length / 2 * sizeof(char));                     // память для подстроки вдвое меньше
    //int result;
	printf("Введите строку:\t");
    enterString();
    printf("\nВаша строка: ");
    int i;
    for (i = 0; i<length; i++)
    {
        printf("%c",*str++);
    }
    str -= i;
    destructor();
    exit(0);
	//printf("\n\n");
	//printf("Поиск фрагментов: \n");
	//for (p = 0; *ptr++!='\0'; p++)				                        // проходим по всей строке
	{
		fill();
		//result = find();
        proc(str);
		//if (result!=0)
		//{
		//	printf("Указатель: %p\t", str+p);
		//	printf("Индекс повтора = %d \t", result);
		//	printf("Фрагмент: %s\n", subStr);
		//}
	}
	//printf("\nПовторов больше нет\n");
	_getch();
	return 0;
}

void fill()				                                                    // заполнение дополнительного массива
{
	int i, j;
	for (i = p, j = length-1; j>=0; i++, j--)
	{
		*(subStr+j) = *(str+i);
	}
	return;
}

int find()																	// поиск фрагмента
{
	int i, j, start;
	i = 0;
	j = p;
	start = j;
	while (*(subStr+i)!='\0')
	{
		if (*(subStr+i)==*(str+j))
		{
			i++;
			j++;
		}
		else
		{
			j++;
			start = j;
			i = 0;
		}
		if (*(str+j)=='\0')
			return 0;
	}
	if (i==0) 
		return 0;
	else 
		return start;
}

void proc(char c[]) {
    int i;
    for (i = 0; c[i] != 0; i++)
    {
        if (c[i] != ' ' && c[i] == c[i + 1])
        {                         
            putchar('*');
            while (c[i] == c[i + 1]) i++;
        }
        else putchar(c[i]);
    }
    //printf("\n:%s", c);
    return;
}

void destructor()
{
    free(str);
    free(subStr);
    return;
}

void enterString()
{
    int i;
    for (i = 0; i < length; i++)
    {
        *str = _getch();
        printf("%c", *str);
        if (*str++ == 13) 
        {
            //str -= i;
            break;
        }
    }
    str -= i;
    length = i - 1;
    return;
}