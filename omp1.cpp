/* �������� ��������� ��� ���������� ������� ��������� ������� ������ ���������������.
(a � b ������ � ���������, ��������������� ������� (exp^(-x^2)) ������� � ��������� �������). */

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
using namespace std;

const int NUM_threads = 4;
const int a = 1; // ������ ������ ���������
const int b = 4; // ������� ������ ���������
const int c = 3; // ���������� ��������
int x;

// �������, ������������ exp^(-x^2)
double f (double x)
{
	return exp(-1 * x * x);
};

void main ()
{
	long double clockStart, clockStop;
	double s;
	double d = abs(b-a)/c; //  ����� �������

	clockStart = omp_get_wtime();

	#pragma omp parallel for shared (s, x, d, b) num_threads (NUM_threads)
	for (x = 1; x < b; x += d)
	{
		#pragma omp atomic 
			s += (d * f(x)); // �������
	}

	clockStop = omp_get_wtime();

	cout.precision(3);
	cout<<"Square s = "<<s<<endl;
	cout<<"Seconds: "<<(clockStop - clockStart)<<endl;
}



