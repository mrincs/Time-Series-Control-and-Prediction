//
//  LUdecomposition.h
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/5/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#ifndef Time_Series_Control_and_Prediction_LUdecomposition_h
#define Time_Series_Control_and_Prediction_LUdecomposition_h

#define _dim int n
typedef double **mat;


void mat_zero(mat x, _dim);
mat mat_new(_dim);
mat mat_copy(void *a, _dim);
void mat_del(mat a);
mat mat_mul(mat a, mat b, _dim);
void mat_pivot(mat a,mat p, _dim);
void mat_LU(mat A, mat L, mat U, mat P, _dim);
void mat_show(mat x, char *fmt, _dim);




#define _zero(a) mat_zero(a, n)
#define _new(a) a = mat_new(n)
#define _copy(a) mat_copy(a, n)
#define _del(a) mat_del(a)
#define _mul(a, b) mat_mul(a, b, n)
#define _pivot(a, b) mat_pivot(a, b, n)
#define _LU(a, l, u, p) mat_LU(a, l, u, p, n)
#define _QUOT(x) #x
#define QUOTE(x) _QUOT(x)
#define _show(a) printf(QUOTE(a)" =");mat_show(a, 0, n)



#define foreach(a, b, c) (for (int a = b; a < c; a++))
#define for_i foreach(i, 0, n)
#define for_j foreach(j, 0, n)
#define for_k foreach(k, 0, n)
#define for_ij for_i for_j
#define for_ijk for_ij for_k
#define _dim int n
#define _swap(x, y) {typeof(x) tmp = x; x = y; y = tmp;}
#define _sum_k(a, b, c, s) {s = 0; foreach(k, a, b) s+=c; }


#endif
