# CSA02 – C Programming Assignment 3
**Searching, Sorting, Merging, 2D Arrays, String Processing, and System Design**

* **Student Name:** Samiksha
* **Register Number:** 1972260036
* **Compiler:** GCC 16.2.0 (`WinLibs x86_64-w64-mingw32`)
* **Compile Command:** `gcc -Wall -Wextra <folder>\<source.c> -o <folder>\<output.exe>`
* **Run Command:** `.\<folder>\<output.exe>`

---

## Question Summary & Results

| Question | Folder | Topic | Summary of Findings & Results |
| :--- | :--- | :--- | :--- |
| **Q1** | `Q1/` | Searching a Library Catalogue | Implemented linear and binary search with overflow-safe midpoint `low + (high - low) / 2`. Confirmed binary search takes at most **17 comparisons** vs **100,000** for linear search at $N = 100,000$. |
| **Q2** | `Q2/` | Sorting Seating Register | Benchmarked Bubble Sort (early-exit), Selection Sort, and Insertion Sort across Sorted, Nearly Sorted, Reverse, and Random inputs up to $N = 10,000$. Recommended **Insertion Sort** ($O(n)$) for nearly sorted registers with 20 late registrations. |
| **Q3** | `Q3/` | Merging Two Merit Lists | Implemented stable descending two-pointer merge in **$O(m + n)$** time (`19,999` comparisons vs `~285,754` for concatenate + `qsort` at $m = n = 10,000$), preserving Campus A priority on ties. |
| **Q4** | `Q4/` | 2D District Rainfall Records | Computed row totals, monthly column averages, wettest district-month, and `< 60%` deficit districts for `rain[38][12]`. Demonstrated row-major spatial cache locality on a `2,000 × 2,000` matrix. |
| **Q5** | `Q5/` | Text Processing Without `string.h` | Built manual and `string.h` versions of word counting (handling multiple spaces and tabs), uppercase conversion, string reversal, and case-insensitive palindrome checks; replaced unsafe `strcpy`/`gets` with `snprintf`/`fgets`. |
| **Q6** | `Q6/` | Sorting & Searching String Directory | Eliminated **162.5 million** character copies at $N = 5,000$ by sorting an integer index array instead of `strcpy` swaps on `names[5000][30]`; added binary search and adjacent duplicate detection. |
| **Q7** | `Q7/` | Student Council Election Counter | Designed a single-pass **$O(v + c \log c)$** election tally system from first principles with invalid ballot filtering, descending rank sorting, and tie detection; processed `500,000` votes in `< 2 ms`. |

---

## How to Compile and Run Any Question

1. Open PowerShell inside the repository root (`CSA02-1972260036-Assignment3`).
2. Compile and run any task (for example, `Q1`):
   ```powershell
   gcc -Wall -Wextra Q1\q1.c -o Q1\q1.exe
   .\Q1\q1.exe
   ```
3. Each folder (`Q1/` through `Q7/`) contains:
   * `qX.c` — Complete C source code
   * `analysis.md` — Theoretical derivations, complexity comparisons, and joint design decisions
   * `output.png` — Screenshot of program execution
