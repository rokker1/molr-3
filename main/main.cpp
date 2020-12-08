#include <iostream>
#include <conio.h>
#include <math.h>

#include "MinFNPpoNapr.h"
#include <string>



void testGrad(); //прототип
void run_minFunction3();
std::string start_p;
std::string stop_p;
double min_function(double (*pf)(double), double x0);//прототип
double min_function3(double (*pf)(double), double a, double b);//прототип
double min_function4(double (*pf)(double), double x0);//прототип
double dichotomy_min_function(double(*fi)(double), double x0, double x1);//прототип

//функция одной переменной
double f(double x)
{
    return x * x - 4 * x + 1;  // точный экстремум = 2
}

const double v = 5.0;//ВАРИАНТ
//функция одной переменной из лабы
double f1(double x)
{
	return pow(x, 6) - v * pow(x, 5) + v * pow(x, 3) - 10 * pow(x, 2) + x;
}

//просто еще одна функция
double simpleparabola(double x)
{
	return x*x;
}



//функция двух переменных
double F2(double* x, int n)
{
    //х - указатель на аргемент функции
	//n - число переменных
	return x[0] * x[0] + x[1] * x[1];
}

//функция трех переменных
double F3(double* x, int n)
{
	//х - указатель на аргемент функции
	//n - число переменных
	double x1 = x[0];
	double x2 = x[1];
	double x3 = x[2];
	return x1*x1+v*x2*x2+x3*x3+3*x1*x2-v*x1*x3-x2*x3+x1-v*x2+x3;
}

//одномерная оптимизация
void testMinFOP()
{
	//тестирование метода одномерной оптимизации
	double xmin, ans = 2.;
	xmin = min_function(f, 5); // одномерная функция pf, начальная точка x0 = 5
	if (fabs(xmin - ans) > 0.01)
		printf("\nErrrorr1: Naydena Tochka minimuma = %lf, answer = %lf", xmin, ans);
}

void test()
{

	MinFNPpoNapr minFNPpoNapr(F3, 3);
	minFNPpoNapr.x0[0] = 2;
	minFNPpoNapr.x0[1] = 1;
	minFNPpoNapr.x0[2] = v;
	minFNPpoNapr.d[0] = -1;
	minFNPpoNapr.d[1] = 2;
	minFNPpoNapr.d[2] = 1;
	double answ[3] = { 1,0,0 };//ошибка! найти аналтически
	double* xopt = minFNPpoNapr.findMinFNPpoNapr();
	double S = 0;
	for (int i = 0; i < 3; i++)
		S += (xopt[i] - answ[i]) * (xopt[i] - answ[i]);
	if (fabs(sqrt(S)) > 0.01)
		printf("\nErrrorr2: Naydena Tochka minimuma = (%f, %f, %f), answer = (%f, %f, %f)", xopt[0], xopt[1], xopt[2], answ[0], answ[1], answ[2]);

}



//Тестирование градиента
double f3(double x[], int n)
{
	return 2 * x[0] + 4 * x[1];
}

void testGrad()
{
	MinFNPpoNapr myFunc(f3, 2);
	double gr_ans[] = { 2, 4 }, x0[] = { 1, 1 };
	double* res;
	res = myFunc.grad(x0);
	for (int i = 0; i < 2; i++)
		if (fabs(gr_ans[i] - res[i]) > 1e-3)
			printf("Errrrror1: Gradient");


	delete[] res;
}

void run_minFunction3() //работа с минимизацией методом касательных
{
	while (1)
	{
		std::cout << "Enter new points\n";
		std::cin >> start_p;
		std::cin >> stop_p;
		double dstart_p = std::stod(start_p);
		double dstop_p = std::stod(stop_p);
		double result = min_function3(f1, dstart_p,dstop_p);
		printf( "Result is given: %f\n\n", result);
		
	}
}
void run_minFunction4() //работа с минимизацией методом Ньютона
{
	while (1)
	{
		std::cout << "Enter new start point\n";
		std::cin >> start_p;
		double dstart_p = std::stod(start_p);
		double result = min_function4(f1, dstart_p);
		printf("Result is given: %f\n\n", result);

	}
}
void run_dichotomy_minFunction() //работа с минимизацией методом Ньютона
{
	while (1)
	{
		std::cout << "Enter new points\n";
		std::cin >> start_p;
		std::cin >> stop_p;
		double dstart_p = std::stod(start_p);
		double dstop_p = std::stod(stop_p);
		dichotomy_min_function(f1,dstart_p, dstop_p);
		

	}
}


int main()
{
	run_dichotomy_minFunction();
	
	//run_minFunction4();
	//testMinFOP();
    //test();
    //testGrad();
	//run_minFunction3();
	//min_function3(f1, -7, 15.0);
	
    //std::cout << "\nhello";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
