#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double f(double* x);
double p1(double* x);
double p2(double* x);
double p3(double* x);
double fun(double* x, double a, double* p);
double wind(double* x, double a, double* p);
double interpol(double* x, double a, double* p);
void fastspusk(double* x0);

																											// Ishodnaya funkcia
double f(double* x) 
{
	return ( (pow(x[0], 2)) + 8 * x[0] + 5 * (pow(x[1], 2)) + 7 * (pow(x[2], 2)) + 119 * x[2] + 531.75 );
}

																											// Proizvodnaya po x3
double p1(double* x) 
{
	return (2 * x[0] + 8);
}


																											// Proizvodnaya po x2
double p2(double* x) 
{
	return (10 * x[1]);
}

																											// Proizvodnaya po x3
double p3(double* x) 
{
	return (14 * x[2] + 119);
}


double fun(double* x, double a, double* p) 
{
	double xn[] = { x[0] + a * p[0], x[1] + a * p[1], x[2] + a * p[2] };

	return f(xn);
}


																											// Skolzyashee okno
double wind(double* x, double a, double* p) 
{
	double d = 0.025;

	while (!((fun(x, a - d, p) >= fun(x, a, p)) && (fun(x, a, p) <= fun(x, a + d, p))))
	{
		if ((fun(x, a - d, p) >= fun(x, a, p)) && (fun(x, a, p) >= fun(x, a + d, p)))
			a += d / 2;
		else if (a > -d / 2)
			a -= d / 2;
	}

	return a;
}


double interpol(double* x, double a, double* p)																// Kvadratnaya interpolyaciya
{
	double d = 0.025;

	a = wind(x, a, p);
	
	double a1 = a;
	
	double a2, a3, amin, ast;
	
	do {
		a2 = a1 + d;
		if (fun(x, a1, p) > fun(x, a2, p))
			a3 = a1 + 2 * d;
		else
			a3 = a1 - d;
		ast = 0.5 * ((a2 * a2 - a3 * a3) * fun(x, a1, p) + (a3 * a3 - a1 * a1) * fun(x, a2, p) + (a1 * a1 - a2 * a2) * fun(x, a3, p));
		ast = ast / ((a2 - a3) * fun(x, a1, p) + (a3 - a1) * fun(x, a2, p) + (a1 - a2) * fun(x, a3, p));
		if ((fun(x, a1, p) <= fun(x, a2, p)) && (fun(x, a2, p) <= fun(x, a3, p)))
			amin = a1;
		else if ((fun(x, a2, p) <= fun(x, a1, p)) && (fun(x, a1, p) <= fun(x, a3, p)))
			amin = a2;
		else
			amin = a3;
		if ((a1 <= ast) && (ast <= a3))
		{
			if (fun(x, amin, p) < fun(x, ast, p))
				a1 = amin;
			else
				a1 = ast;
		}
		else
			a1 = ast;
	} while ((abs(amin - ast)) >= 1e-5);
	
	return ast;
}

																											// Metod naiskoreyshego spuska
void fastspusk(double* x0) 
{	
	ofstream t("traektoria.txt", ios_base::out);
	
	double x[] = { x0[0], x0[1], x0[2] };
	
	t << x[0] << "," << x[1] << "," << x[2] << endl;
	
	double p[] = { -p1(x), -p2(x), -p3(x) };
	
	double a = 0;
	
	a = interpol(x0, a, p);
	
	double x_n[] = { x[0] + a * p[0], x[1] + a * p[1], x[2] + a * p[2] };
	
	t << x_n[0] << "," << x_n[1] << "," << x_n[2] << endl;

	while (abs(f(x_n) - f(x)) > 1e-4 && sqrt(pow(x[0] - x_n[0], 2) + pow(x[1] - x_n[1], 2) + pow(x[2] - x_n[2], 2)) > 1e-4) {
		x[0] = x_n[0];
		x[1] = x_n[1];
		x[2] = x_n[2];
		p[0] = -p1(x);
		p[1] = -p2(x);
		p[2] = -p3(x);
		a = interpol(x, a, p);
		x_n[0] = x[0] + a * p[0];
		x_n[1] = x[1] + a * p[1];
		x_n[2] = x[2] + a * p[2];
	}

		t << x_n[0] << "," << x_n[1] << "," << x_n[2] << endl;
	

	t.close();
	
	cout << "X min: (" << x_n[0] << ", " << x_n[1] << "," << x_n[2] << ")" << endl;
	cout << "f min = " << f(x_n) << endl;
}


int main()
{
	double x0[] = { 8, -2, 6 };

	fastspusk(x0);
	
	return 0;
}


