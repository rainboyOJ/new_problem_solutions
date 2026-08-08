n = int(input())
words = [input().strip() for _ in range(n)]
start = input().strip()
used = [0] * n


def overlap(left, right):
    return next(
        (
            length
            for length in range(1, min(len(left), len(right)))
            if left.endswith(right[:length])
        ),
        0,
    )


overlaps = [[overlap(left, right) for right in words] for left in words]


def dfs(last, length):
    best = length
    for nxt, shared in enumerate(overlaps[last]):
        if not shared or used[nxt] == 2:
            continue
        used[nxt] += 1
        best = max(best, dfs(nxt, length + len(words[nxt]) - shared))
        used[nxt] -= 1
    return best


answer = 0
for index, word in enumerate(words):
    if word.startswith(start):
        used[index] = 1
        answer = max(answer, dfs(index, len(word)))
        used[index] = 0

print(answer)
