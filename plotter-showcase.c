#include "plotter.h"


void test(void)
{
	// some data
	int num = 7;
	double xs[] 	= 	{1., 	2., 	4., 	5., 	6., 	3., 	3.};
	double ys[] 	= 	{1., 	3., 	6., 	8., 	10., 	10., 	4.};
	double dys_up[] = 	{0.2, 	0.3, 	1., 	0.7, 	0.4, 	2., 	3.};
	double dys_dn[] = 	{0.2, 	0.3, 	1., 	0.7, 	0.4, 	2., 	1.};
	double line_a = 1.76, line_b = -0.7;

	plot(num, xs, ys, dys_up, dys_dn, line_a, line_b, true);
}


void test_woe(void)
{
	// some data
	int num = 7;
	double xs[] 	= 	{1., 	2., 	4., 	5., 	6., 	3., 	3.};
	double ys[] 	= 	{1., 	3., 	6., 	8., 	10., 	10., 	4.};
	double line_a = 1.76, line_b = -0.7;

	plot_without_errors(num, xs, ys, line_a, line_b);
}


int main(int argc, char const *argv[])
{
	printf("== plot() ==\n\n");
	test();

	printf("\n\n\n\n== plot_without_errors() ==\n\n");
	test_woe();

	printf("Press Enter to exit\n");
	getchar();
	return 0;
}
