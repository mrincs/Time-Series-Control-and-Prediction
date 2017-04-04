//
//  matrix.h
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/6/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#ifndef __Time_Series_Control_and_Prediction__matrix__
#define __Time_Series_Control_and_Prediction__matrix__

#include <stdio.h>
#include <stdlib.h>

typedef double **mat;

void mat_zero_generalized(mat x, int rows, int cols);
mat mat_new_generalized(int rows, int cols);
void mat_show_generalized(mat x, char *fmt, int rows, int cols);
mat mat_copy_generalized(void *a, int rows, int cols);
void mat_del_generalized(mat a);

#define _zero_generalized(a, rows, cols) mat_zero_generalized(a, rows, cols)
#define _new_generalized(a, rows, cols) a = mat_new_generalized(rows, cols)
#define _show_generalized(a, rows, cols) printf(QUOTE(a)" =");mat_show_generalized(a, 0, rows, cols)
#define _copy_generalized(a, rows, cols) mat_copy_generalized(a, rows, cols)
#define _del_generalized(a) mat_del_generalized(a)


#endif /* defined(__Time_Series_Control_and_Prediction__matrix__) */
