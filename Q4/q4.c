#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISTRICTS 38
#define MONTHS 12

/* 1. Compute annual total rainfall per district (row totals) */
void compute_district_totals(int rows, int cols, const double rain[rows][cols], double totals[])
{
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) {
            sum += rain[i][j];
        }
        totals[i] = sum;
    }
}

/* 2. Compute monthly average rainfall across all districts (column averages) */
void compute_monthly_averages(int rows, int cols, const double rain[rows][cols], double month_avg[])
{
    for (int j = 0; j < cols; j++) {
        double sum = 0.0;
        for (int i = 0; i < rows; i++) {
            sum += rain[i][j];
        }
        month_avg[j] = sum / rows;
    }
}

/* 3. Find the wettest district-month (maximum element) */
double find_wettest(int rows, int cols, const double rain[rows][cols], int *best_d, int *best_m)
{
    double max_val = rain[0][0];
    *best_d = 0;
    *best_m = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (rain[i][j] > max_val) {
                max_val = rain[i][j];
                *best_d = i;
                *best_m = j;
            }
        }
    }
    return max_val;
}

/* 4. List districts whose annual rainfall fell below 60% of the state annual average */
void report_deficient_districts(int rows, const double totals[])
{
    double state_sum = 0.0;
    for (int i = 0; i < rows; i++) {
        state_sum += totals[i];
    }
    double state_avg = state_sum / rows;
    double threshold = 0.60 * state_avg;

    printf("State Annual Average: %.2f mm | 60%% Deficit Threshold: %.2f mm\n",
           state_avg, threshold);
    printf("Deficient Districts (< 60%% of state average): ");
    int found = 0;
    for (int i = 0; i < rows; i++) {
        if (totals[i] < threshold) {
            printf("District_%d (%.1f mm) ", i + 1, totals[i]);
            found++;
        }
    }
    if (!found) printf("None");
    printf("\n\n");
}

/* Cache locality benchmark on a 2,000 x 2,000 array */
void benchmark_traversal(void)
{
    const int N = 2000;
    double (*grid)[2000] = malloc((size_t)N * sizeof(*grid));
    if (!grid) return;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 1.0;

    volatile double sink = 0.0;

    /* Row-wise traversal (cache-friendly) */
    clock_t t1 = clock();
    double sum_row = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum_row += grid[i][j];
        }
    }
    clock_t t2 = clock();

    /* Column-wise traversal (cache-unfriendly strided access) */
    clock_t t3 = clock();
    double sum_col = 0.0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            sum_col += grid[i][j];
        }
    }
    clock_t t4 = clock();

    sink = sum_row + sum_col;
    (void)sink;

    double row_ms = 1000.0 * (double)(t2 - t1) / CLOCKS_PER_SEC;
    double col_ms = 1000.0 * (double)(t4 - t3) / CLOCKS_PER_SEC;

    printf("=== 2,000 x 2,000 Cache Locality Benchmark ===\n");
    printf("Row-wise traversal    : %.3f ms\n", row_ms);
    printf("Column-wise traversal : %.3f ms\n\n", col_ms);

    free(grid);
}

int main(void)
{
    /* 1. Hand-verified 3 x 4 verification matrix */
    double sample[3][4] = {
        {100.0, 200.0, 300.0, 400.0}, /* District 1 Total = 1000 mm */
        {150.0, 250.0, 350.0, 450.0}, /* District 2 Total = 1200 mm */
        { 50.0,  50.0, 100.0, 100.0}  /* District 3 Total =  300 mm (Deficient!) */
    };
    double totals[3], month_avg[4];
    int best_d = 0, best_m = 0;

    printf("=== Hand-Verified 3 x 4 Matrix ===\n");
    compute_district_totals(3, 4, sample, totals);
    for (int i = 0; i < 3; i++) {
        printf("District %d Annual Total: %.2f mm\n", i + 1, totals[i]);
    }

    compute_monthly_averages(3, 4, sample, month_avg);
    printf("Monthly Averages: ");
    for (int j = 0; j < 4; j++) {
        printf("M%d=%.2f ", j + 1, month_avg[j]);
    }
    printf("\n");

    double wet = find_wettest(3, 4, sample, &best_d, &best_m);
    printf("Wettest Record: District %d, Month %d (%.2f mm)\n", best_d + 1, best_m + 1, wet);
    report_deficient_districts(3, totals);

    /* 2. Full 38 Districts x 12 Months Simulation */
    double rain[DISTRICTS][MONTHS];
    srand(42);
    for (int i = 0; i < DISTRICTS; i++) {
        for (int j = 0; j < MONTHS; j++) {
            /* Make District 5 and District 22 drought-prone for testing */
            if (i == 4 || i == 21) {
                rain[i][j] = 15.0 + (rand() % 20);
            } else {
                rain[i][j] = 50.0 + (rand() % 150);
            }
        }
    }

    double full_totals[DISTRICTS];
    double full_avg[MONTHS];
    compute_district_totals(DISTRICTS, MONTHS, rain, full_totals);
    compute_monthly_averages(DISTRICTS, MONTHS, rain, full_avg);
    double max_rain = find_wettest(DISTRICTS, MONTHS, rain, &best_d, &best_m);

    printf("=== Full State Dataset (38 Districts x 12 Months) ===\n");
    printf("Wettest District-Month: District_%d, Month_%d (%.2f mm)\n",
           best_d + 1, best_m + 1, max_rain);
    report_deficient_districts(DISTRICTS, full_totals);

    /* 3. Row-wise vs Column-wise Traversal Benchmark */
    benchmark_traversal();

    return 0;
}
