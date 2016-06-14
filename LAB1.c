/* Кудрявцев И.В. Поток 09.2015. Вариант №5.
Вариант задания реализовать в виде функции, использующей для работы со строкой
только указатели и операции вида *p++, p++ и т.д. Если функция возвращает строку или ее
фрагмент, то это также необходимо сделать через указатель.
Вариант №9.
Функция находит в строке пары инвертированных фрагментов (например, "123apr" и "rpa321")
и возвращает указатель на первый. С помощью функции найти все пары.*/

#include <stdio.h>
#include <locale.h>
#include <conio.h>

#define SIZE 4

void fill();
int find();

int  p;                                                                     // переменная - точка отсчёта
char *str = "1jan2feb3mar4ram3naj1bef21";									// исходная строка
char subStr[SIZE+1] = {0};													// массив-подстрока
int lenght = SIZE;															// длина подстроки для поиска совпадений

int main()
{
	setlocale(LC_ALL, "russian");
	int result;
	printf("Ваша строка: %s", str);
	printf("\n\n");
	printf("Поиск фрагментов: \n");
	for (p = 0; *(str+p)!='\0'; p++)				                        // проходим по всей строке
	{
		fill();
		result = find();
		if (result!=0)
		{
			printf("Указатель: %p\t", str+p);
			printf("Индекс повтора = %d \t", result);
			printf("Фрагмент: %s\n", subStr);
		}
	}
	printf("\nПовторов больше нет\n");
	_getch();
	return 0;
}

void fill()				                                                    // заполнение дополнительного массива
{
	int i, j;
	for (i = p, j = lenght-1; j>=0; i++, j--)
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