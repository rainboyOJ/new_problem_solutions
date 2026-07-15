from collections import defaultdict
import heapq
import sys


def greedy(abilities):
    chains = defaultdict(list)
    for x in sorted(abilities):
        length = heapq.heappop(chains[x - 1]) + 1 if chains[x - 1] else 1
        heapq.heappush(chains[x], length)
    return min(length for heap in chains.values() for length in heap)


def valid(group):
    return len(group) == len(set(group)) and max(group) - min(group) + 1 == len(group)


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
abilities = data[1:1 + n]

if n > 10:
    print(greedy(abilities))
else:
    groups = []
    answer = 0

    def dfs(index):
        global answer
        if index == n:
            if all(valid(group) for group in groups):
                answer = max(answer, min(map(len, groups)))
            return

        x = abilities[index]
        for group in groups:
            if x in group:
                continue
            group.append(x)
            dfs(index + 1)
            group.pop()

        groups.append([x])
        dfs(index + 1)
        groups.pop()

    dfs(0)
    print(answer)
