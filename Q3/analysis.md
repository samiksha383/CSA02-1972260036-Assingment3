\# Q3 – Merging Two Merit Lists



\## 1. Student A: Mathematical Analysis \& Comparison

\* \*\*Comparisons for Lists of Sizes m and n:\*\*

&#x20; \* \*\*Best Case:\*\* \*\*\\(\\min(m, n)\\)\*\* comparisons (when every score in one campus is strictly higher than the highest score in the other campus).

&#x20; \* \*\*Worst Case:\*\* \*\*m + n - 1\*\* comparisons (when elements alternate until only one element remains uncompared).

\* \*\*Merge vs. Concatenate + Sort (`qsort`):\*\*



| List Sizes (m = n) | Merge Comparisons (m + n - 1) | Concatenate + Sort (\\(O((m+n)\\log\_2(m+n))\\)) | Speedup |

| :--- | :--- | :--- | :--- |

| `m = n = 1,000` | \*\*1,999\*\* | \*\*\~21,932\*\* | \*\*\~11× fewer comparisons\*\* |

| `m = n = 10,000` | \*\*19,999\*\* | \*\*\~285,754\*\* | \*\*\~14.3× fewer comparisons\*\* |



\* \*\*Extra Memory:\*\* The third array `out\[]` requires \*\*\\((m + n) \\times \\text{sizeof(int)}\\)\*\* bytes of auxiliary memory (O(m + n) space).



\## 2. Student B: Pseudocode \& Correctness

```text

MERGE\_DESC(A, na, B, nb, OUT):

&#x20;   i <- 0, j <- 0, k <- 0

&#x20;   while i < na and j < nb:

&#x20;       if A\[i] >= B\[j]: OUT\[k++] <- A\[i++]

&#x20;       else:            OUT\[k++] <- B\[j++]

&#x20;   while i < na: OUT\[k++] <- A\[i++]

&#x20;   while j < nb: OUT\[k++] <- B\[j++]

&#x20;   return k

```

\* \*\*Why Each Element is Compared at Most Once:\*\* Every comparison in the main `while` loop increments either `i` or `j` and places one element permanently into `out\[k]`. Once placed, it is never revisited.

\* \*\*How Empty Lists \& Remaining Elements Work:\*\* When `nb == 0`, `while (i < na \&\& j < nb)` is immediately false (`0 < 0` is false), skipping straight to `while (i < na)` which copies all `na` elements in $O(m)$ time with zero comparisons.

\* \*\*Stability on Equal Scores:\*\* Using `if (a\[i] >= b\[j])` ensures Campus A's candidate is placed before Campus B's candidate when scores tie, keeping relative campus order deterministic and stable.



\## 3. Joint Engineering Decision \& Alternative Complexity

\* \*\*When to Merge In-Place:\*\* Only on severely memory-constrained embedded hardware where allocating an extra $O(m + n)$ output array is impossible. The cost is losing $O(m + n)$ linear speed.

\* \*\*Complexity Summary:\*\*

&#x20; \* \*\*Two-Pointer Merge (Third Array):\*\* \*\*$O(m + n)$\*\* time, \*\*$O(m + n)$\*\* extra space.

&#x20; \* \*\*Concatenate + `qsort()`:\*\* \*\*$O((m + n)\\log(m + n))$\*\* time, \*\*$O(\\log(m + n))$\*\* stack space.

&#x20; \* \*\*Simple In-Place Merge (Insertion Shift):\*\* \*\*$O(m \\cdot n)$\*\* time, \*\*$O(1)$\*\* extra space.



