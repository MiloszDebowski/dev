#include"user_funs.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#define PI 3.14

matrix ff0T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = pow(x(0) - ud1(0), 2) + pow(x(1) - ud1(1), 2);
	return y;
}

matrix ff0R(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	matrix Y0 = matrix(2, 1), MT = matrix(2, new double[2] { m2d(x), 0.5 });
	matrix* Y = solve_ode(df0, 0, 0.1, 10, Y0, ud1, MT);
	int n = get_len(Y[0]);
	double teta_max = Y[1](0, 0);
	for (int i = 1; i < n; ++i)
		if (teta_max < Y[1](i, 0))
			teta_max = Y[1](i, 0);
	y = abs(teta_max - m2d(ud1));
	Y[0].~matrix();
	Y[1].~matrix();
	return y;
}

matrix df0(double t, matrix Y, matrix ud1, matrix ud2)
{
	matrix dY(2, 1);
	double m = 1, l = 0.5, b = 0.5, g = 9.81;
	double I = m * pow(l, 2);
	dY(0) = Y(1);
	dY(1) = ((t <= ud2(1)) * ud2(0) - m * g * l * sin(Y(0)) - b * Y(1)) / I;
	return dY;
}

matrix ff1T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = -cos(0.1 * m2d(x)) * pow(exp(1), -pow(0.1 * m2d(x) - 2 * M_PI, 2)) + 0.002 * pow(0.1 * m2d(x), 2);
	return y;
}

matrix df1(double t, matrix Y, matrix ud1, matrix ud2)
{
	// dane
	double a = 0.98; // wsp odpowiadajacy za lepkosc cieczy
	double b = 0.63; // wsp odpowiadajacy za zwezenie strumienia cieczy
	double g = 9.81; // przysp ziemskie
	double Pa = 0.5;
	double Pb = 1.0;
	double FbIn = 0.01;
	double Da = m2d(ud2);
	double Db = 0.00365665;
	double Va = Y(0);
	double Vb = Y(1);
	double Ta0 = 90.0;
	double Tb0 = Y(2);
	double TbIn = 20.0;

	matrix dY(3, 1);

	double FaOut, FbOut;

	if (Y(0) > 0)
	{
		FaOut = a * b * Da * sqrt(2.0 * g * Va / Pa);
	}
	else
	{
		FaOut = 0;
	}


	if (Y(1) > 0)
	{
		FbOut = a * b * Db * sqrt(2.0 * g * Vb / Pb);
	}
	else
	{
		FbOut = 0;
	}

	dY(0) = -1.0 * FaOut;
	dY(1) = FaOut + FbIn - FbOut;
	dY(2) = FbIn / Vb * (TbIn - Tb0) + FaOut / Vb * (Ta0 - Tb0);
	return dY;
}

//matrix ff1R(matrix X, matrix ud1, matrix ud2) 
// {
//	matrix Yi;
//	matrix Y0 = matrix(3, new double[3] {5.0, 1.0, 20.0});
//	// 5 - Va, 1 - Vb, 20 - Tb0
//
//	matrix* Y = solve_ode(df1, 0, 1, 2000, Y0, ud1, X);
//
//	int n = get_len(Y[0]);
//	double max = Y[1](0, 2);
//	for (int i = 0; i < n; i++)
//	{
//		if (max < Y[1](i, 2)) {
//			max = Y[1](i, 2);
//		}
//	}
//	return abs(max - 50);
//	//return max;
//}

matrix ff1R(matrix X, matrix ud1, matrix ud2)
{
	matrix Yi;
	matrix Y0 = matrix(3, new double[3] {5.0, 1.0, 20.0});
	// 5 - Va, 1 - Vb, 20 - Tb0

	matrix* lag = solve_ode(df1, 0, 1, 2000, Y0, ud1, 0.00116775);
	matrix* fib = solve_ode(df1, 0, 1, 2000, Y0, ud1, 0.00116724);

	std::ofstream Sout_fibonacci("results_fibonacci4.csv");
	Sout_fibonacci << "t; FVA; LVA; FVB; LVB; FTB; LTB" << std::endl;
	int n = get_len(lag[0]);
	double max = lag[1](0, 2);
	for (int i = 0; i < n; i++)
	{
		Sout_fibonacci << i << "; " << fib[1](i, 0) << "; " << lag[1](i, 0) << "; " << fib[1](i, 1) << "; " << lag[1](i, 1) << "; " << fib[1](i, 2) << "; " << lag[1](i, 2) << "\n";
	}
	Sout_fibonacci.close();
	return abs(max - 50);
	//return max;
}

matrix ff2T(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = pow(m2d(x(0)), 2) + pow(m2d(x(1)), 2) - cos(2.5 * M_PI * m2d(x(0))) - cos(2.5 * M_PI * m2d(x(1))) + 2;
	return y;
}

matrix ff2TTest(matrix x, matrix ud1, matrix ud2)
{
	matrix y;
	y = 2.5 * pow(pow(x(0), 2) - x(1), 2) + pow(1 - x(0), 2);
	return y;
}

matrix ff_lab3(matrix x, matrix ud1, matrix ud2)
{
	matrix y0(4, 1);
	y0(0) = 0;
	y0(1) = x(0);
	y0(2) = 100;
	y0(3) = 0;

	matrix* y = solve_ode(df3, 0, 0.01, 7, y0, ud1, x(1));
	int i0 = 0;
	int i50 = 0;
	int n = get_len(y[0]);
	for (int i = 0; i < n; i++)
	{
		if (abs(y[1](i, 2)) < abs(y[1](i0, 2)))
		{
			i0 = i;
		}
		if (abs(y[1](i, 2) - 50) < abs(y[1](i50, 2) - 50))
		{
			i50 = i;
		}
	}
	matrix res = y[1](i0, 0);


	if (abs(x(0)) - 10 > 0)
		res = res - ud2 * pow(abs(x(0)) - 10, 2);
	if (abs(x(1)) - 23 > 0)
		res = res - ud2 * pow(abs(x(1)) - 23, 2);
	if (abs(y[1](i50, 0) - 5) - 1 > 0)
		res = res - ud2 * pow(abs(y[1](i50, 0) - 5) - 1, 2);
	delete[] y;

	return res * (-1);
}

matrix df3(long double t, matrix y, matrix ud1, matrix ud2)
{
	matrix dy(4, 1);

	long double C = 0.47;
	long double ro = 1.2;
	long double r = 0.12;
	long double S = PI * r * r;

	long double Fmx = ro * y(3) * ud2(0) * r * r * r * PI;
	long double Dx = 0.5 * C * ro * S * y(1) * y(1);
	long double Fmy = ro * y(1) * ud2(0) * r * r * r * PI;
	long double Dy = 0.5 * C * ro * S * y(3) * y(3);
	long double m = 0.6;
	long double g = 9.81;

	dy(0) = y(1);
	dy(1) = (-1) * (Fmx + Dx) / m;
	dy(2) = y(3);
	dy(3) = (-1) * (Fmx + Dx + m * g) / m;

}

matrix testowa_lab_3_wew(matrix x, matrix ud1, matrix ud2)
{
	matrix y = sin(PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2))) / (PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2)));

	if (-x(0) + 1 > 0)
	{
		y = y + 10e4;
	}
	else
	{
		y = y + ud2(0, 0) / (1 - x(0));
	}

	if (-x(1) + 1 > 0)
	{
		y = y + 10e4;
	}
	else
	{
		y = y + ud2(0, 0) / (1 - x(1));
	}

	if (norm(x) - ud1 > 0)
	{
		y = y + 10e4;
	}
	else
	{
		y = y + ud2(0, 0) / (norm(x) - ud1);
	}

	return y;
}

matrix testowa_lab_3_zew(matrix x, matrix ud1, matrix ud2)
{
	matrix y = sin(PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2))) / (PI * sqrt(pow(x(0) / PI, 2) + pow(x(1) / PI, 2)));

	if (-x(0) + 1 > 0)
	{
		y = y + ud2 * pow(-x(0) + 1, 2);
	}

	if (-x(1) + 1 > 0)
	{
		y = y + ud2 * pow(-x(1) + 1, 2);
	}

	if (norm(x) - ud1 > 0)
	{
		y = y + ud2 * pow(norm(x), 2);
	}

	return y;
}