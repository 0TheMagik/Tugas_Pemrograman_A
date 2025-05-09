#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curve.h"
#include "Interpolation.h"

#define MAX_DATA 100

typedef struct {
    int year;         
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

    fgets(line, sizeof(line), file);

    // Read data
    while (fgets(line, sizeof(line), file) && count < MAX_DATA) {
        line[strcspn(line, "\n")] = 0;
        
        // Parse year
        token = strtok(line, ",");
        if (token != NULL) {
            data[count].year = atoi(token);
            
            token = strtok(NULL, ",");
            if (token != NULL) {
                data[count].internet_user = atof(token);
                
                // Parse population
                token = strtok(NULL, ",");
                if (token != NULL) {
                    char *end;
                    data[count].population = strtod(token, &end);
                    count++;
                }
            }
        }
    }

    fclose(file);

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
    
    for(int i = 0; i < count; i++) {
        years[i] = (double)data[i].year;
        internet_users[i] = data[i].internet_user;
        populations[i] = data[i].population;
    }

    int recent_count = 10;
    int start_idx = count - recent_count;
    if (start_idx < 0) start_idx = 0;

    printf("1. Estimasi Jumlah Penduduk Indonesia tahun 2030:\n");
    double pop_2030 = LangrangeInterpolation(&years[start_idx], &populations[start_idx], recent_count, 2030);
    printf("   %.0f jiwa\n\n", pop_2030);

    printf("2. Estimasi Jumlah Pengguna Internet Indonesia tahun 2035:\n");
    double pop_2035 = LangrangeInterpolation(&years[start_idx], &populations[start_idx], recent_count, 2035);
    double internet_2035 = LangrangeInterpolation(&years[start_idx], &internet_users[start_idx], recent_count, 2035);
    

    pop_2035 = fabs(pop_2035);
    internet_2035 = fabs(internet_2035);
    internet_2035 = internet_2035 > 100 ? 100 : internet_2035;
    double internet_users_2035 = pop_2035 * (internet_2035 / 100.0);
    
    printf("   Persentase (uncapped): %.4f%%\n", internet_2035);
    printf("   Persentase (capped): %.4f%%\n", internet_2035);
    printf("   Populasi: %.0f jiwa\n", pop_2035);
    printf("   Jumlah Pengguna Internet: %.0f jiwa\n", internet_users_2035);

    return 0;
}