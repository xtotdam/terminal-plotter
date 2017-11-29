#include "plotter.h"

void d_show1darray(double*, int);
void i_show1darray(int*, int);
void show2darray(int**, int, int);

int plot(int, double*, double*, double*, double*, double, double, bool);


void d_show1darray(double arr[], int xm)
{
	int i;
	for (i = 0; i < xm; i++)
	{
		printf("% .2g ", arr[i]);
	}
	printf("\n");
}


void i_show1darray(int arr[], int xm)
{
	int i;
	for (i = 0; i < xm; i++)
	{
		printf("% .2d ", arr[i]);
	}
	printf("\n");
}


void show2darray(int **arr, int xm, int ym)
{
	int i, j;
	for (i = 0; i < xm; i++)
	{
		for (j = 0; j < ym; j++)
		{
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
}


int plot(int num, double *xs, double *ys, double *dys_up, double *dys_dn, double line_a, double line_b, bool plot_errors)
{
	/**
	@param num length of arrays
	@param xs X coordinates of points
	@param ys Y coordinates of points
	@param dys_up upper Y coordinates' errors
	@param dys_dn lower Y coordinates' errors
	@param line_a line slope
	@param line_b line intercept
	@param plot_errors if we should plot errors
	*/

	int lines = LINES,
	    cols = COLUMNS - 1;
	int i, j;

	/// allocating space for canvas
	int **field = (int**)calloc(lines, sizeof(int*));
	for (i = 0; i < lines; i++)
	{
		field[i] = (int*)calloc(cols, sizeof(int));

		for (j = 0; j < cols; j++)
		{
			field[i][j] = BG;
		}
	}

	/// allocating space for X-axis
	char *xaxes = (char*)calloc((cols + 1), sizeof(char));
	for (j = 0; j < cols; j++)
	{
		xaxes[j] = BG;
	}
	xaxes[cols] = '\0';

	/// find edges of axes
	double minx = xs[0],
	       maxx = xs[0],
	       miny = ys[0] - dys_dn[0],
	       maxy = ys[0] + dys_up[0];

	if (num < 2)
	{
		return 101;	// data set not big enough to be plotted
	}

	for (i = 1; i < num; i++)
	{
		if (xs[i] < minx) { minx = xs[i]; }
		if (xs[i] > maxx) { maxx = xs[i]; }
		if (ys[i] - dys_dn[i] < miny) { miny = ys[i] - dys_dn[i]; }
		if (ys[i] + dys_up[i] > maxy) { maxy = ys[i] + dys_up[i]; }
	}

	if (line_a * minx + line_b < miny) { miny = line_a * minx + line_b; }
	if (line_a * maxx + line_b > maxy) { maxy = line_a * maxx + line_b; }

	/// create ticks
	int xticksnum = XTICKS_NUM,
	    yticksnum = YTICKS_NUM;
	double *xticks = (double*)calloc(xticksnum, sizeof(double));
	double *yticks = (double*)calloc(yticksnum, sizeof(double));
	double dx = maxx - minx,
	       dy = maxy - miny;
	char tempstr[100];
	int *xplaces = (int*)calloc(xticksnum, sizeof(int));
	int *yplaces = (int*)calloc(yticksnum, sizeof(int));

	for (i = 0; i < xticksnum; i++)
	{
		xticks[i] = minx + dx * (double)i / (xticksnum - 1.);
		xplaces[i] = (cols - 1) * i / (xticksnum - 1);
	}

	for (i = 0; i < yticksnum; i++)
	{
		yticks[i] = miny + dy * (double)i / (yticksnum - 1.);
		yplaces[i] = (lines - 1) * i / (yticksnum - 1);
	}
	// d_show1darray(xticks, xticksnum);
	// d_show1darray(yticks, yticksnum);
	// i_show1darray(xplaces, xticksnum);
	// i_show1darray(yplaces, yticksnum);

	/// create axis
	int chars;

	for (i = 0; i < yticksnum; i++)
	{
		chars = sprintf(tempstr, "%.4g", yticks[i]);
		for (j = 0; j < chars; j++)
		{
			// printf("%d  ", lines - yplaces[i]);
			field[ lines - yplaces[i] - 1 ][j] = tempstr[j];
		}
	}

	for (i = 0; i < xticksnum - 1; i++)
	{
		chars = sprintf(tempstr, "%.4g", xticks[i]);
		for (j = 0; j < chars; j++)
		{
			xaxes[xplaces[i] + j] = tempstr[j];
		}
	}

	/// last tick -- should be printed with margin from right
	chars = sprintf(tempstr, "%.2g", xticks[xticksnum - 1]);
	for (j = 0; j < chars; j++)
	{
		xaxes[xplaces[xticksnum - 1] + j - chars + 1] = tempstr[j];
	}

	/// line
	double x, y;
	int xcoord, ycoord;

	for (i = 0; i < cols; i++)
	{
		x = minx + dx * i / (cols - 1);
		y = line_a * x + line_b;
		xcoord = i;
		ycoord = floor((y - miny) / dy * (lines - 1));
		field[lines - ycoord - 1][xcoord] = LINE_POINT;
	}

	if (plot_errors)
	{
		/// errors
		int ycoord1;

		for (i = 0; i < num; i++)
		{
			x = xs[i];
			xcoord = floor((x - minx) / dx * (cols - 1));
			y = ys[i];
			ycoord1 = floor((y - miny) / dy * (lines - 1));

			y = ys[i] - dys_dn[i];
			ycoord = floor((y - miny) / dy * (lines - 1));
			if (ycoord != ycoord1)
			{
				for (j = ycoord; j < ycoord1; j++)
				{
					field[lines - j - 1][xcoord] = BAR;
				}
			}
			field[lines - ycoord - 1][xcoord] = BOTTOM_END_OF_BAR;

			y = ys[i] + dys_up[i];
			ycoord = floor((y - miny) / dy * (lines - 1));
			if (ycoord != ycoord1)
			{
				for (j = ycoord1; j < ycoord; j++)
				{
					field[lines - j - 1][xcoord] = BAR;
				}
			}
			field[lines - ycoord - 1][xcoord] = TOP_END_OF_BAR;
		}
	}

	/// points
	for (i = 0; i < num; i++)
	{
		x = xs[i];
		y = ys[i];
		xcoord = floor((x - minx) / dx * (cols - 1));
		ycoord = floor((y - miny) / dy * (lines - 1));
		// printf("%lf %lf - %d %d\n", x, y, xcoord, ycoord);
		field[lines - ycoord - 1][xcoord] = POINT;
	}

	/// output

	// d_show1darray(xs, num);
	// d_show1darray(ys, num);
	// d_show1darray(dys, num);
	printf("Plot borders are X: from %.6g to %.6g; Y: from %.6g to %.6g\n", minx, maxx, miny, maxy);
	show2darray(field, lines, cols);
	printf("%s\n", xaxes);
	fflush(stdout);

	/// freeing memory
	free(xaxes);
	free(xticks);
	free(yticks);
	free(xplaces);
	free(yplaces);
	for (i = 0; i < lines; i++)
	{
		free(field[i]);
	}
	free(field);

	return 0;
}
