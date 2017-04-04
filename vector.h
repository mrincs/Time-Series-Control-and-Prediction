//
//  vector.h
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/6/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#ifndef __Time_Series_Control_and_Prediction__vector__
#define __Time_Series_Control_and_Prediction__vector__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LUdecomposition.h"


typedef double *vector;

void v_zero(vector v, int len);
vector v_new(int len);
void v_display(vector v, char *fmt, int len);
void v_del(vector v);
double v_mul_rowwise(vector v1, vector v2, int len);
vector vs_mul(vector v, double s, int len);
vector v_sub_rowwise(vector v1, vector v2, int len);
vector v_add_rowwise(vector v1, vector v2, int len);

#define _zero_vector(v, len) v_zero(v, len)
#define _new_vector(v, len) v = v_new(len)
#define _show_vector(v, len)   printf(QUOTE(v)" =");v_display(v, 0, len)
#define _delete_vector(v) v_del(v)
#define multiply_vectors_rowwise(v1, v2, len) v_mul_rowwise(v1, v2, len)
#define multiply_vector_with_scalar(v, s, len) vs_mul(v, s, len)
#define subtract_vectors_rowwise(v1, v2, len) v_sub_rowwise(v1, v2, len);
#define add_vector_rowwise(v1, v2, len) v_add_rowwise(v1, v2, len);

#endif /* defined(__Time_Series_Control_and_Prediction__vector__) */
