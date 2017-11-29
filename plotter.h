#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BG 					' '		///< canvas background
#define LINE_POINT 			'.'		///< line style

#define POINT 				'@'		///< point marker

#if defined(WIN32) || defined(_WIN32)

#define BAR 				0xb3	///< error line between point and caps
#define TOP_END_OF_BAR 		0xc2	///< upper error cap
#define BOTTOM_END_OF_BAR 	0xc1	///< lower error cap

// double bars
// #define TOP_END_OF_BAR 		0xd1	// double bar (pseudographics)
// #define BOTTOM_END_OF_BAR 	0xcf	// double bar (pseudographics)

#else

#define BAR 				'|'		///< error line between point and caps
#define TOP_END_OF_BAR 		'~'		///< upper error cap
#define BOTTOM_END_OF_BAR 	'~'		///< lower error cap

#endif

// standard Windows cmd window: 25x80
#define LINES 				25		///< canvas height
#define COLUMNS 			80		///< canvas width

#define XTICKS_NUM			9		///< number of X-axis ticks
#define YTICKS_NUM			5		///< number of Y-axis ticks


extern int plot(int, double*, double*, double*, double*, double, double, bool);

#endif
