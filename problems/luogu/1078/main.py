import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, culture_count, edge_count, start, target = (next(data), next(data), next(data),
                                                next(data) - 1, next(data) - 1)
culture = [next(data) - 1 for _ in range(n)]
rejected = [0] * culture_count
for i in range(culture_count):
    for j in range(culture_count):
        if next(data):
            rejected[i] |= 1 << j
graph = [[] for _ in range(n)]
for _ in range(edge_count):
    u, v, weight = next(data) - 1, next(data) - 1, next(data)
    graph[u].append((v, weight))
    graph[v].append((u, weight))

best = [[] for _ in range(n)]


def add_state(node, mask, distance):
    if any(old_distance <= distance and old_mask & mask == old_mask
           for old_mask, old_distance in best[node]):
        return False
    best[node] = [(old_mask, old_distance) for old_mask, old_distance in best[node]
                  if not (distance <= old_distance and mask & old_mask == mask)]
    best[node].append((mask, distance))
    return True


start_mask = 1 << culture[start]
add_state(start, start_mask, 0)
heap = [(0, start, start_mask)]
answer = -1

while heap:
    distance, node, mask = heapq.heappop(heap)
    if (mask, distance) not in best[node]:
        continue
    if node == target:
        answer = distance
        break
    for neighbor, weight in graph[node]:
        next_culture = culture[neighbor]
        bit = 1 << next_culture
        if mask & bit or rejected[next_culture] & mask:
            continue
        next_mask = mask | bit
        next_distance = distance + weight
        if add_state(neighbor, next_mask, next_distance):
            heapq.heappush(heap, (next_distance, neighbor, next_mask))

print(answer)
