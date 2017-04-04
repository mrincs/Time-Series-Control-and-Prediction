//
//   LU decomposition
//---------------------
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/4/15. Taken from Rossettacode
//  Code in : http://rosettacode.org/wiki/LU_decomposition#C


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LUdecomposition.h"

//#define _zero(a) mat_zero(a, n)
void mat_zero(mat x, _dim) {
    int i,j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            x[i][j] = 0;
        }
    }
    
}

//#define _new(a) a = mat_new(n)
mat mat_new(_dim) {
    int i;
    mat x = malloc(sizeof(double *) * n);
    x[0] = malloc(sizeof(double) * n * n);
    
    for (i = 0; i < n; i++) {
        x[i] = x[0] + n*i;
    }
    _zero(x);
    
    return x;
}


//#define _copy(a) mat_copy(a, n)
mat mat_copy(void *a, _dim) {
    int i,j;
    mat x = mat_new(n);
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            x[i][j] = ((double (*)[n])a)[i][j];
        }
    }
    return x;
}


//#define _del(a) mat_del(a)
void mat_del(mat a) {
    free(a[0]);
    free(a);
}



//#define _mul(a, b) mat_mul(a, b, n)
mat mat_mul(mat a, mat b, _dim) {
    int i, j, k;
    
    mat c = _new(c);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    return c;
}


//#define _pivot(a, b) mat_pivot(a, b, n)
void mat_pivot(mat a,mat p, _dim) {
    
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            p[i][j] = (i==j);
        }
    }
    
    for (i = 0; i < n; i++) {
        int max_j = i;
        for (j = i ; j < n; j++) {
            if (fabs(a[j][i]) > fabs(a[max_j][i])) {
                max_j = j;
            }
        }
        if (max_j != i) {
            for (k = 0; k < n; k++) {
                _swap(p[i][k], p[max_j][k]);
            }
        }
    }
}


//#define _LU(a, l, u, p) mat_LU(a, l, u, p, n)
void mat_LU(mat A, mat L, mat U, mat P, _dim) {
    
    int i, j, k;
    
    _zero(L);
    _zero(U);
    
    for (i = 0; i < n; i++) {
        L[i][i] = 1;
    }
    
    _pivot(A, P);
    
    mat Aprime = _mul(P, A);
    
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            
            double s;
            
            if (i <= j) {
                s = 0;
                for ( k = 0; k < i; k++) {
                    s = s + L[i][k] * U[k][j];
                }
                U[i][j] = Aprime[i][j] - s;
            }
            
            if (i >= j) {
                s = 0;
                for (k = 0; k < j; k++) {
                    s = s + L[i][k] * U[k][j];
                }
                L[i][j] = (Aprime[i][j] - s)/ U[j][j];
            }
        }
    }
    _del(Aprime);
    
}




void mat_show(mat x, char *fmt, _dim)
{
    int i, j;
    
    if (!fmt) fmt = "%8.4g";
    for(i = 0; i < n; i++) {
        printf(i ? "      " : " [ ");
        for (j = 0; j < n; j++) {
            printf(fmt, x[i][j]);
            printf(j < n - 1 ? "  " : i == n - 1 ? " ]\n" : "\n");
        }
    }
}


// Example Matrices
double A3[3][3] = {{ 1, 3, 5 }, { 2, 4, 7 }, { 1, 1, 0 }};
double A4[4][4] = {{16, 9, 24, 2}, {1, 5, 2, 6}, {3, 17, 18, 1}, {2, 5, 7, 1}};

/*
int main()
{
    int n = 3;
    mat A, L, P, U;
    
    // Test with a 3X3 matrix
    _new(L); _new(P); _new(U);
    A = _copy(A3);
    _LU(A, L, U, P);
    _show(A); _show(L); _show(U); _show(P);
    _del(A);  _del(L);  _del(U);  _del(P);
    
    printf("\n");
    
    
    // Test with a 4X4 matrix
    n = 4;
    
    _new(L); _new(P); _new(U);
    A = _copy(A4);
    _LU(A, L, U, P);
    _show(A); _show(L); _show(U); _show(P);
    _del(A);  _del(L);  _del(U);  _del(P);
    
    return 0;
}

*/