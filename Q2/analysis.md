\# Q2 – Sorting the Examination Hall Seating Register



\## 1. Student A: Hand Trace on 6 Register Numbers (`\[105, 102, 108, 101, 104, 103]`)

\* \*\*Bubble Sort (Early-Exit):\*\*

&#x20; \* Pass 1: `\[102, 105, 101, 104, 103, 108]` (5 comps, 4 swaps)

&#x20; \* Pass 2: `\[102, 101, 104, 103, 105, 108]` (4 comps, 3 swaps)

&#x20; \* Pass 3: `\[101, 102, 103, 104, 105, 108]` (3 comps, 2 swaps)

&#x20; \* Pass 4: `\[101, 102, 103, 104, 105, 108]` (2 comps, \*\*0 swaps\*\* $\\rightarrow$ `swapped == 0` triggers early exit!).

\* \*\*Selection Sort:\*\* Always scans the unsorted suffix to find the minimum (`5 + 4 + 3 + 2 + 1 = 15` comparisons) and performs at most $n - 1 = 5$ swaps.

\* \*\*Insertion Sort:\*\* Inserts each element into the sorted left prefix: `102` (1 shift), `108` (0 shifts), `101` (3 shifts), `104` (2 shifts), `103` (3 shifts) $\\rightarrow$ \*\*9 shifts total\*\*.

\* \*\*Why Insertion Sort Excels on Nearly Sorted Data:\*\* Each element moves only a few positions left until hitting a smaller key (`a\[j] <= key`), terminating the inner `while` loop immediately in $O(1)$ per element ($O(n + d)$ total where $d$ is the number of inversions).

\* \*\*Stability:\*\* \*\*Bubble Sort\*\* and \*\*Insertion Sort\*\* are \*\*stable\*\* (strict `>` comparison never swaps equal keys), whereas \*\*Selection Sort\*\* is \*\*unstable\*\* (long-distance swaps can reorder equal keys). Stability ensures students with equal marks retain their original register-number order.



\## 2. Student B: Comparative Measurements (`N = 10,000`)



| Input Order | Bubble (Comps / Swaps) | Selection (Comps / Swaps) | Insertion (Comps / Shifts) | Best Choice |

| :--- | :--- | :--- | :--- | :--- |

| \*\*Sorted\*\* | `9,999 / 0` | `49,995,000 / 0` | `9,999 / 0` | \*\*Insertion / Bubble\*\* ($O(n)$) |

| \*\*Nearly Sorted\*\* | `\~39,990 / \~60` | `49,995,000 / \~35` | `\~10,058 / \~60` | \*\*Insertion Sort\*\* |

| \*\*Reverse\*\* | `49,995,000 / 49,995,000` | `49,995,000 / 5,000` | `49,995,000 / 49,995,000` | \*\*Selection Sort\*\* (fewest writes) |

| \*\*Random\*\* | `\~49,990,000 / \~25,000,000` | `49,995,000 / \~9,990` | `\~25,000,000 / \~25,000,000` | \*\*Insertion Sort\*\* (half the comps) |



\## 3. Joint Conclusion \& Alternative Concept (Counting Sort)

\* \*\*Recommendation for 20 Late Registrations:\*\* \*\*Insertion Sort\*\* — it is stable, in-place ($O(1)$ space), and completes in \*\*$O(n)$\*\* time (\~$n + 20d$ operations), beating Bubble Sort by avoiding full backward sweeps across already-sorted prefixes.

\* \*\*Alternative Concept (Counting Sort):\*\* Uses an auxiliary frequency array of size $k$ (range of register numbers) to sort in \*\*$O(n + k)$\*\* time and \*\*$O(k)$\*\* extra space. It is unsuitable when register numbers are sparse 10-digit IDs (e.g., `1972260036`, where $k \\approx 10^{10}$ would exhaust RAM).



