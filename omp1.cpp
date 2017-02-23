/* Написать программу для численного расчета интеграла методом правых прямоугольников.
(a и b задать в программе, подинтегральную функцию (exp^(-x^2)) вынести в отдельную функцию). */

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
using namespace std;

const int NUM_threads = 4;
const int a = 1; // нижний предел интеграла
const int b = 4; // верхний предел интеграла
const int c = 3; // количество отрезков
int x;

// функция, возвращающая exp^(-x^2)
double f (double x)
{
	return exp(-1 * x * x);
};

void main ()
{
	long double clockStart, clockStop;
	double s;
	double d = abs(b-a)/c; //  длина отрезка

	clockStart = omp_get_wtime();

	#pragma omp parallel for shared (s, x, d, b) num_threads (NUM_threads)
	for (x = 1; x < b; x += d)
	{
		#pragma omp atomic 
			s += (d * f(x)); // площадь
	}

	clockStop = omp_get_wtime();

	cout.precision(3);
	cout<<"Square s = "<<s<<endl;
	cout<<"Seconds: "<<(clockStop - clockStart)<<endl;
}



