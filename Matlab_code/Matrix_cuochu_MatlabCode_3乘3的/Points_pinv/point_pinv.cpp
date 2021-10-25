/*
* File: point_pinv.c
*
* MATLAB Coder version            : 2.7
* C/C++ source code generated on  : 07-Sep-2021 15:45:59
*/

/* Include Files */
#include "rt_nonfinite.h"
#include "point_pinv.h"
#include <stdio.h>

/* Function Declarations */
static double eml_matlab_zlarfg(int n, double *alpha1, double x[12], int ix0);
static double eml_xnrm2(int n, const double x[12], int ix0);
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
* Arguments    : int n
*                double *alpha1
*                double x[12]
*                int ix0
* Return Type  : double
*/
static double eml_matlab_zlarfg(int n, double *alpha1, double x[12], int ix0)
{
	double tau;
	double xnorm;
	int knt;
	int i1;
	int k;
	tau = 0.0;
	if (n <= 0) {
	}
	else {
		xnorm = eml_xnrm2(n - 1, x, ix0);
		if (xnorm != 0.0) {
			xnorm = rt_hypotd_snf(*alpha1, xnorm);
			if (*alpha1 >= 0.0) {
				xnorm = -xnorm;
			}

			if (fabs(xnorm) < 1.0020841800044864E-292) {
				knt = 0;
				do {
					knt++;
					i1 = (ix0 + n) - 2;
					for (k = ix0; k <= i1; k++) {
						x[k - 1] *= 9.9792015476736E+291;
					}

					xnorm *= 9.9792015476736E+291;
					*alpha1 *= 9.9792015476736E+291;
				} while (!(fabs(xnorm) >= 1.0020841800044864E-292));

				xnorm = rt_hypotd_snf(*alpha1, eml_xnrm2(n - 1, x, ix0));
				if (*alpha1 >= 0.0) {
					xnorm = -xnorm;
				}

				tau = (xnorm - *alpha1) / xnorm;
				*alpha1 = 1.0 / (*alpha1 - xnorm);
				i1 = (ix0 + n) - 2;
				for (k = ix0; k <= i1; k++) {
					x[k - 1] *= *alpha1;
				}

				for (k = 1; k <= knt; k++) {
					xnorm *= 1.0020841800044864E-292;
				}

				*alpha1 = xnorm;
			}
			else {
				tau = (xnorm - *alpha1) / xnorm;
				*alpha1 = 1.0 / (*alpha1 - xnorm);
				i1 = (ix0 + n) - 2;
				for (k = ix0; k <= i1; k++) {
					x[k - 1] *= *alpha1;
				}

				*alpha1 = xnorm;
			}
		}
	}

	return tau;
}

/*
* Arguments    : int n
*                const double x[12]
*                int ix0
* Return Type  : double
*/
static double eml_xnrm2(int n, const double x[12], int ix0)
{
	double y;
	double scale;
	int kend;
	int k;
	double absxk;
	double t;
	y = 0.0;
	if (n < 1) {
	}
	else if (n == 1) {
		y = fabs(x[ix0 - 1]);
	}
	else {
		scale = 2.2250738585072014E-308;
		kend = (ix0 + n) - 1;
		for (k = ix0; k <= kend; k++) {
			absxk = fabs(x[k - 1]);
			if (absxk > scale) {
				t = scale / absxk;
				y = 1.0 + y * t * t;
				scale = absxk;
			}
			else {
				t = absxk / scale;
				y += t * t;
			}
		}

		y = scale * sqrt(y);
	}

	return y;
}

/*
* Arguments    : double u0
*                double u1
* Return Type  : double
*/
static double rt_hypotd_snf(double u0, double u1)
{
	double y;
	double a;
	double b;
	a = fabs(u0);
	b = fabs(u1);
	if (a < b) {
		a /= b;
		y = b * sqrt(a * a + 1.0);
	}
	else if (a > b) {
		b /= a;
		y = a * sqrt(b * b + 1.0);
	}
	else if (rtIsNaN(b)) {
		y = b;
	}
	else {
		y = a * 1.4142135623730951;
	}

	return y;
}

/*
* FUNCPINV Summary of this function goes here
*    Detailed explanation goes here
* Arguments    : double x[3]
* Return Type  : void
*/
void point_pinv(double x[3])
{
	double B[4];
	int i0;
	double A[12];
	static const double b_A[12] = { 1.0, 4.0, 7.0, 10.0, 2.0, 5.0, 8.0, 11.0, 3.0,
		6.0, 9.0, 12.0 };

	double tau[3];
	signed char jpvt[3];
	double work[3];
	int k;
	double vn1[3];
	double vn2[3];
	int iy;
	double tol;
	double rankR;
	int itemp;
	static const signed char iv0[12] = { 1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12 };

	double t;
	int i;
	int i_i;
	int ix;
	int pvt;
	int i_ip1;
	int lastv;
	int lastc;
	boolean_T exitg2;
	int32_T exitg1;
	double absxk;
	for (i0 = 0; i0 < 4; i0++) {
		B[i0] = 2.0 + 3.0 * (double)i0;
	}

	memcpy(&A[0], &b_A[0], 12U * sizeof(double));
	for (i0 = 0; i0 < 3; i0++) {
		jpvt[i0] = (signed char)(1 + i0);
		work[i0] = 0.0;
	}

	k = 1;
	for (iy = 0; iy < 3; iy++) {
		tol = 0.0;
		rankR = 2.2250738585072014E-308;
		for (itemp = k; itemp <= k + 3; itemp++) {
			if (iv0[itemp - 1] > rankR) {
				t = rankR / (double)iv0[itemp - 1];
				tol = 1.0 + tol * t * t;
				rankR = iv0[itemp - 1];
			}
			else {
				t = (double)iv0[itemp - 1] / rankR;
				tol += t * t;
			}
		}

		tol = rankR * sqrt(tol);
		vn1[iy] = tol;
		vn2[iy] = vn1[iy];
		k += 4;
	}

	for (i = 0; i < 3; i++) {
		i_i = i + (i << 2);
		itemp = 1;
		if (3 - i > 1) {
			ix = i;
			tol = vn1[i];
			for (k = 2; k <= 3 - i; k++) {
				ix++;
				if (vn1[ix] > tol) {
					itemp = k;
					tol = vn1[ix];
				}
			}
		}

		pvt = (i + itemp) - 1;
		if (pvt + 1 != i + 1) {
			ix = pvt << 2;
			iy = i << 2;
			for (k = 0; k < 4; k++) {
				tol = A[ix];
				A[ix] = A[iy];
				A[iy] = tol;
				ix++;
				iy++;
			}

			itemp = jpvt[pvt];
			jpvt[pvt] = jpvt[i];
			jpvt[i] = (signed char)itemp;
			vn1[pvt] = vn1[i];
			vn2[pvt] = vn2[i];
		}

		rankR = A[i_i];
		tau[i] = eml_matlab_zlarfg(4 - i, &rankR, A, i_i + 2);
		A[i_i] = rankR;
		if (i + 1 < 3) {
			rankR = A[i_i];
			A[i_i] = 1.0;
			i_ip1 = (i + ((i + 1) << 2)) + 1;
			if (tau[i] != 0.0) {
				lastv = 4 - i;
				itemp = (i_i - i) + 3;
				while ((lastv > 0) && (A[itemp] == 0.0)) {
					lastv--;
					itemp--;
				}

				lastc = 2 - i;
				exitg2 = false;
				while ((!exitg2) && (lastc > 0)) {
					itemp = i_ip1 + ((lastc - 1) << 2);
					k = itemp;
					do {
						exitg1 = 0;
						if (k <= (itemp + lastv) - 1) {
							if (A[k - 1] != 0.0) {
								exitg1 = 1;
							}
							else {
								k++;
							}
						}
						else {
							lastc--;
							exitg1 = 2;
						}
					} while (exitg1 == 0);

					if (exitg1 == 1) {
						exitg2 = true;
					}
				}
			}
			else {
				lastv = 0;
				lastc = 0;
			}

			if (lastv > 0) {
				if (lastc == 0) {
				}
				else {
					for (iy = 1; iy <= lastc; iy++) {
						work[iy - 1] = 0.0;
					}

					iy = 0;
					i0 = i_ip1 + ((lastc - 1) << 2);
					for (itemp = i_ip1; itemp <= i0; itemp += 4) {
						ix = i_i;
						tol = 0.0;
						pvt = (itemp + lastv) - 1;
						for (k = itemp; k <= pvt; k++) {
							tol += A[k - 1] * A[ix];
							ix++;
						}

						work[iy] += tol;
						iy++;
					}
				}

				if (-tau[i] == 0.0) {
				}
				else {
					itemp = i_ip1 - 1;
					pvt = 0;
					for (iy = 1; iy <= lastc; iy++) {
						if (work[pvt] != 0.0) {
							tol = work[pvt] * -tau[i];
							ix = i_i;
							i0 = lastv + itemp;
							for (k = itemp; k + 1 <= i0; k++) {
								A[k] += A[ix] * tol;
								ix++;
							}
						}

						pvt++;
						itemp += 4;
					}
				}
			}

			A[i_i] = rankR;
		}

		for (iy = i + 1; iy + 1 < 4; iy++) {
			itemp = (i + (iy << 2)) + 1;
			if (vn1[iy] != 0.0) {
				tol = fabs(A[i + (iy << 2)]) / vn1[iy];
				tol = 1.0 - tol * tol;
				if (tol < 0.0) {
					tol = 0.0;
				}

				rankR = vn1[iy] / vn2[iy];
				rankR = tol * (rankR * rankR);
				if (rankR <= 1.4901161193847656E-8) {
					tol = 0.0;
					if (3 - i == 1) {
						tol = fabs(A[itemp]);
					}
					else {
						rankR = 2.2250738585072014E-308;
						pvt = (itemp - i) + 3;
						while (itemp + 1 <= pvt) {
							absxk = fabs(A[itemp]);
							if (absxk > rankR) {
								t = rankR / absxk;
								tol = 1.0 + tol * t * t;
								rankR = absxk;
							}
							else {
								t = absxk / rankR;
								tol += t * t;
							}

							itemp++;
						}

						tol = rankR * sqrt(tol);
					}

					vn1[iy] = tol;
					vn2[iy] = vn1[iy];
				}
				else {
					vn1[iy] *= sqrt(tol);
				}
			}
		}
	}

	rankR = 0.0;
	tol = 4.0 * fabs(A[0]) * 2.2204460492503131E-16;
	k = 0;
	while ((k < 3) && (!(fabs(A[k + (k << 2)]) <= tol))) {
		rankR++;
		k++;
	}

	for (i = 0; i < 3; i++) {
		x[i] = 0.0;
	}

	for (iy = 0; iy < 3; iy++) {
		if (tau[iy] != 0.0) {
			tol = B[iy];
			for (i = 0; i <= 2 - iy; i++) {
				itemp = (iy + i) + 1;
				tol += A[itemp + (iy << 2)] * B[itemp];
			}

			tol *= tau[iy];
			if (tol != 0.0) {
				B[iy] -= tol;
				for (i = 0; i <= 2 - iy; i++) {
					itemp = (iy + i) + 1;
					B[itemp] -= A[itemp + (iy << 2)] * tol;
				}
			}
		}
	}

	for (i = 0; i < (int)rankR; i++) {
		x[jpvt[i] - 1] = B[i];
	}

	for (iy = 0; iy < (int)-(1.0 + (-1.0 - rankR)); iy++) {
		tol = rankR + -(double)iy;
		x[jpvt[(int)tol - 1] - 1] /= A[((int)tol + (((int)tol - 1) << 2)) - 1];
		for (i = 0; i <= (int)tol - 2; i++) {
			x[jpvt[i] - 1] -= x[jpvt[(int)tol - 1] - 1] * A[i + (((int)tol - 1) << 2)];
		}
	}
	for (int i = 0; i < 3; i++)
	printf("x=%f\n", x[i]);
	
}

/*
* File trailer for point_pinv.c
*
* [EOF]
*/
