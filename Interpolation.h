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

double LangrangeInterpolation(double x[], double y[], int n, double xx) {
    double result = 0.0;
    
    // Input validation
    if (n <= 0 || x == NULL || y == NULL) {
        printf("Error: Invalid input parameters\n");
        return 0.0;
    }

    // Use fewer points for better accuracy (use 4-6 nearest points)
    int start_idx = 0;
    int points_to_use = 6;  // Use 6 points for interpolation
    
    // Find the closest point to xx
    for (int i = 0; i < n - 1; i++) {
        if (x[i] <= xx && x[i + 1] >= xx) {
            start_idx = (i < 3) ? 0 : i - 2;
            break;
        }
    }
    
    // Adjust if near the end of the array
    if (start_idx + points_to_use > n) {
        start_idx = n - points_to_use;
    }
    
    // Calculate Lagrange interpolation using nearby points
    for (int i = start_idx; i < start_idx + points_to_use; i++) {
        double term = y[i];
        for (int j = start_idx; j < start_idx + points_to_use; j++) {
            if (i != j) {
                term *= (xx - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    
    return result;
}