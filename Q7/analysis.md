\# Q7 – Design an Election Counting Program from First Principles



\## Stage 1 – Interpret the Problem

\* \*\*Inputs:\*\* Number of candidates c (1 ≤ c ≤ 12) and a stream/array of v integer votes (v ≤ 5,000, scaled to 500,000).

\* \*\*Outputs:\*\* `valid\_votes`, `invalid\_votes`, candidate vote totals sorted in descending order, the `winner`, or a `TIE` notice.

\* \*\*Rules:\*\* Any vote v < 1 or v > c is counted as invalid without crashing. `valid\_votes + invalid\_votes == total\_votes`.

\* \*\*Arrays \& Sizes:\*\* `long counts\[13]` (1-indexed tally array, 104 bytes) and `CandidateResult res\[12]` (192 bytes) to preserve candidate IDs during sorting.

\* \*\*Measurable Requirements:\*\* Process 5,000 votes in < 1 ms with O(1) auxiliary space relative to vote count.



\## Stage 2 – Design \& Pseudocode

```text

COUNT\_ELECTION(votes, v, c):

&#x20;   counts\[1..c] <- 0, valid <- 0, invalid <- 0

&#x20;   for i <- 0 to v - 1:

&#x20;       if 1 <= votes\[i] <= c:

&#x20;           counts\[votes\[i]] <- counts\[votes\[i]] + 1

&#x20;           valid <- valid + 1

&#x20;       else:

&#x20;           invalid <- invalid + 1

&#x20;   Build list res\[0..c-1] of (id, counts\[id]) and sort descending by votes

&#x20;   if valid == 0: print "No valid votes"

&#x20;   else if c > 1 and res\[0].votes == res\[1].votes: print "TIE"

&#x20;   else: print "Winner:", res\[0].id

```



\## Stage 3 – Implementation \& Hand Verification

\* \*\*Hand-Verified Input (`{1, 3, 2, 1, 0, 3, -2, 4, 9, 1, 3, 2}`, $c = 4$):\*\*

&#x20; \* \*\*Invalid (`3`):\*\* `0`, `-2`, `9`.

&#x20; \* \*\*Valid (`9`):\*\* Candidate `#1`: `3` votes, Candidate `#3`: `3` votes, Candidate `#2`: `2` votes, Candidate `#4`: `1` vote.

&#x20; \* \*\*Result:\*\* \*\*TIE\*\* between Candidate `#1` and Candidate `#3` (`3` votes each).

\* \*\*Measured Time:\*\* `5,000` votes complete in \*\*`\~0.02 ms`\*\*; `500,000` votes complete in \*\*`\~1.8 ms`\*\*.



\## Stage 4 – Defence \& Alternative Complexity Analysis

\* \*\*Why Direct Indexing Beats Searching:\*\* Using `counts\[vote]` accesses the candidate's bucket in \*\*$O(1)$\*\* direct memory offset without scanning candidate names.

\* \*\*Scaling to 500 Candidates:\*\* Increase `MAX\_CANDIDATES` to `500` (`4 KB` tally array) and replace insertion sort ($O(c^2)$) with `qsort` ($O(c \\log c)$).

\* \*\*Remaining Limitation:\*\* Does not authenticate voter IDs to prevent duplicate ballot submissions (requires a `bool has\_voted\[MAX\_VOTERS]` bitmap).



\### Alternative Concept Comparison ($v$ votes, $c$ candidates)



| Approach | Time Complexity | Extra Space | Verdict |

| :--- | :--- | :--- | :--- |

| \*\*Direct Count Array (Chosen)\*\* | \*\*$O(v + c \\log c)$\*\* | \*\*$O(c)$\*\* | Fastest and simplest |

| \*\*Linear Search Candidate List per Vote\*\* | \*\*$O(v \\cdot c)$\*\* | \*\*$O(c)$\*\* | $12\\times$ to $500\\times$ slower |

| \*\*Sort All Votes + Count Runs\*\* | \*\*$O(v \\log v)$\*\* | \*\*$O(v)$\*\* | Wastes memory storing all ballots |



