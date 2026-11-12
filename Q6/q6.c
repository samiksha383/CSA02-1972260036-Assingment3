#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 5000
#define NAME_LEN 30

static char names[MAX_NAMES][NAME_LEN];
static int idx[MAX_NAMES];
static long long cmp_count = 0;
static long long char_copies = 0;

/* Safe input helper: strips trailing '\n' and flushes overflow */
void read_name_safe(FILE *fp, char dest[NAME_LEN])
{
    if (fgets(dest, NAME_LEN, fp)) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        } else {
            int ch;
            while ((ch = fgetc(fp)) != '\n' && ch != EOF); /* discard excess chars */
        }
    }
}

/* Case-insensitive string comparison */
int stricmp_custom(const char *a, const char *b)
{
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

/* Method 1: Sort 2D array directly using strcpy */
void sort_by_copy(int n)
{
    cmp_count = 0;
    char_copies = 0;
    char temp[NAME_LEN];
    for (int i = 1; i < n; i++) {
        strcpy(temp, names[i]);
        char_copies += (long long)strlen(names[i]) + 1;
        int j = i - 1;
        while (j >= 0) {
            cmp_count++;
            if (strcmp(names[j], temp) > 0) {
                strcpy(names[j + 1], names[j]);
                char_copies += (long long)strlen(names[j]) + 1;
                j--;
            } else {
                break;
            }
        }
        strcpy(names[j + 1], temp);
        char_copies += (long long)strlen(temp) + 1;
    }
}

/* Method 2: Sort index array only (0 character copies!) */
void sort_by_index(int n)
{
    cmp_count = 0;
    char_copies = 0;
    for (int i = 0; i < n; i++) idx[i] = i;

    for (int i = 1; i < n; i++) {
        int key_idx = idx[i];
        int j = i - 1;
        while (j >= 0) {
            cmp_count++;
            if (strcmp(names[idx[j]], names[key_idx]) > 0) {
                idx[j + 1] = idx[j];
                j--;
            } else {
                break;
            }
        }
        idx[j + 1] = key_idx;
    }
}

/* Binary search on sorted names */
int binary_search_names(int n, const char *target, int *search_comps)
{
    *search_comps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*search_comps)++;
        int c = strcmp(names[mid], target);
        if (c == 0) return mid;
        else if (c < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void populate_synthetic(int n)
{
    srand(123);
    for (int i = 0; i < n; i++) {
        snprintf(names[i], NAME_LEN, "Resident_%04d_HostelBlockA", rand() % n);
    }
}

int main(void)
{
    /* 1. Benchmark strcpy vs Index Sorting for 100, 500, 5000 names */
    int sizes[] = {100, 500, 5000};
    printf("=== Benchmark: Direct strcpy Sort vs. Index Array Sort ===\n");
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        populate_synthetic(n);
        sort_by_index(n);
        long long idx_cmps = cmp_count;

        sort_by_copy(n);
        printf("N = %4d | strcmp calls: %8lld | strcpy char copies: %10lld vs Index copies: 0\n",
               n, idx_cmps, char_copies);
    }

    /* 2. Boundary length test (29 vs 30 chars in char[30]) & Duplicate Detection */
    printf("\n=== Boundary Length (29 vs 30 chars) & Duplicate Report ===\n");
    char buf29[NAME_LEN], buf30[NAME_LEN];
    snprintf(buf29, NAME_LEN, "12345678901234567890123456789");  /* 29 chars + '\0' = fits! */
    snprintf(buf30, NAME_LEN, "123456789012345678901234567890"); /* 30 chars -> truncated to 29! */
    printf("29-char input stored as: \"%s\" (len=%zu)\n", buf29, strlen(buf29));
    printf("30-char input stored as: \"%s\" (len=%zu - 30th char truncated for '\\0'!)\n\n",
           buf30, strlen(buf30));

    /* Small directory test with duplicates and binary search */
    const char *sample[] = {"Zoya", "Arun", "Meera", "Arun", "Kiran", "Meera"};
    int m = 6;
    for (int i = 0; i < m; i++) snprintf(names[i], NAME_LEN, "%s", sample[i]);
    sort_by_copy(m);

    printf("Sorted Directory & Adjacent Duplicates:\n");
    for (int i = 0; i < m; i++) {
        printf("  [%d] %s%s\n", i, names[i],
               (i > 0 && strcmp(names[i], names[i - 1]) == 0) ? "  <-- DUPLICATE" : "");
    }

    int comps = 0;
    int pos1 = binary_search_names(m, "Kiran", &comps);
    printf("\nSearch \"Kiran\" (Present) : index = %d, strcmp calls = %d\n", pos1, comps);
    int pos2 = binary_search_names(m, "Rahul", &comps);
    printf("Search \"Rahul\" (Missing) : index = %d, strcmp calls = %d\n", pos2, comps);

    return 0;
}
