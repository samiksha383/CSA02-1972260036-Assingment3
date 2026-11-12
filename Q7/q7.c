#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 12

typedef struct {
    int id;
    long votes;
} CandidateResult;

void run_election(const int votes[], long num_votes, int num_candidates, int show_details)
{
    long counts[MAX_CANDIDATES + 1] = {0}; /* 1-indexed: candidates 1..num_candidates */
    long valid_votes = 0;
    long invalid_votes = 0;

    clock_t start = clock();

    /* Stage 2: Single-pass O(v) counting */
    for (long i = 0; i < num_votes; i++) {
        int v = votes[i];
        if (v >= 1 && v <= num_candidates) {
            counts[v]++;
            valid_votes++;
        } else {
            invalid_votes++;
        }
    }

    /* Populate result structs and sort descending (Insertion Sort on c <= 12) */
    CandidateResult res[MAX_CANDIDATES];
    for (int c = 0; c < num_candidates; c++) {
        res[c].id = c + 1;
        res[c].votes = counts[c + 1];
    }

    for (int i = 1; i < num_candidates; i++) {
        CandidateResult key = res[i];
        int j = i - 1;
        while (j >= 0 && res[j].votes < key.votes) {
            res[j + 1] = res[j];
            j--;
        }
        res[j + 1] = key;
    }

    clock_t end = clock();
    double elapsed_ms = 1000.0 * (double)(end - start) / CLOCKS_PER_SEC;

    if (show_details) {
        printf("=== Hand-Verified Election Test (%ld total votes, %d candidates) ===\n",
               num_votes, num_candidates);
        printf("Valid Votes: %ld | Invalid Votes: %ld\n", valid_votes, invalid_votes);
        for (int c = 0; c < num_candidates; c++) {
            printf("  Rank %d: Candidate #%d -> %ld votes\n",
                   c + 1, res[c].id, res[c].votes);
        }

        /* Tie detection logic */
        if (valid_votes == 0) {
            printf("Result: No valid votes cast.\n\n");
        } else if (num_candidates > 1 && res[0].votes == res[1].votes) {
            printf("Result: TIE between Candidate #%d and Candidate #%d (%ld votes each)!\n\n",
                   res[0].id, res[1].id, res[0].votes);
        } else {
            printf("Result: WINNER is Candidate #%d with %ld votes.\n\n",
                   res[0].id, res[0].votes);
        }
    } else {
        printf("Scale Test: %7ld votes -> Valid: %7ld | Invalid: %6ld | Time: %.3f ms\n",
               num_votes, valid_votes, invalid_votes, elapsed_ms);
    }
}

int main(void)
{
    /* 1. Hand-verified small vote set (includes invalid votes 0, -2, 9 and a tie between #1 and #3) */
    int sample_votes[] = {1, 3, 2, 1, 0, 3, -2, 4, 9, 1, 3, 2};
    int n_sample = sizeof(sample_votes) / sizeof(sample_votes[0]);
    run_election(sample_votes, n_sample, 4, 1);

    /* 2. Performance benchmark for 5,000 and 500,000 votes */
    printf("=== Performance Benchmark (12 Candidates) ===\n");
    long bench_sizes[] = {5000, 500000};
    for (int b = 0; b < 2; b++) {
        long v_count = bench_sizes[b];
        int *bulk = (int *)malloc((size_t)v_count * sizeof(int));
        if (!bulk) return 1;

        srand(99);
        for (long i = 0; i < v_count; i++) {
            bulk[i] = (rand() % 15) - 1; /* Generates -1..13 (includes invalid votes) */
        }
        run_election(bulk, v_count, 12, 0);
        free(bulk);
    }
    return 0;
}
