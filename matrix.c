//
//  matrix.c
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/6/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#include "matrix.h"

typedef double **mat;

void mat_zero_generalized(mat x, int rows, int cols) {
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            x[i][j] = 0;
        }
    }
}


mat mat_new_generalized(int rows, int cols) {
    int i;
    mat x = malloc(sizeof(double *) * rows);
    x[0] = malloc(sizeof(double) * rows * cols);
    
    for (i = 0; i < rows; i++) {
        x[i] = x[0] + cols*i;
    }
    _zero_generalized(x, rows, cols);
    
    return x;
}


void mat_show_generalized(mat x, char *fmt, int rows, int cols)
{
    int i, j;
    
    if (!fmt) fmt = "%8.4g";
    for(i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf(fmt, x[i][j]);
        }
        printf("\n");
    }
}



mat mat_copy_generalized(void *a, int rows, int cols) {
    int i,j;
    mat x = mat_new_generalized(rows, cols);
    
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            x[i][j] = ((double (*)[rows])a)[i][j];
        }
    }
    return x;
}

void mat_del_generalized(mat a) {
    free(a[0]);
    free(a);
}

