//
//  Auto Regression / Adaline / Widrow-Hoff Rule
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 7/29/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#include "AutoRegression.h"

/* Extract submatrix from a bigger matrix */
/* Free the matrix after usage in caller function */
mat submatrix(mat table, int start_row_idx, int start_col_idx, int rows, int cols) {
    
    int i, j;
    
    mat submat;
    _new_generalized(submat, rows, cols);
    
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            submat[i][j] = table[i+start_row_idx][j+start_col_idx];
            //printf("%d, %d\n", i, j);
            //_show_generalized(submat, rows, cols);
        }
    }
    
    return submat;
}


void test_submatrix() {
    
    double A[5][5] = {  {1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};
    int x_rows = 5;
    int x_cols = 5;
    int x_sub_rows = 3;
    int x_sub_cols = x_cols;
    
    /*
    printf("Input Matrix\n");
    int i, j;
    for (i = 0; i < x_rows; i++) {
        for (j = 0; j< x_cols; j++) {
            printf("%f  ", A[i][j]);
        }
        printf("\n");
    }
    */
    
    mat x;
    _new_generalized(x,x_rows, x_cols);
    x = _copy_generalized(A, x_rows, x_cols);
    _show_generalized(x, x_rows, x_cols);
    printf("\n");
    
    mat xhist;
    _new_generalized(xhist, x_sub_rows, x_sub_cols);
    xhist = submatrix(x, 0, 0, x_sub_rows, x_sub_cols);
    _show_generalized(xhist, x_sub_rows, x_sub_cols);
    
    _del_generalized(x);
    _del_generalized(xhist);
    
    return;
}


/* Flatten the histogram into a row vector */
/* Free the vector after use from caller function */
vector flatten_matrix(mat X, int rows, int cols) {
    int i, j, k;
    vector V;
    _new_vector(V, rows * cols);
    
    k = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            V[k++] = X[i][j];
        }
    }
    return V;
}

/* Considering X_hist as a 2d matrix */
/* autoRegression(p, T, i, d) */
/*
#define _AR(p, T, i, d) autoRegression(p, T, i, d)
int autoRegression(int span, int tot_time, int signal, int featureDimension) {

    int time_index;
    //double weights[featureDimension];
    
    // signal should not be > featureDim
    if (signal > featureDimension) {
        return ERROR;
    }
    
    int x_rows = 5, x_cols = 5;
    double A[5][5] = {  {1, 2, 3, 4, 5},
                                    {6, 7, 8, 9, 10},
                                    {11, 12, 13, 14, 15},
                                    {16, 17, 18, 19, 20},
                                    {21, 22, 23, 24, 25}};
    
    mat X;
    _new_generalized(X,x_rows, x_cols);
    X = _copy_generalized(A, x_rows, x_cols);
    _show_generalized(X, x_rows, x_cols);
    printf("\n");
    
    //list weights;
    //_new_list(weights, featureDimension);
    //_show_list(weights, featureDimension);
    
    
    double step_param;
    mat X_hist, y_t;
    _new_generalized(X_hist, span, featureDimension);
    _new_generalized(y_t, span, 1);
    
    for (time_index = span; time_index < tot_time; time_index++) {
        printf("Iteration %d\n", time_index-span);
        step_param = 0.1;  // alpha
        X_hist = submatrix(X, (time_index-span), 0, span, featureDimension);
        _show_generalized(X_hist, span, featureDimension);
        y_t = submatrix(X, (time_index-span), (signal-1), span, 1);
        _show_generalized(y_t, span, 1);
     }
    
    
    return SUCCESS;
}
*/


/* Considering X_hist as a column vector by flattening histogram*/
/* autoRegression(p, T, i, d) */
#define _AR(p, T, i, d) autoRegression(p, T, i, d)
int autoRegression(int span, int tot_time, int signal, int featureDimension) {
 
    // signal should not be > featureDim
    if (signal > featureDimension) {
        return ERROR;
    }
 
    int x_rows = 5, x_cols = 5;
    double A[5][5] = {  {1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};
 
    mat X;
    _new_generalized(X,x_rows, x_cols);
    X = _copy_generalized(A, x_rows, x_cols);
    _show_generalized(X, x_rows, x_cols);
    printf("\n");
 
    int time_index;
    vector weights;
    double step_size;
    vector X_hist;
    double y_t;
    int vectorDimension = span * featureDimension;
    
    
    _new_vector(weights, vectorDimension);
    _show_vector(weights, vectorDimension);
    
    y_t = 0;
 
    for (time_index = span; time_index < tot_time; time_index++) {
        
        printf("\nIteration %d\n", time_index-span);
        step_size = 0.1;  // alpha
        
        mat tmp_sub_mat = submatrix(X, (time_index-span), 0, span, featureDimension);
        X_hist = flatten_matrix(tmp_sub_mat, span, featureDimension);
        _del_generalized(tmp_sub_mat);
        _show_vector(X_hist, vectorDimension);
        
        y_t = X[time_index][signal];
        printf("\ny_t = %f\n", y_t);
        
        // Adaline Update Rule
        weights = subtract_vectors_rowwise(weights, (multiply_vector_with_scalar(X_hist, (step_size * (multiply_vectors_rowwise(X_hist, weights, vectorDimension) - y_t)), vectorDimension)), vectorDimension);
        _show_vector(weights, vectorDimension);
        
        _delete_vector(X_hist);
    }
 
    _del_generalized(X);
    _delete_vector(weights);
 
    return SUCCESS;
 }
 


int main(int argc, const char * argv[]) {
    //test_submatrix();
    autoRegression(2, 5, 3, 5);
    return 0;
}