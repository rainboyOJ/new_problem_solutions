import sys


INF = 10**18
data = iter(map(int, sys.stdin.buffer.read().split()))
n, edge_count = next(data), next(data)
edge = [[INF] * n for _ in range(n)]
for _ in range(edge_count):
    u, v, weight = next(data) - 1, next(data) - 1, next(data)
    edge[u][v] = edge[v][u] = min(edge[u][v], weight)

size = 1 << n
full = size - 1
connection = [[INF] * size for _ in range(n)]
for vertex in range(n):
    for mask in range(1, size):
        bit = mask & -mask
        other = bit.bit_length() - 1
        connection[vertex][mask] = min(connection[vertex][mask ^ bit], edge[vertex][other])

transitions = [[] for _ in range(size)]
for mask in range(1, size):
    remaining_vertices = [vertex for vertex in range(n) if not mask >> vertex & 1]

    def enumerate_additions(index, subset, cost):
        if index == len(remaining_vertices):
            if subset:
                transitions[mask].append((mask | subset, cost))
            return
        enumerate_additions(index + 1, subset, cost)
        vertex = remaining_vertices[index]
        weight = connection[vertex][mask]
        if weight < INF:
            enumerate_additions(index + 1, subset | 1 << vertex, cost + weight)

    enumerate_additions(0, 0, 0)

dp = [INF] * size
for root in range(n):
    dp[1 << root] = 0
for depth in range(1, n):
    next_dp = dp[:]
    for mask, base in enumerate(dp):
        if base == INF:
            continue
        for next_mask, cost in transitions[mask]:
            next_dp[next_mask] = min(next_dp[next_mask], base + depth * cost)
    dp = next_dp
print(dp[full])
