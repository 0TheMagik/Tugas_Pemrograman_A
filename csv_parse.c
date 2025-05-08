#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curve.h"
#include "Interpolation.h"

int main() {
    FILE *file = fopen("sample.csv", "r");
    char line[1024];
    int x[100] = {0}, y[100] = {0};
    int i = 0;

    while(fgets(line, sizeof(line), file)) {
        
        char *token = strtok(line, ",");
        
        if (strcmp(token, "axis") == 0) {
            continue; 
        }
        else {
            x[i] = atoi(token); 
            token = strtok(NULL, ",");
            y[i] = atoi(token); 
        }
        i++;
    }

    // print file
    // for(int i = 0; i < 100; i++){
    //     printf("(%d,%d)\n", x[i], y[i]);
    // }

    double hasil = LangrangeInterpolation(x, y, i, 3);
    
    fclose(file);

    return 0;
}