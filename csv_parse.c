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

    double years[MAX_DATA];
    double internet_users[MAX_DATA];
    double populations[MAX_DATA];
    
    for(int i = 0; i < count; i++) {
        years[i] = (double)data[i].year;
        internet_users[i] = data[i].internet_user;
        populations[i] = data[i].population;
    }

    // Years to interpolate
    int missing_years[] = {2005, 2006, 2015, 2016};
    int num_missing = sizeof(missing_years) / sizeof(missing_years[0]);

    // Calculate interpolation for missing years
    printf("\nInterpolated Values for Missing Years:\n");
    printf("Year\tPopulation\tInternet Users %%\n");
    for(int i = 0; i < num_missing; i++) {
        double pop = LangrangeInterpolation(years, populations, count, missing_years[i]);
        double internet = LangrangeInterpolation(years, internet_users, count, missing_years[i]);
        
        printf("%d\t%.2f\t%.6f\n", missing_years[i], pop, internet);
    }

    // Calculate predictions for 2030 and 2035
    printf("\nPredicted Values:\n");
    printf("Year\tPopulation\tInternet Users %%\n");
    int future_years[] = {2030, 2035};
    for(int i = 0; i < 2; i++) {
        double pop = LangrangeInterpolation(years, populations, count, future_years[i]);
        double internet = LangrangeInterpolation(years, internet_users, count, future_years[i]);
        
        printf("%d\t%f\t%f\n", future_years[i], pop, internet);
    }

    return 0;
}