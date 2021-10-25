/*
* File: funu_zuochu.c
*
* MATLAB Coder version            : 2.7
* C/C++ source code generated on  : 08-Sep-2021 14:26:39
*/

/* Include Files */
#include "rt_nonfinite.h"
#include "funu_zuochu.h"
#include <stdio.h>

/* Function Declarations */
static double b_eml_xnrm2(int n, const double x[216], int ix0);
static void eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[216],
	int ic0, double work[9]);
static double eml_matlab_zlarfg(int n, double *alpha1, double x[216], int ix0);
static double eml_xnrm2(const double x[216], int ix0);
static void eml_xswap(double x[216], int ix0, int iy0);
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
* Arguments    : int n
*                const double x[216]
*                int ix0
* Return Type  : double
*/
static double b_eml_xnrm2(int n, const double x[216], int ix0)
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
* Arguments    : int m
*                int n
*                int iv0
*                double tau
*                double C[216]
*                int ic0
*                double work[9]
* Return Type  : void
*/
static void eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[216],
	int ic0, double work[9])
{
	int lastv;
	int i;
	int lastc;
	boolean_T exitg2;
	int ia;
	int32_T exitg1;
	int i1;
	int jy;
	int ix;
	double c;
	int j;
	if (tau != 0.0) {
		lastv = m;
		i = iv0 + m;
		while ((lastv > 0) && (C[i - 2] == 0.0)) {
			lastv--;
			i--;
		}

		lastc = n;
		exitg2 = false;
		while ((!exitg2) && (lastc > 0)) {
			i = ic0 + (lastc - 1) * 24;
			ia = i;
			do {
				exitg1 = 0;
				if (ia <= (i + lastv) - 1) {
					if (C[ia - 1] != 0.0) {
						exitg1 = 1;
					}
					else {
						ia++;
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
			for (i = 1; i <= lastc; i++) {
				work[i - 1] = 0.0;
			}

			i = 0;
			i1 = ic0 + 24 * (lastc - 1);
			for (jy = ic0; jy <= i1; jy += 24) {
				ix = iv0;
				c = 0.0;
				j = (jy + lastv) - 1;
				for (ia = jy; ia <= j; ia++) {
					c += C[ia - 1] * C[ix - 1];
					ix++;
				}

				work[i] += c;
				i++;
			}
		}

		if (-tau == 0.0) {
		}
		else {
			i = ic0 - 1;
			jy = 0;
			for (j = 1; j <= lastc; j++) {
				if (work[jy] != 0.0) {
					c = work[jy] * -tau;
					ix = iv0;
					i1 = lastv + i;
					for (ia = i; ia + 1 <= i1; ia++) {
						C[ia] += C[ix - 1] * c;
						ix++;
					}
				}

				jy++;
				i += 24;
			}
		}
	}
}

/*
* Arguments    : int n
*                double *alpha1
*                double x[216]
*                int ix0
* Return Type  : double
*/
static double eml_matlab_zlarfg(int n, double *alpha1, double x[216], int ix0)
{
	double tau;
	double xnorm;
	int knt;
	int i0;
	int k;
	tau = 0.0;
	if (n <= 0) {
	}
	else {
		xnorm = b_eml_xnrm2(n - 1, x, ix0);
		if (xnorm != 0.0) {
			xnorm = rt_hypotd_snf(*alpha1, xnorm);
			if (*alpha1 >= 0.0) {
				xnorm = -xnorm;
			}

			if (fabs(xnorm) < 1.0020841800044864E-292) {
				knt = 0;
				do {
					knt++;
					i0 = (ix0 + n) - 2;
					for (k = ix0; k <= i0; k++) {
						x[k - 1] *= 9.9792015476736E+291;
					}

					xnorm *= 9.9792015476736E+291;
					*alpha1 *= 9.9792015476736E+291;
				} while (!(fabs(xnorm) >= 1.0020841800044864E-292));

				xnorm = rt_hypotd_snf(*alpha1, b_eml_xnrm2(n - 1, x, ix0));
				if (*alpha1 >= 0.0) {
					xnorm = -xnorm;
				}

				tau = (xnorm - *alpha1) / xnorm;
				*alpha1 = 1.0 / (*alpha1 - xnorm);
				i0 = (ix0 + n) - 2;
				for (k = ix0; k <= i0; k++) {
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
				i0 = (ix0 + n) - 2;
				for (k = ix0; k <= i0; k++) {
					x[k - 1] *= *alpha1;
				}

				*alpha1 = xnorm;
			}
		}
	}

	return tau;
}

/*
* Arguments    : const double x[216]
*                int ix0
* Return Type  : double
*/
static double eml_xnrm2(const double x[216], int ix0)
{
	double y;
	double scale;
	int k;
	double absxk;
	double t;
	y = 0.0;
	scale = 2.2250738585072014E-308;
	for (k = ix0; k <= ix0 + 23; k++) {
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

	return scale * sqrt(y);
}

/*
* Arguments    : double x[216]
*                int ix0
*                int iy0
* Return Type  : void
*/
static void eml_xswap(double x[216], int ix0, int iy0)
{
	int ix;
	int iy;
	int k;
	double temp;
	ix = ix0 - 1;
	iy = iy0 - 1;
	for (k = 0; k < 24; k++) {
		temp = x[ix];
		x[ix] = x[iy];
		x[iy] = temp;
		ix++;
		iy++;
	}
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
* Arguments    : double xm[9]
* Return Type  : void
*/
void funu_zuochu(double xm[9])
{
	double B[24];
	static const double b_B[24] = { -2.08381292186414, 1.2134834197918,
		-3.16581367492343, -1.0117031419245, 0.34809006654416, -1.15037980979967,
		-2.08381292186414, 1.2134834197918, -3.45440239144251, -0.787245684480467,
		-0.094229399336513, -1.15037980979967, -2.08381292186414, 1.2134834197918,
		-2.42095953986593, -0.937836455275374, 0.569242387905433, -1.15037980979967,
		-2.08381292186414, 1.2134834197918, -1.79167659167796, 0.561653746220372,
		-1.50788709249775, -1.15037980979967 };

	double A[216];
	static const double b_A[216] = { 0.012624106665439, 0.0, -0.008478403749059,
		0.012624106665439, -0.008478403749059, 1.0E-13, -0.00018022998848,
		-0.022253304851889, 0.012624106665439, -0.008478403749059, 1.0E-13,
		0.006389289516962, -0.010650116757995, 0.0, 0.012624106665439,
		-0.008478403749059, 1.0E-13, 0.013146434848445, 0.006219403968743, 0.0,
		0.012624106665439, -0.008478403749059, 1.0E-14, 4.2633E-14, 10.299788015772,
		-0.000255532897717, -0.002500964607704, 0.576830580792696,
		-0.006156940383443, -0.204837363556828, 0.102997880154201,
		-0.000255532897717, -0.002500964607704, 0.440555516053874, 0.002669003344975,
		-0.105681120975826, 0.102997880154201, -0.000255532897717,
		-0.002500964607704, 0.110746641043542, 0.006011012265116, -0.004579172423017,
		0.102997880154201, -0.000255532897717, -0.002500964607704,
		-0.145615572665585, -0.038811682163167, -0.060812225212553,
		-0.138459863375094, -0.019118809496031, 0.640069841185349,
		-0.787053877805143, 0.003466327212345, -0.687956689706998,
		-0.138459863375094, -0.019118809496031, 0.640069841185349,
		-0.602920346630641, -0.055642082657283, 0.109160921249486,
		-0.138459863375094, -0.019118809496031, -0.019118809496031,
		-0.148491072315152, -0.017277204899115, 0.748357343187755,
		-0.138459863375094, -0.019118809496031, 0.640069841185349, 0.20509423670572,
		0.022051931829274, 0.341406488484386, 1.04405749153127, 0.340730496396017,
		-0.423462813560605, 1.60910783664518, 1.52720514903964, -2.15044481005108,
		1.04405749153127, 0.340730496396017, -0.423462813560605, 1.32080069576222,
		1.12244792259891, -1.70398545316354, 1.04405749153127, 0.340730496396017,
		-0.423462813560605, 1.57678033952132, 0.403814816429035, -0.43749826223113,
		1.04405749153127, 0.340730496396017, -0.423462813560605, 1.18318922592379,
		-0.207189319292927, 0.573284515345446, 1.72764829639395, 2.05473702281759,
		-0.832732110664852, -1.65379407782794, 0.330476231922734, -2.2537310945621,
		1.72764829639395, 2.05473702281759, -0.832732110664852, -2.34038534562772,
		0.656248285556745, -1.6776195833578, 1.72764829639395, 2.05473702281759,
		-0.832732110664852, -2.51499671365274, 2.27589418098688, -2.20949280195776,
		1.72764829639395, 2.05473702281759, -0.832732110664852, -2.68338331791973,
		2.82087658322209, -1.01736870738034, -0.685068584381291, 0.203408398381888,
		-0.169835402556852, -0.349500552910165, -0.014537985206255,
		0.296863794701024, -0.685068584381291, 0.203408398381888, -0.169835402556852,
		-0.294747960676447, -0.019510148761968, 0.291420138077107,
		-0.685068584381291, 0.203408398381888, -0.169835402556852,
		-0.404091085909845, -0.015567585016506, 0.290358245946913,
		-0.685068584381291, 0.203408398381888, -0.169835402556852,
		-0.413184818019773, -0.036259059716707, 0.277285293583299, -0.00819930697414,
		-0.012646459709786, 0.011640592226233, -0.00079342861312, -1.0591307925E-5,
		0.007862186039651, -0.00819930697414, -0.012646459709786, 0.011640592226233,
		0.002411552573127, -0.001413402909834, 0.006336720845252, -0.00819930697414,
		-0.012646459709786, 0.011640592226233, 0.005235337873566, -0.00677462665353,
		0.006354235107802, -0.00819930697414, -0.012646459709786, 0.011640592226233,
		0.005391368105586, -0.010905194218409, 0.004475811804413, -0.018219123275742,
		0.005683970825127, -0.004765496860614, -0.009356502141754, -0.00038960515964,
		0.007816565960153, -0.018219123275742, 0.005683970825127, -0.004765496860614,
		-0.007946771589605, -0.000497395754738, 0.007698365264901,
		-0.018219123275742, 0.005683970825127, -0.004765496860614, -0.01092990047032,
		-0.000294135938692, 0.007669574736237, -0.018219123275742, 0.005683970825127,
		-0.004765496860614, -0.011176564056065, -0.000773765582843,
		0.007353236783261, -0.000836413058706, 0.005226879797996, -0.004721183214046,
		-0.009918472519458, -0.000463784569487, -0.008000028693825,
		-0.000836413058706, 0.005226879797996, -0.004721183214046,
		-0.007927791559953, 0.001874504721572, -0.005463504590263,
		-0.000836413058706, 0.005226879797996, -0.004721183214046,
		-0.003154275939135, 0.005172821004281, -0.005410607773451,
		-0.000836413058706, 0.005226879797996, -0.004721183214046, 0.001172500985912,
		0.004674783991617, -0.00403905367705 };

	double tau[9];
	int k;
	double vn1[9];
	double vn2[9];
	signed char jpvt[9];
	double work[9];
	int pvt;
	double tol;
	int i;
	int i_i;
	int ix;
	double rankR;
	double absxk;
	double t;
	memcpy(&B[0], &b_B[0], 24U * sizeof(double));
	memcpy(&A[0], &b_A[0], 216U * sizeof(double));
	k = 1;
	for (pvt = 0; pvt < 9; pvt++) {
		jpvt[pvt] = (signed char)(1 + pvt);
		work[pvt] = 0.0;
		tol = eml_xnrm2(b_A, k);
		vn2[pvt] = tol;
		k += 24;
		vn1[pvt] = tol;
	}

	for (i = 0; i < 9; i++) {
		i_i = i + i * 24;
		pvt = 1;
		if (9 - i > 1) {
			ix = i;
			tol = fabs(vn1[i]);
			for (k = 2; k <= 9 - i; k++) {
				ix++;
				rankR = fabs(vn1[ix]);
				if (rankR > tol) {
					pvt = k;
					tol = rankR;
				}
			}
		}

		pvt = (i + pvt) - 1;
		if (pvt + 1 != i + 1) {
			eml_xswap(A, 1 + 24 * pvt, 1 + 24 * i);
			ix = jpvt[pvt];
			jpvt[pvt] = jpvt[i];
			jpvt[i] = (signed char)ix;
			vn1[pvt] = vn1[i];
			vn2[pvt] = vn2[i];
		}

		tol = A[i_i];
		tau[i] = eml_matlab_zlarfg(24 - i, &tol, A, i_i + 2);
		A[i_i] = tol;
		if (i + 1 < 9) {
			tol = A[i_i];
			A[i_i] = 1.0;
			eml_matlab_zlarf(24 - i, 8 - i, i_i + 1, tau[i], A, (i + (i + 1) * 24) + 1,
				work);
			A[i_i] = tol;
		}

		for (k = i + 1; k + 1 < 10; k++) {
			pvt = (i + 24 * k) + 1;
			if (vn1[k] != 0.0) {
				tol = fabs(A[i + 24 * k]) / vn1[k];
				tol = 1.0 - tol * tol;
				if (tol < 0.0) {
					tol = 0.0;
				}

				rankR = vn1[k] / vn2[k];
				rankR = tol * (rankR * rankR);
				if (rankR <= 1.4901161193847656E-8) {
					tol = 0.0;
					rankR = 2.2250738585072014E-308;
					ix = (pvt - i) + 23;
					while (pvt + 1 <= ix) {
						absxk = fabs(A[pvt]);
						if (absxk > rankR) {
							t = rankR / absxk;
							tol = 1.0 + tol * t * t;
							rankR = absxk;
						}
						else {
							t = absxk / rankR;
							tol += t * t;
						}

						pvt++;
					}

					tol = rankR * sqrt(tol);
					vn1[k] = tol;
					vn2[k] = vn1[k];
				}
				else {
					vn1[k] *= sqrt(tol);
				}
			}
		}
	}

	rankR = 0.0;
	tol = 24.0 * fabs(A[0]) * 2.2204460492503131E-16;
	k = 0;
	while ((k < 9) && (!(fabs(A[k + 24 * k]) <= tol))) {
		rankR++;
		k++;
	}

	memset(&xm[0], 0, 9U * sizeof(double));
	for (k = 0; k < 9; k++) {
		if (tau[k] != 0.0) {
			tol = B[k];
			for (i = 0; i <= 22 - k; i++) {
				pvt = (k + i) + 1;
				tol += A[pvt + 24 * k] * B[pvt];
			}

			tol *= tau[k];
			if (tol != 0.0) {
				B[k] -= tol;
				for (i = 0; i <= 22 - k; i++) {
					pvt = (k + i) + 1;
					B[pvt] -= A[pvt + 24 * k] * tol;
				}
			}
		}
	}

	for (i = 0; i < (int)rankR; i++) {
		xm[jpvt[i] - 1] = B[i];
	}

	for (k = 0; k < (int)-(1.0 + (-1.0 - rankR)); k++) {
		tol = rankR + -(double)k;
		xm[jpvt[(int)tol - 1] - 1] /= A[((int)tol + 24 * ((int)tol - 1)) - 1];
		for (i = 0; i <= (int)tol - 2; i++) {
			xm[jpvt[i] - 1] -= xm[jpvt[(int)tol - 1] - 1] * A[i + 24 * ((int)tol - 1)];
		}
	}
	for (int i =0; i < 9;i++)
	printf("xm=%f\n", xm[i]);
}

/*
* File trailer for funu_zuochu.c
*
* [EOF]
*/
