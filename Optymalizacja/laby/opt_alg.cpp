#include"opt_alg.h"
#include <cmath>
#include<vector>
#include "matrix.h"

solution MC(matrix(*ff)(matrix, matrix, matrix), int N, matrix lb, matrix ub, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		while (true)
		{
			Xopt = rand_mat(N);
			for (int i = 0; i < N; ++i)
				Xopt.x(i) = (ub(i) - lb(i)) * Xopt.x(i) + lb(i);
			Xopt.fit_fun(ff, ud1, ud2);
			if (Xopt.y < epsilon)
			{
				Xopt.flag = 1;
				break;
			}
			if (solution::f_calls > Nmax)
			{
				Xopt.flag = 0;
				break;
			}
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution MC(...):\n" + ex_info);
	}
}

solution expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution interval;
		interval.x = matrix(2, 1);
		int i = 0;
		solution X0 = x0;
		solution X1 = X0.x + d;

		if (X1.fit_fun(ff) == X0.fit_fun(ff))
		{
			interval.x(0, 0) = X0.x(0);
			interval.x(1, 0) = X1.x(0);
			return interval;
		}

		if (X1.fit_fun(ff) > X0.fit_fun(ff))
		{
			d = -d;
			X1 = X0.x + d;
			if (X1.fit_fun(ff) >= X0.fit_fun(ff))
			{
				interval.x(0, 0) = X1.x(0);
				interval.x(1, 0) = X0.x(0) - d;
				return interval;
			}
		}

		solution xPre;

		while (true)
		{
			if (i >= Nmax) throw "Maximum number of function calls exceeded";

			i++;
			xPre = X0;
			X0 = X1;
			X1.x(0) = X0.x(0) + pow(alpha, i) * d;

			if (X0.fit_fun(ff) <= X1.fit_fun(ff))
				break;
		}

		if (d > 0)
		{
			interval.x(0, 0) = xPre.x(0);
			interval.x(1, 0) = X1.x(0);
		}
		else
		{
			interval.x(0, 0) = X1.x(0);
			interval.x(1, 0) = xPre.x(0);
		}

		return interval;
	}
	catch (string ex_info)
	{
		throw ("solution expansion(...):\n" + ex_info);
	}
}

double generateFibonacci(int n) {
	return (pow(1. + sqrt(5.), n) - pow(1. - sqrt(5.), n)) / (pow(2., n) * sqrt(5.));;
}

solution fib(matrix(ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		int k = 0;

		while (generateFibonacci(k) <= (b - a) / epsilon)
		{
			k++;
		}

		solution A0 = a;
		solution B0 = b;
		solution C0, D0;
		C0.x(0) = B0.x(0) - (generateFibonacci(k - 1) / generateFibonacci(k)) * (B0.x(0) - A0.x(0));
		D0.x(0) = A0.x(0) + B0.x(0) - C0.x(0);

		for (int i = 0; i < k - 3; i++)
		{
			if (C0.fit_fun(ff) < D0.fit_fun(ff))
			{
				B0.x(0) = D0.x(0);
			}
			else
			{
				A0.x(0) = C0.x(0);
			}

			C0.x(0) = B0.x(0) - (generateFibonacci(k - i - 2) / generateFibonacci(k - i - 1)) * (B0.x(0) - A0.x(0));
			D0.x(0) = A0.x(0) + B0.x(0) - C0.x(0);
		}

		Xopt.x = C0.x(0);
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}
}


solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		solution A0 = a;
		solution B0 = b;
		solution C0 = 0.5 * (A0.x + B0.x);
		solution D0;
		solution D1, A1, B1, C1;
		solution l, m;
		int i = 0;

		while (true)
		{
			if (i > Nmax)
				throw "Maximum number of function calls exceeded";

			l = A0.fit_fun(ff) * (pow(B0.x, 2) - pow(C0.x, 2)) +
				B0.fit_fun(ff) * (pow(C0.x, 2) - pow(A0.x, 2)) +
				C0.fit_fun(ff) * (pow(A0.x, 2) - pow(B0.x, 2));
			m = A0.fit_fun(ff) * (B0.x - C0.x) +
				B0.fit_fun(ff) * (C0.x - A0.x) +
				C0.fit_fun(ff) * (A0.x - B0.x);

			if (m.x <= 0)
			{
				Xopt.x(0) = 666;
				Xopt.y = 666;
				return Xopt;
			}

			D0 = 0.5 * l.x / m.x;

			if (A0.x < D0.x && D0.x < C0.x)
			{
				if ((D0.fit_fun(ff) - 50) < (C0.fit_fun(ff) - 50))
				{
					A1 = A0;
					B1 = C0;
					C1 = D0;
				}
				else
				{
					A1 = D0;
					C1 = C0;
					B1 = B0;
				}
			}
			else if (C0.x < D0.x && D0.x < B0.x)
			{
				if (D0.fit_fun(ff) < C0.fit_fun(ff))
				{
					A1 = C0;
					C1 = D0;
					B1 = B0;
				}
				else
				{
					A1 = A0;
					C1 = C0;
					B1 = D0;
				}
			}
			else
			{
				Xopt.x(0) = 666;
				Xopt.y(0) = 666;
				return Xopt;
			}

			if ((B0.x - A0.x < epsilon) || (fabs(D0.x(0) - D1.x(0)) < gamma))
				break;
			D1.x(0) = D0.x(0);
			A0 = A1;
			B0 = B1;
			C0 = C1;
			D1 = D0;
			i++;
		}

		Xopt = D0;
		Xopt.flag = 0;
		return Xopt;
	}

	catch (string ex_info)
	{
		throw ("solution lag(...):\n" + ex_info);
	}
}


solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		solution x = x0;
		solution xb;

		do
		{
			xb = x;
			x = HJ_trial(ff, xb, s);
			if (x.fit_fun(ff) < xb.fit_fun(ff))
			{
				while (x.fit_fun(ff) < xb.fit_fun(ff))
				{
					solution tempxb = xb;
					xb = x;
					x = 2 * xb.x - tempxb.x;
					x = HJ_trial(ff, x, s);
					if (solution::f_calls > Nmax)
						throw "Maximum number of function calls exceeded";
				}
				x = xb;
			}
			else
			{
				s = alpha * s;
			}

			if (solution::f_calls > Nmax)
				throw "Maximum number of function calls exceeded";
		} while (s >= epsilon);

		Xopt = xb;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try
	{
		int n = get_len(XB.x);
		matrix ej = ident_mat(n);

		for (int j = 0; j < n; j++)
		{
			solution xbPlus = XB.x + s * ej[j];
			solution xbMinus = XB.x - s * ej[j];
			if (xbPlus.fit_fun(ff) < XB.fit_fun(ff))
			{
				XB = xbPlus;
			}
			else if (xbMinus.fit_fun(ff) < XB.fit_fun(ff))
			{
				XB = xbMinus;
			}
		}

		return XB;
	}
	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}

double max_abs(const matrix& vec) {
	int n = get_len(vec);
	double max_val = fabs(vec(0, 0));
	for (int i = 1; i < n; i++) {
		max_val = std::max(max_val, fabs(vec(i, 0)));
	}
	return max_val;
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		solution xB = x0;
		matrix s = s0;
		int n = get_len(x0);
		matrix dj = ident_mat(n);
		matrix lambda(n, 1);
		matrix p(n, 1);

		do {
			for (int j = 0; j < n; j++)
			{
				matrix step = s(j) * get_col(dj, j);
				solution xBNew = xB.x + step;

				if (xBNew.fit_fun(ff) < xB.fit_fun(ff))
				{
					xB = xBNew;
					lambda(j) = lambda(j) + s(j);
					s(j) = alpha * s(j);
				}
				else
				{
					s(j) = -beta * s(j);
					p(j) = p(j) + 1;
				}
			}

			if (solution::f_calls > Nmax)
				throw "Maximum number of function calls exceeded";

			bool changeDirection = true;
			for (int j = 0; j < n; j++)
			{
				if (lambda(j) == 0 || p(j) == 0)
				{
					changeDirection = false;
					break;
				}
			}

			if (changeDirection)
			{
				matrix Q(n, n);
				matrix vj(n, 1);
				for (int i = 0; i < n; ++i)
				{
					for (int j = 0; j <= i; ++j)
					{
						Q(i, j) = lambda(i);
					}
				}

				Q = dj * Q;
				vj = Q[0] / norm(Q[0]);
				dj.set_col(vj, 0);

				for (int j = 0; j < n; j++)
				{
					matrix sum(n, 1);
					for (int k = 0; k < j; k++)
					{
						sum = sum + (trans(Q[j]) * dj[k]) * dj[k];
					}
					vj = Q[j] - sum;
					dj.set_col(vj, j);
				}
				lambda = matrix(n, 1);
				p = matrix(n, 1);
				s = s0;
			}

		} while (max_abs(s) >= epsilon);

		Xopt = xB;
		Xopt.flag = 0;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

/*solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	
}
*/
solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix lb, matrix ub, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}


// Znajdü indeks wierzcho≥ka z maksymalnπ wartoúciπ funkcji celu
// Znajdü indeks wierzcho≥ka o maksymalnej wartoúci funkcji celu
int max_vertex(solution* Xopt, int dim) {
	int max_index = 0;
	for (int i = 1; i <= dim; i++) {
		if (Xopt[i].y > Xopt[max_index].y) {
			max_index = i;
		}
	}
	return max_index;
}

// Znajdü indeks wierzcho≥ka o minimalnej wartoúci funkcji celu
int min_vertex(solution* Xopt, int dim) {
	int min_index = 0;
	for (int i = 1; i <= dim; i++) {
		if (Xopt[i].y < Xopt[min_index].y) {
			min_index = i;
		}
	}
	return min_index;
}

// Oblicz úrodek masy wszystkich wierzcho≥kÛw, z wy≥πczeniem maksymalnego
matrix mass_center(solution* Xopt, int dim, int exclude_index) {
	int count = 0;
	matrix center = matrix(Xopt[0].x.rows(), Xopt[0].x.cols(), 0.0f); // Inicjalizuj zerowπ macierz o odpowiednich wymiarach

	for (int i = 0; i <= dim; i++) {
		if (i == exclude_index) continue; // PomiÒ maksymalny wierzcho≥ek
		center = center + Xopt[i].x;
		count++;
	}
	return center / static_cast<long double>(count); // Wylicz úredniπ (úrodek masy)
}



solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, long double s,
	long double alpha, long double beta, long double gamma, long double delta,
	long double epsilon, int Nmax, matrix ud1, matrix ud2) {

	try
	{
		int* size = get_size(x0);
		int dim = size[0];
		delete[] size;

		solution* Xopt = new solution[dim + 1];
		matrix e(dim, 1, 0.0f);

		for (int i = 0; i < dim; i++)
		{
			e(i, 0) = 1;
			Xopt[i].x = x0 + s * e;
			Xopt[i].y = ff(Xopt[i].x, ud1, ud2); solution::f_calls++;
		}
		Xopt[dim].x = x0;
		Xopt[dim].y = ff(x0, ud1, ud2);
		int min, max;
		matrix p_center;
		matrix p_odb;
		matrix p_e;
		matrix ff_min;
		matrix ff_max;
		matrix ff_odb;

		for (int itr = 0; itr < Nmax; itr++)
		{
			max = max_vertex(Xopt, dim);
			min = min_vertex(Xopt, dim);

			if (norm(Xopt[max].x - Xopt[min].x) < epsilon) break;

			p_center = mass_center(Xopt, dim, max);
			p_odb = p_center + alpha * (p_center - Xopt[max].x);

			ff_min = Xopt[min].fit_fun(ff, ud1, ud2);
			ff_max = Xopt[max].fit_fun(ff, ud1, ud2);
			ff_odb = ff(p_odb, ud1, ud2); solution::f_calls++;
		}



		if (ff_odb < ff_min)
		{
			p_e = p_center + gamma * (p_odb - p_center);
			matrix ff_e = ff(p_e, ud1, ud2); solution::f_calls++;

			if (ff_e < ff_odb)
			{
				Xopt[max].x = p_e;
				Xopt[max].y = ff_e;
			}
			else
			{
				Xopt[max].x = p_odb;
				Xopt[max].y = ff_odb;
			}
		}
		else if (ff_min <= ff_odb && ff_odb < ff_max)
		{
			Xopt[max].x = p_odb;
			Xopt[max].y = ff_odb;
		}
		else
		{
			matrix p_z = p_center + beta * (Xopt[max].x - p_center);
			matrix ff_z = ff(p_z, ud1, ud2); solution::f_calls++;

			if (ff_z >= ff_max)
			{
				for (int i = 0; i < dim; i++)
				{
					if (i == min) continue;
					Xopt[i].x = delta * (Xopt[i].x + Xopt[min].x);
					Xopt[i].y = ff(Xopt[i].x, ud1, ud2); solution::f_calls++;
				}
			}
			else
			{
				Xopt[max].x = p_z;
				Xopt[max].y = ff_z;
			}
		}


		min = min_vertex(Xopt, dim);
		return Xopt[min];
	}

	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}