#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculateConstants(int n, double x[], double y[], double *a, double *b) {
    double sumX = 0, sumX2 = 0, sumY = 0, sumXY = 0;

    for (int i = 0; i < n; i++) {
        double logX = log(x[i]);
        double logY = log(y[i]);
        sumX += logX;
        sumX2 += logX * logX;
        sumY += logY;
        sumXY += logX * logY;
    }

    *b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double A = (sumY - (*b) * sumX) / n;

    *a = exp(A);
}

void parseInputFromCSV(const char *filename, int *n, double **x, double **y) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *n = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        (*n)++;
    }

    *x = (double *)malloc((*n) * sizeof(double));
    *y = (double *)malloc((*n) * sizeof(double));


    rewind(file);

    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%lf,%lf", &(*x)[i], &(*y)[i]);
        i++;
    }

    fclose(file);
}

void writeResultsToCSV(const char *filename, double a, double b) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write the results to the CSV file
    fprintf(file, "a,b\n");
    fprintf(file, "%.6lf,%.6lf\n", a, b);

    fclose(file);
}

int main() {
    int n;
    double *x, *y, a, b;

    parseInputFromCSV("input.csv", &n, &x, &y);

    calculateConstants(n, x, y, &a, &b);

    writeResultsToCSV("output.csv", a, b);

    free(x);
    free(y);

    return 0;
}