# Luogu 7910 Ordered Array Alternative Design

## Goal

Add a second accepted solution for Luogu P7910 that uses an ordinary sorted array and binary search. Present this new solution as the primary teaching approach in `index.md`, while retaining the existing rank-array `main.cpp` as a secondary approach.

## Scope

Create or modify only:

- `problems/luogu/7910/main2.cpp`
- `problems/luogu/7910/index.md`

Do not modify `main.cpp`, `brute.cpp`, `gen.py`, image files, relation metadata, or unrelated problems. Keep the obsolete one-page image unreferenced because it describes the former `vector` implementation.

## Shared Ordering Model

The insertion sort in the statement swaps only when the right value is strictly smaller, so it is stable. Represent the element at original index `i` by the unique key:

```text
(a[i], i)
```

Sort keys first by value and then by original index. Query `2 x` asks for the position of `(a[x], x)` in this order.

Both solutions in the article share this model. The article should explain it once before separating the approaches.

## `main2.cpp` Data Structures

Use fixed-size ordinary arrays:

```text
a[i]    current value at original index i
ord[p]  the (value, original index) key currently at sorted position p
```

Use a simple `Node` struct with `value` and `id` fields. Do not use `vector`, lambda expressions, or another dynamic container.

## Initialization

1. Read `a[i]`.
2. Store `(a[i], i)` in `ord[i]`.
3. Run `std::sort(ord + 1, ord + n + 1)` with a normal comparator function.

Initialization costs `O(n log n)`. Do not use literal insertion sort for initialization because that would add an unnecessary `O(n^2)` term.

## Binary Search

Implement a normal function that returns the first position whose key is not less than the target key.

For an ordered range of length `len`, the return value is in `1..len+1`:

- `1..len` when the target belongs before or at a current key;
- `len+1` when the target belongs after every current key.

Because `(value, original index)` is unique, querying an existing element always finds exactly one position.

## Query Operation

For operation `2 x`:

1. Build target `(a[x], x)`.
2. Binary-search it in `ord[1..n]`.
3. Output the returned position.

One query costs `O(log n)`.

## Modification Operation

For operation `1 x v`:

1. Binary-search old key `(a[x], x)` in `ord[1..n]`.
2. Shift subsequent elements one position left to remove it. The valid ordered range now has length `n-1`.
3. Set `a[x] = v` and build new key `(v, x)`.
4. Binary-search the insertion position in `ord[1..n-1]`.
5. Shift elements from the end toward the insertion position one place right.
6. Write the new key into the empty position.

Binary search costs `O(log n)`, but array movement costs `O(n)`, so one modification is `O(n)`.

## Complexity

Let `M` be the number of type-1 modifications, with `M <= 5000`.

### Ordered-array solution (`main2.cpp`)

- Initialization: `O(n log n)`
- Each modification: `O(n)`
- Each query: `O(log n)`
- Total: `O(n log n + Mn + Q log n)`
- Space: `O(n)`

### Rank-array solution (`main.cpp`)

- Initialization: `O(n log n)`
- Each modification: `O(n)`
- Each query: `O(1)`
- Total: `O(n log n + Mn + Q)`
- Space: `O(n)`

Do not describe the ordered-array solution as only `O(Q log n)`, because modifications still shift up to `O(n)` elements.

## Article Organization

Keep the current problem statement and shared stable-order observation.

Within `### 思路`, organize the optimized solutions as:

1. `#### 方案二：维护有序数组 + 二分` as the primary, detailed explanation.
2. `#### 方案一：直接维护排名数组` as the secondary explanation, preserving the existing removal-and-reinsertion rank logic in a more compact form.

Within `### 代码`:

1. Introduce and include `main2.cpp` first.
2. Introduce and include `main.cpp` second.

Within `### 复杂度`, give separate formulas for the two solutions. Update frontmatter `description` and `### 总结` so the ordered-array approach is the main teaching signal while the rank-array approach remains visible.

Do not restore the one-page image reference because its source material names `vector`, `erase`, and the old complexity.

## Edge Cases

- Equal values are ordered by original index.
- Updating an element to its current value removes and reinserts it at the same logical position.
- Insertion before the first key and after the last key shifts the correct range.
- Removing the first or last key does not read outside `ord[1..n]`.
- `n = 1` always produces rank `1`.

## Verification

1. Compile `main2.cpp` as C++17 with warnings enabled.
2. Run repository samples using `main2.cpp`.
3. Run manual tests for equal values, unchanged updates, and first/last insertion positions.
4. Differential-test `main2.cpp` against `brute.cpp` with `gen.py` for at least 500 random cases.
5. Run `check_problem.py` and `check_relations.py`.
6. Confirm `main2.cpp` contains no `vector` and `index.md` correctly references both code files.
