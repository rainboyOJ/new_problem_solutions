from functools import cache
import heapq
import sys


def huffman(a):
    heap = list(a)
    heapq.heapify(heap)
    answer = 0
    while len(heap) > 1:
        x = heapq.heappop(heap)
        y = heapq.heappop(heap)
        answer += x + y
        heapq.heappush(heap, x + y)
    return answer


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
weights = tuple(sorted(data[1:1 + n]))

if n > 9:
    print(huffman(weights))
else:
    @cache
    def dfs(state):
        if len(state) == 1:
            return 0
        best = 10**18
        state = list(state)
        for i in range(len(state)):
            for j in range(i + 1, len(state)):
                merged = state[i] + state[j]
                next_state = [state[k] for k in range(len(state)) if k not in (i, j)]
                next_state.append(merged)
                best = min(best, merged + dfs(tuple(sorted(next_state))))
        return best

    print(dfs(weights))
