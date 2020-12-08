#pragma once
void swap(double& x1, double& x2)
{
	double buf = x1;
	x1 = x2;
	x2 = buf;
}
//---------------------------
class MinFNPpoNapr
{
public:
	
	double (*f)(double* x, int n);//я не понимаю эту запись
	int n;
	double* d;//
	double* x0;//начальная точка, в которой ищем градиент
	MinFNPpoNapr(double (*f)(double* x, int n), int n)//конструктор. создается экземпляр класса и хаписывает в поля 1) указатель на функцию f от (указателя на х и число n), 2) число n
	{
		this->f = f;//указатель на функцию, которую мы минимизируем - записываем в поле класса
		this->n = n;//число переменных из функции передаем в переменную класса
		d = new double[n];//вектор направления - массив из n чисел double
		x0 = new double[n];//точка начальная - массив из n чисел double
	}
	double fi(double t)
	{
		double* x = new double[n];
		double res;
		for (int i = 0; i < n; i++)
		{
			x[i] = x0[i] + t * d[i];
		}
		res = f(x, n);
		return res;
	}
	double* findMinFNPpoNapr()
	{
		double* res = new double[n];
		
		double t = min_function(0);
		for (int i = 0; i < n; i++)
			res[i] = x0[i] + t * d[i];
		return res;
	}
	double min_function(double x0)
	{
		// 
		double h = 0.0001;
		double gold = (sqrt(5) - 1) / 2;
		//выбираем направление движения
		double y0 = fi(x0), y1 = fi(x0 + h);
		if (y0 > y1)
			h = h;
		else
			h = -h;
		//
		double x1 = x0 + h, x2, x3;
		while (1)
		{

			x2 = x1 + (x1 - x0) / gold;
			//если h>0, то тройка (x0, x1, x2) 
			//если h<0, то тройка (x2, x1, x0)
			if (fi(x1) < fi(x0) && fi(x1) < fi(x2))  // (x0, x1, x2) удачная тройка
			{
				// проверяем критерий останова
				if (fabs(x2 - x0) < 1e-3)
					break;
				
				while (1)
				{
					// проверяем критерий останова
					if (fabs(x2 - x0) < 1e-3)
						break;
					if (x2 < x0)
						swap(x2, x0);
					// (x0, x1, x2) удачная тройка
					x3 = x2 - (x1 - x0);
					if (x3 < x1)
						swap(x1, x3);
					//x0<x1<x3<x2
					//имеем 2 тройки  (x0, x1, x3), (x1, x3, x2)
					// выбираем из них удачную
					if (fi(x1) < fi(x0) && fi(x1) < fi(x3))  //удачная тройка (x0, x1, x3)
					{
						x2 = x3;
					}
					if (fi(x3) < fi(x1) && fi(x3) < fi(x2))  //удачная тройка (x1, x3, x2)
					{
						x0 = x1;
						x1 = x3;
					}

				}
				return (x0 + x2) / 2;
			}
			else
			{
				x0 = x1;
				x1 = x2;
			}
		}
		return 0;
	}
	double* grad(double x0[])
	{
		double* gr = new double[n];
		double h = 1e-8;
		double fx0 = f(x0, n);
		for (int i = 0; i < n; i++)
		{
			x0[i] += h;
			double fxh = f(x0, n);
			x0[i] -= h;
			
			gr[i] = (fxh - fx0) / h;
		}
		return gr;
	}
};