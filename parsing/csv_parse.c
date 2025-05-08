#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("sample.csv", "r");
    char line[1024];
    int x[100] = {0}, y[100] = {0};
    int i = 0;
    while(fgets(line, sizeof(line), file)) {
        // Assuming the CSV file has two columns: x,y
        char *token = strtok(line, ",");
        if (strcmp(token, "axis") == 0) {
            continue; // Skip header line
        }
        else {
            x[i] = atoi(token); // Convert string to int
            token = strtok(NULL, ",");
            y[i] = atoi(token); // Convert string to int
        }
        i++;
    }
    for(int i = 0; i < 100; i++){
        printf("(%d,%d)\n", x[i], y[i]);
    }
    fclose(file);
    return 0;
}