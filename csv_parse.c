#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curve.h"
#include "Interpolation.h"

#define MAX_DATA 100

typedef struct {
    int year;           // Changed to int since we're using atoi
    double internet_user;
    double population;
} DataPoint;

int main() {
    FILE *file = fopen("Data Tugas Pemrograman A.csv", "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        return 1;
    }

    char line[1024];
    char *token;
    DataPoint data[MAX_DATA];
    int count = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    // Read data
    while (fgets(line, sizeof(line), file) && count < MAX_DATA) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        
        // Parse year
        token = strtok(line, ",");
        if (token != NULL) {
            data[count].year = atoi(token);
            
            // Parse internet user percentage
            token = strtok(NULL, ",");
            if (token != NULL) {
                data[count].internet_user = atof(token);
                
                // Parse population
                token = strtok(NULL, ",");
                if (token != NULL) {
                    // Remove any non-numeric characters
                    char *end;
                    data[count].population = strtod(token, &end);
                    count++;
                }
            }
        }
    }

    fclose(file);

    // Print parsed data to verify
    printf("Parsed Data:\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%.6f\t%.0f\n", 
               data[i].year, 
               data[i].internet_user, 
               data[i].population);
    }

    double hasil LangrangeInterpolation

    return 0;
}