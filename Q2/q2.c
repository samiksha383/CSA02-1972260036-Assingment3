#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long comps;
    long long moves; /* swaps for bubble/selection, shifts for insertion */
} Metrics;

Metrics bubble_sort(int a[], int n)
{
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            m.comps++;
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                m.moves++;
                swapped = 1;
            }
        }
        if (!swapped) break; /* Early-exit optimization */
    }
    return m;
}

Metrics selection_sort(int a[], int n)
{
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m.comps++;
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int tmp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = tmp;
            m.moves++;
        }
    }
    return m;
}

Metrics insertion_sort(int a[], int n)
{
    Metrics m = {0, 0};
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            m.comps++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                m.moves++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
    return m;
}

void generate_data(int base[], int n, int type)
{
    /* 0 = Sorted, 1 = Nearly Sorted (20 late registrations), 2 = Reverse, 3 = Random */
    for (int i = 0; i < n; i++) base[i] = 1000 + i;

    if (type == 1) {
        int k = (n < 20) ? n / 4 : 20;
        for (int i = 0; i < k; i++) {
            int idx1 = (i * 37) % n;
            int idx2 = (idx1 + 3) % n;
            int t = base[idx1]; base[idx1] = base[idx2]; base[idx2] = t;
        }
    } else if (type == 2) {
        for (int i = 0; i < n; i++) base[i] = 1000 + (n - 1 - i);
    } else if (type == 3) {
        srand(42);
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int t = base[i]; base[i] = base[j]; base[j] = t;
        }
    }
}

int main(void)
{
    int sizes[] = {100, 1000, 10000};
    const char *labels[] = {"Sorted", "Nearly Sorted", "Reverse", "Random"};

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int *base = (int *)malloc((size_t)n * sizeof(int));
        int *work = (int *)malloc((size_t)n * sizeof(int));

        printf("=== N = %d ===\n", n);
        for (int t = 0; t < 4; t++) {
            generate_data(base, n, t);

            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics mb = bubble_sort(work, n);

            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics ms = selection_sort(work, n);

            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics mi = insertion_sort(work, n);

            printf("%-13s | Bubble: %8lldc / %8lldsw | Select: %8lldc / %5lldsw | Insert: %8lldc / %8lldsh\n",
                   labels[t], mb.comps, mb.moves, ms.comps, ms.moves, mi.comps, mi.moves);
        }
        printf("\n");
        free(base);
        free(work);
    }
    return 0;
}
