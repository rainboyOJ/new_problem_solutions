# Luogu 7910 Array Rank Solution Design

## Goal

Replace the current `vector`-based ordered-table solution for Luogu P7910 with an ordinary-array implementation that maintains each original element's current stable-sort rank.

The final solution should make queries constant-time and use the problem's limit of at most 5000 modifications to allow linear work per modification.

## Scope

Change only:

- `problems/luogu/7910/main.cpp`
- `problems/luogu/7910/index.md`

Keep `brute.cpp`, `gen.py`, images, relation metadata, and unrelated problem files unchanged.

## Ordering Model

The insertion sort in the statement swaps only when the right value is strictly smaller. It is therefore stable.

Represent the element at original index `i` by the unique key:

```text
(a[i], i)
```

Keys are ordered first by value and then by original index. The answer to query `2 x` is the rank of key `(a[x], x)` among all current keys.

## Data Structures

Use only fixed-size ordinary arrays and a simple struct:

```text
a[i]       current value at original index i
rank_pos[i] current stable-sort rank of element i
nodes[i]   temporary (value, original index) records for initialization
```

`n <= 8000`, so arrays of size `8005` are sufficient. Do not use `vector` or another dynamic container. `std::sort` over the `nodes` array is allowed.

## Initialization

1. Read every `a[i]` and create `nodes[i] = (a[i], i)`.
2. Sort `nodes[1..n]` by value, then original index.
3. For every sorted position `p`, set `rank_pos[nodes[p].id] = p`.

Initialization costs `O(n log n)`.

## Modification

For operation `1 x v`, remove the old key from the conceptual ranking and insert the new key without maintaining a separate ordered sequence.

### Remove the old key

Store `old_rank = rank_pos[x]`. For every `i != x` whose rank is greater than `old_rank`, decrement `rank_pos[i]` by one. The remaining elements now occupy ranks `1..n-1`.

### Insert the new key

Set `a[x] = v` and start `rank_pos[x] = 1`.

For every `i != x`:

- if `(a[i], i) < (a[x], x)`, increment `rank_pos[x]`;
- otherwise, increment `rank_pos[i]`, because the new key is inserted before that element.

All keys are unique because the original index is part of the key, so exactly one of these two cases holds.

One modification costs `O(n)`.

## Query

For operation `2 x`, output `rank_pos[x]` directly.

One query costs `O(1)`.

## Complexity

Let `M` be the number of type-1 modifications. The statement guarantees `M <= 5000`.

- Initialization: `O(n log n)`
- All modifications: `O(Mn)`
- All operations and output handling: `O(Q)`
- Total: `O(n log n + Mn + Q)`
- Space: `O(n)`

Do not describe the final complexity as only `O(Q log n)`. The chosen solution deliberately trades `O(n)` modification time for `O(1)` query time because modifications are limited.

## Article Changes

Preserve the current explanation of insertion-sort stability and the `(value, original index)` key.

Replace the ordered-`vector` discussion with:

1. the meaning of `rank_pos[i]`;
2. initialization by sorting an ordinary `Node` array;
3. removal of the old rank during a modification;
4. insertion of the new key by comparing it with every other key;
5. direct `O(1)` rank queries.

Update the complexity section to `O(n log n + Mn + Q)` time and `O(n)` space. Keep the existing brute-force include, final-code include, summary, and one-page image.

## Edge Cases

- Equal values must remain ordered by original index.
- Assigning an element its current value must leave every final rank unchanged.
- Updating the first- or last-ranked element must correctly close and reopen the rank interval.
- `n = 1` must always answer rank `1`.
- All values equal must produce ranks equal to original indices.

## Verification

1. Compile `main.cpp` as C++17.
2. Run the repository sample checker.
3. Run random differential testing against the existing `brute.cpp` and `gen.py` for at least 200 cases.
4. Run `check_problem.py` after updating the article.
5. Confirm `main.cpp` contains no `vector` and the article no longer recommends `vector`, `erase`, or `insert`.
