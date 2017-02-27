/* Написать программу для численного расчета интеграла методом правых прямоугольников.
(a и b задать в программе, подинтегральную функцию (exp^(-x^2)) вынести в отдельную функцию). */

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
using namespace std;

const int NUM_threads = 4; // количество потоков
const int a = 0; // нижний предел интеграла
const int b = 4; // верхний предел интеграла
const int c = 100000; // количество отрезков
double x;
int i;

// функция, возвращающая exp^(-x^2)
double f (double x)
{
	return exp(-1 * x * x);
};

void main ()
{
	long double clockStart, clockStop;
	double s = 0;
	double d = abs(b - a) / (double) c; //  длина отрезка

	clockStart = omp_get_wtime();

	#pragma omp parallel for shared(s, a, d, i) private(x) num_threads(NUM_threads)
	for (i = 1; i < c; i++)
	{
		x = a + i * d;
		#pragma omp atomic 
			s += (d * f(x)); // площадь
	}

	clockStop = omp_get_wtime();

	cout << "Square s = " << s << endl;
	cout << "Seconds: " << (clockStop - clockStart) << endl;
	getchar();
}



