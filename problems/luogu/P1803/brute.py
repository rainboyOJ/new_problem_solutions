from itertools import combinations
import sys


def greedy(matches):
    answer = 0
    last_end = 0
    for start, end in sorted(matches, key=lambda x: x[1]):
        if start >= last_end:
            answer += 1
            last_end = end
    return answer


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
matches = [(data[i], data[i + 1]) for i in range(1, len(data), 2)]

if n > 22:
    print(greedy(matches))
else:
    answer = 0
    for size in range(n + 1):
        for chosen in combinations(matches, size):
            ordered = sorted(chosen, key=lambda x: x[1])
            ok = all(ordered[i][1] <= ordered[i + 1][0] for i in range(len(ordered) - 1))
            if ok:
                answer = max(answer, size)
    print(answer)
