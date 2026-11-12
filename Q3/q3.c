#include <stdio.h>
#include <stdlib.h>

/* Complete the Code: Merge two descending sorted arrays into out[] */
int merge(const int a[], int na, const int b[], int nb, int out[])
{
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] >= b[j]) { /* >= preserves Campus A priority on ties (stability) */
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
    }
    while (i < na) {
        out[k++] = a[i++];
    }
    while (j < nb) {
        out[k++] = b[j++];
    }
    return k;
}

int cmp_desc(const void *p1, const void *p2)
{
    int x = *(const int *)p1;
    int y = *(const int *)p2;
    return (y > x) - (y < x);
}

int main(void)
{
    /* 1. Prompt Expected Output Test */
    int campusA[] = {98, 91, 85, 72};
    int campusB[] = {95, 91, 80};
    int merged[7];
    int n = merge(campusA, 4, campusB, 3, merged);
    printf("Prompt Test: ");
    for (int i = 0; i < n; i++) printf("%d ", merged[i]);
    printf("\n");

    /* 2. Edge Case A: One Empty List */
    int empty_out[4];
    int n_empty = merge(campusA, 4, NULL, 0, empty_out);
    printf("Empty List Test (na=4, nb=0): ");
    for (int i = 0; i < n_empty; i++) printf("%d ", empty_out[i]);
    printf("\n");

    /* 3. Edge Case B: All Scores Equal */
    int eqA[] = {90, 90, 90};
    int eqB[] = {90, 90};
    int eq_out[5];
    int n_eq = merge(eqA, 3, eqB, 2, eq_out);
    printf("All Equal Test (na=3, nb=2):  ");
    for (int i = 0; i < n_eq; i++) printf("%d ", eq_out[i]);
    printf("\n");

    return 0;
}
