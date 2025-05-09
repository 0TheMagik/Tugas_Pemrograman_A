#include <stdio.h>


void NewtonInterpolation(double x[], double y[], int n, double xi, double *yint, double ea[]) {
    double fdd[n][n];

    for (int i = 0; i < n; i++) {
        fdd[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            fdd[i][j] = (fdd[i+1][j-1] - fdd[i][j-1]) / (x[i+j] - x[i]);
        }
    }

    double xterm = 1.0;
    yint[0] = fdd[0][0];

    for (int order = 1; order < n; order++) {
        xterm *= (xi - x[order - 1]);
        yint[order] = yint[order - 1] + fdd[0][order] * xterm;
        ea[order - 1] = yint[order] - yint[order - 1];
    }
}

double LangrangeInterpolation (double x[], int y[], int n, int xx){
    double hasil = 0;
    for(int i = 0; i < n ; i++){
        double product = y[i];
        for(int j = 0; j < n; j++){
            if (i != j){
                product = product * (xx - x[j])/(x[i] - x[j]);
            }
        }
        hasil = hasil + product;
    }
    return hasil;
}

