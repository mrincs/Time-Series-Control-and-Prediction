//  Row vector. Used instead of column vector due to efficient usage of resources
//  vector.c
//  Time Series Control and Prediction
//
//  Created by Mrinmoy Maity on 8/6/15.
//  Copyright (c) 2015 Mrinmoy Maity. All rights reserved.
//

#include "vector.h"


void v_zero(vector v, int len) {
    int i;
    for (i = 0; i < len; i++) {
        v[i] = 0;
    }
}

vector v_new(int len) {
    vector v = malloc(sizeof(double) * len);
    _zero_vector(v, len);
    return v;
    
}


void v_display(vector v, char *fmt, int len) {
    int i;
    if (!fmt) fmt = "%8.4g";
    for(i = 0; i < len; i++) {
        printf(fmt, v[i]);
    }
}


void v_del(vector v) {
    free(v);
}


double v_mul_rowwise(vector v1, vector v2, int len) {
    int i;
    double sum = 0.0;
    
    for (i = 0; i < len; i++) {
        sum = sum + v1[i] * v2[i];
    }
    return sum;
}


vector vs_mul(vector v, double s, int len) {
    int i;
    for (i = 0; i < len; i++) {
        v[i] = v[i] * s;
    }
    return v;
}


vector v_sub_rowwise(vector v1, vector v2, int len) {
    int i;
    for (i = 0; i < len; i++) {
        v1[i] = v1[i] - v2[i];
    }
    return v1;
}


vector v_add_rowwise(vector v1, vector v2, int len) {
    int i;
    for (i = 0; i < len; i++) {
        v1[i] = v1[i] + v2[i];
    }
    return v1;
}