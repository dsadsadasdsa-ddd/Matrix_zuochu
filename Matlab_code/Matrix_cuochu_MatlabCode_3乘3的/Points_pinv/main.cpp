#include <stdio.h>
#include "point_pinv.h"

int main()
{
	double result[3] = { 0 };
	point_pinv(result);
	getchar();
	return 0;
}