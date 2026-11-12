\# Q5 – Processing Text Without the Library



\## 1. Student A: Character-Level Design

\* \*\*Role of `'\\0'` (Null Terminator):\*\* C strings have no hidden length header; functions scan sequential bytes until encountering `'\\0'` (`0x00`). Omitting `'\\0'` causes out-of-bounds memory reads.

\* \*\*Pseudocode for Multi-Space Word Counting:\*\*

&#x20; ```text

&#x20; WORD\_COUNT(s):

&#x20;     count <- 0, inside <- FALSE

&#x20;     for i <- 0 while s\[i] != '\\0':

&#x20;         if s\[i] is whitespace (' ', '\\t', '\\n'):

&#x20;             inside <- FALSE

&#x20;         else if not inside:

&#x20;             inside <- TRUE

&#x20;             count <- count + 1

&#x20;     return count

&#x20; ```

\* \*\*Why String Length Should Not Be Recomputed in Every Iteration:\*\* Calling `strlen(s)` inside `for (i = 0; i < strlen(s); i++)` rescans the string from index `0` on every iteration, turning an \*\*$O(n)$\*\* loop into \*\*$O(n^2)$\*\* time.

\* \*\*`char s\[] = "OK"` vs. `char \*s = "OK"`:\*\* `char s\[]` allocates a writable 3-byte array (`{'O','K','\\0'}`) on the stack. `char \*s` points to a string literal in read-only memory (`.rodata`), where modifying `s\[0]` causes a segmentation fault (Undefined Behaviour).

\* \*\*Tab Character Test (`"Meet\\tat\\t5 PM"`):\*\* When treating both `' '` and `'\\t'` as delimiters, `word\_count` returns \*\*4 words\*\* (`Meet`, `at`, `5`, `PM`). If only `' '` were checked, `'\\t'` would be treated as part of a single giant token and falsely return `2` words.



\## 2. Student B: Library Functions \& Safety

\* \*\*Buffer Overflow with `strcpy`:\*\* Copying a 50-character SMS into `char small\[10]` via `strcpy(small, long\_sms)` overwrites adjacent stack memory, corrupting local variables or return addresses.

\* \*\*Safe Replacements:\*\* Use `fgets(buf, sizeof(buf), stdin)` for input and `snprintf(dst, sizeof(dst), "%s", src)` (or `strncpy` with explicit `dst\[sizeof(dst)-1] = '\\0'`) for copying.

\* \*\*Why `gets()` Was Removed in C11:\*\* `gets(buf)` takes no buffer size parameter, making it impossible to prevent stack buffer overflows on arbitrary input.



\## 3. Joint Conclusion \& Alternative Complexity

\* \*\*When to Write Custom vs. `string.h`:\*\* Rely on `string.h` (`strlen`, `strcmp`, `memcpy`) for standard operations because standard libraries use vectorized SIMD instructions. Write custom single-pass loops when combining domain rules (like palindrome filtering with `isalpha`/`tolower`) in one scan.

\* \*\*Complexity Comparison:\*\*

&#x20; \* Single-pass loop: \*\*$O(n)$\*\* time, \*\*$O(1)$\*\* space.

&#x20; \* `strlen(s)` in loop condition: \*\*$O(n^2)$\*\* time, \*\*$O(1)$\*\* space.

&#x20; \* Recursive string reversal: \*\*$O(n)$\*\* time, \*\*$O(n)$\*\* call-stack space ($n/2$ stack frames).



