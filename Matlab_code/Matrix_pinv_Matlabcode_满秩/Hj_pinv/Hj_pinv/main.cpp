#include <stdio.h>
#include "Hj_pinv.h"


int main()
{
	double result[9];
	Hj_pinv(result);
	getchar();
	return 0;
}