\# Q6 – A Directory of Names: Sorting and Searching Strings



\## 1. Student A: Measured `strcmp` Calls \& Character Copies



| Directory Size ($N$) | `strcmp` Calls (Avg Insertion) | `strcpy` Character Copies (2D Array) | Index Sort Character Copies |

| :--- | :--- | :--- | :--- |

| `100` | `\~2,500` | `\~65,000 bytes` | \*\*0 bytes\*\* |

| `500` | `\~62,500` | `\~1,625,000 bytes` | \*\*0 bytes\*\* |

| `5,000` | `\~6,250,000` | `\~162,500,000 bytes` | \*\*0 bytes\*\* |



\* \*\*Length 29 vs. 30 in `char\[30]`:\*\* A 29-character name uses indices `0..28` plus `'\\0'` at index `29` (fits completely). A 30-character name leaves no room for `'\\0'`, so `fgets`/`snprintf` truncates the 30th character to preserve null termination.

\* \*\*Binary Search Comparisons:\*\* For $N = 6$, searching `"Kiran"` (present) takes \*\*1–2\*\* `strcmp` calls; searching `"Rahul"` (missing) takes \*\*3\*\* `strcmp` calls ($\\lfloor\\log\_2 6\\rfloor + 1$).



\## 2. Student B: Design \& Correctness

\* \*\*Why `"Apple"` < `"apple"` in `strcmp`:\*\* `strcmp` compares unsigned ASCII values byte-by-byte. Uppercase `'A'` (`65`) is smaller than lowercase `'a'` (`97`), so `"Apple"` sorts before `"apple"`. Converting characters via `tolower()` provides case-insensitive ordering.

\* \*\*Cost of Swapping 2D Strings:\*\* Swapping two rows of `char\[30]` requires 3 `strcpy` calls copying up to \*\*90 bytes\*\*, whereas swapping two `int` indices moves \*\*8 bytes\*\* (two 4-byte integers).

\* \*\*Duplicate Detection:\*\* Because lexicographical order is transitive, identical names are guaranteed to become \*\*adjacent\*\* (`strcmp(names\[i], names\[i-1]) == 0`), allowing duplicate detection in a single \*\*$O(n)$\*\* pass.



\## 3. Joint Conclusion \& Alternative Concept (`char \*list\[500]` with `qsort`)

\* \*\*Trade-Off of Index/Pointer Sorting:\*\* Eliminates all multi-byte string copying during swaps, at the minor cost of $O(n)$ extra memory (`500 × 4 = 2,000 bytes` for `int idx\[500]`) and one extra pointer indirection per comparison.

\* \*\*Alternative Concept (`char \*list\[500]` + `qsort`):\*\* Performs \*\*$O(n \\log n)$\*\* comparisons (`\~4,500` for $n=500$), each comparing up to $L = 30$ characters ($O(L \\cdot n \\log n)$ worst case), with \*\*$O(1)$\*\* pointer swaps (`8 bytes` on 64-bit systems) and `500 × 8 = 4,000 bytes` of pointer array space.



