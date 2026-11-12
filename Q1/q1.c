#include <stdio.h>
#include <stdlib.h>

int steps; /* comparisons made by the last search */

/* Complete the Code: Binary search on ascending sorted array */
int binary_search(const int a[], int n, int key)
{
    steps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

/* Linear search on unsorted array */
int linear_search(const int a[], int n, int key)
{
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (a[i] == key) {
            return i;
        }
    }
    return -1;
}

void run_scale_experiment(int size)
{
    int *arr = (int *)malloc((size_t)size * sizeof(int));
    if (!arr) return;
    for (int i = 0; i < size; i++) {
        arr[i] = 1000 + i * 2; /* Sorted even accession numbers */
    }

    int key_first = arr[0];
    int key_mid   = arr[(size - 1) / 2];
    int key_last  = arr[size - 1];
    int key_miss  = arr[size - 1] + 1; /* Odd number -> guaranteed missing */

    linear_search(arr, size, key_first); int lin_best = steps;
    linear_search(arr, size, key_mid);   int lin_avg  = steps;
    linear_search(arr, size, key_miss);  int lin_miss = steps;

    binary_search(arr, size, key_mid);   int bin_best = steps;
    binary_search(arr, size, key_last);  int bin_last = steps;
    binary_search(arr, size, key_miss);  int bin_miss = steps;

    printf("N = %6d | Linear (first/mid/miss): %d / %d / %d | Binary (mid/last/miss): %d / %d / %d\n",
           size, lin_best, lin_avg, lin_miss, bin_best, bin_last, bin_miss);
    free(arr);
}

int main(void)
{
    /* 1. Prompt Expected Output Test (10 books) */
    int accession[] = {1021, 1048, 1103, 1190, 1222, 1305, 1377, 1402, 1460, 1533};
    int n = sizeof accession / sizeof accession[0];
    int keys[] = {1021, 1305, 1533, 1400};

    printf("=== Trial Catalogue (10 Books) - Binary Search ===\n");
    for (int k = 0; k < 4; k++) {
        int pos = binary_search(accession, n, keys[k]);
        printf("Book %d -> index %d, comparisons = %d\n", keys[k], pos, steps);
    }

    printf("\n=== Trial Catalogue (10 Books) - Linear Search ===\n");
    for (int k = 0; k < 4; k++) {
        int pos = linear_search(accession, n, keys[k]);
        printf("Book %d -> index %d, comparisons = %d\n", keys[k], pos, steps);
    }

    /* 2. Student B Scale Experiments (1,000, 10,000, 100,000) */
    printf("\n=== Scale Comparison Experiment ===\n");
    run_scale_experiment(1000);
    run_scale_experiment(10000);
    run_scale_experiment(100000);

    return 0;
}
