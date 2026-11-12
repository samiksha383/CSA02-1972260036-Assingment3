\# Q4 – Two-Dimensional Arrays: District Rainfall Records



\## 1. Student A: Memory Layout, Address Formula \& 3-D Extension

\* \*\*Row-Major Storage:\*\* C stores `double rain\[38]\[12]` as a single contiguous block of `38 × 12 = 456` elements (`3,648 bytes`). All 12 months of District 0 (`rain\[0]\[0..11]`) appear first in memory, immediately followed by District 1 (`rain\[1]\[0..11]`), and so on.

\* \*\*Address Formula for `rain\[i]\[j]`:\*\*

&#x20; $$\\text{Address}(\\text{rain}\[i]\[j]) = \\text{Base\\\_Address} + (i \\times 12 + j) \\times \\text{sizeof(double)}$$

\* \*\*Why Loop Order Affects Speed:\*\* Modern CPUs fetch memory in \*\*64-byte cache lines\*\* (holding 8 `double` values at once). A \*\*row-wise\*\* loop (`i` outer, `j` inner) accesses adjacent addresses sequentially, achieving nearly 100% spatial cache hits. A \*\*column-wise\*\* loop (`j` outer, `i` inner) jumps by `N × 8 bytes` (`16,000 bytes` per step for `N = 2000`), causing repeated CPU cache misses.

\* \*\*3-D Array Extension (`rain\[years]\[38]\[12]`):\*\*

&#x20; $$\\text{Address}(\\text{rain}\[y]\[i]\[j]) = \\text{Base} + \\big((y \\times 38 + i) \\times 12 + j\\big) \\times \\text{sizeof(double)}$$



\## 2. Student B: Hand Verification \& Benchmark Results

\* \*\*Hand-Verified `3 × 4` Matrix:\*\*

&#x20; \* District 1 Total: `100 + 200 + 300 + 400 = 1000.00 mm`

&#x20; \* District 2 Total: `150 + 250 + 350 + 450 = 1200.00 mm`

&#x20; \* District 3 Total: `50 + 50 + 100 + 100 = 300.00 mm`

&#x20; \* Monthly Averages: `M1 = 100.00`, `M2 = 166.67`, `M3 = 233.33`, `M4 = 316.67`

&#x20; \* Wettest Record: \*\*District 2, Month 4 (`450.00 mm`)\*\*

&#x20; \* State Annual Average: `(1000 + 1200 + 300) / 3 = 833.33 mm`; 60% threshold = `500.00 mm` $\\rightarrow$ \*\*District 3 (`300.00 mm`)\*\* is flagged as deficient.

\* \*\*2,000 × 2,000 Traversal Measurement:\*\* Column-wise traversal takes significantly longer (\*\*\~3× to 6× slower\*\*) than row-wise traversal because every iteration evicts cache lines before the remaining 7 elements in that cache line are read.



\## 3. Joint Conclusion \& Alternative Concept Analysis

\* \*\*Why `rain\[38]\[12]` Beats 38 Separate 1-D Arrays:\*\* A 2-D array enables parameterized loops over district index `i` and contiguous cache storage, whereas 38 separate variables (`d1\[], d2\[], ...`) require 38 duplicated code blocks and cannot be indexed dynamically.



\### Alternative Concept Comparison



| Representation | Access Time | Extra Space | Memory Layout \& Speed Impact |

| :--- | :--- | :--- | :--- |

| \*\*2-D Array `rain\[38]\[12]`\*\* | \*\*$O(1)$\*\* | \*\*0 bytes\*\* | Single contiguous block (`3,648 B`); fastest cache locality. |

| \*\*Flattened 1-D `rain\[i \* 12 + j]`\*\* | \*\*$O(1)$\*\* | \*\*0 bytes\*\* | Identical contiguous memory and speed; manual index arithmetic. |

| \*\*Array of 38 Row Pointers (`double \*rain\[38]`)\*\* | \*\*$O(1)$\*\* | \*\*`38 × 8 = 304 bytes`\*\* (plus heap headers) | Requires two memory reads (pointer dereference + element) and non-contiguous heap rows, reducing cache locality. |



