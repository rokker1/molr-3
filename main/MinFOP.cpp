#include <math.h>
#include <stdio.h>

void swap(double&, double&);

double f(double x);
double min_function(double (*fi)(double), double x0)
{
	// 
	double h = 0.0001;
	double gold = (sqrt(5) - 1) / 2;
	//�������� ����������� ��������
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
		//���� h>0, �� ������ (x0, x1, x2) 
		//���� h<0, �� ������ (x2, x1, x0)
		if (fi(x1) < fi(x0) && fi(x1) < fi(x2))  // (x0, x1, x2) ������� ������
		{
			// ��������� �������� ��������
			if (fabs(x2 - x0) < 1e-3)
				break;

			while (1)
			{
				// ��������� �������� ��������
				if (fabs(x2 - x0) < 1e-3)
					break;
				if (x2 < x0)
					swap(x2, x0);
				// (x0, x1, x2) ������� ������
				x3 = x2 - (x1 - x0);
				if (x3 < x1)
					swap(x1, x3);
				//x0<x1<x3<x2
				//����� 2 ������  (x0, x1, x3), (x1, x3, x2)
				// �������� �� ��� �������
				if (fi(x1) < fi(x0) && fi(x1) < fi(x3))  //������� ������ (x0, x1, x3)
				{
					x2 = x3;
				}
				if (fi(x3) < fi(x1) && fi(x3) < fi(x2))  //������� ������ (x1, x3, x2)
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

//��������� �������� ������	 ����������� ������� fi � ����� x
double df1(double (*fi)(double), double x) 
{
	
	double h = 1e-4;//��� �����������������
	return (fi(x + h) - fi(x - h)) / (2 * h);
}

//��������� �������� ������ ����������� ������� fi � ����� x
double df2(double (*fi)(double), double x)
{
	double h = 1e-4;//��� �����������������
	return (fi(x + h) - 2* fi(x)+fi(x - h)) / (2 * h*h);
}

//����������� ������� �������
double min_function4(double (*fi)(double), double x_0) 
{
	double x_1 = x_0;//�������� ��������� ����� - ��������, ���������� � �������
	double x_2 = x_1;
	double m = 0;//�����
	int i = 0;//��������
	double d1 = fabs(df1(fi, x_1));//�������� �������� - ����������� � ����� �1
	while (d1 > 1e-4) {
		x_1 = x_2;
		x_2 = x_1 - 0.5* (df1(fi, x_1) / df2(fi, x_1));//��������� �����
		m = (x_1 + x_2) / 2;//�������
		printf("Iteration %d\n",i);
		printf("df1, df2 for x1 is: %f, %f\n", df1(fi, x_1), df2(fi, x_1));
		printf("ratio df1/f for x1 is: %f\n", df1(fi, x_1)/fi(x_1));
		printf("x_1=%f, x_2=%f\n",x_1, x_2);
		printf("mean is %f\n\n", m);
		printf("next iteration \n\n");
		i += 1;
		d1 = fabs(df1(fi, x_1));//����������� ����������� � ����� ����� �1
	}
	return m;
}

double min_function3(double (*fi)(double), double a, double b) //����������� ���������� ������� ������� �����������
{
	double m = 0;//�����
	int i = 0;//��������
	double df1a = df1(fi, a);//����������� � ����� a
	double df1b = df1(fi, b);//����������� � ����� b
	double df1c = 0;//  c
	double f1a = fi(a);//�������� ������� � ����� a
	double f1b= fi(b);//�������� ������� � ����� b
	double f1c = 0;//�������� ������� � ����� b
	double c = 0;
	if (df1a >= 0 or df1b <= 0) //���� � �������� ������ ��������� ����������� ����� ����� �����, �� �� ������� 8.5 ��������� �� ������ ���������
	{
		if (f1a > f1b)
			return b;
		else
			return a;
	}
	while (i < 100) {
		c = ((df1a * a - f1a) - (df1b * b - f1b)) / (df1a - df1b);//����� ����� ����������� �����������
		printf("Crossing point - c = %f\n", c);
		df1c = df1(fi, c);//����������� ������� � ����� �
		if(fabs(df1c)<=1e-3)//���� ����������� � ����� � ����� ���� - ��� �����
			return c;
		else
			if (df1c > 0)
			{
				b = c;//a - �����������; b ��������� � �
				df1b = df1(fi, b);//��������
				f1b = fi(b);//��������
			}
			else
			{
				a = c;//b - �����������; � ��������� � �
				df1a = df1(fi, a);//��������
				f1a = fi(a);//��������
			}
		printf("new a, b is= %f, %f\n", a, b);
		i++;
	}
	return c;
}

double dichotomy_min_function(double(*fi)(double), double x0, double x1)
{
	double s = 1e-5;
	
	while (true)
	{
		if (fabs(x1 - x0) < 1e-4)
		{
			
			printf("answer is: %f", (x0 + x1) / 2);
			printf("\n");
			break;
		}
		double cminus = (x0 + x1) / 2.0 - s / 2.0;
		double cplus = (x0 + x1) / 2.0 + s / 2.0;
		double fx0 = fi(x0);
		double fx1 = fi(x1);
		double fxcplus = fi(cplus);
		double fxcminus = fi(cminus);
		if (fxcminus<= fxcplus)
		{
			x1 = cplus;
		}
		else
			if (fxcminus > fxcplus)
			{
				x0 = cminus;
			}
			else
			{
				printf("net udach tochek (((( ");
				break;
			}
		
	}

	
	return (x0 + x1) / 2.0;
}