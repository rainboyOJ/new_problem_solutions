import sys


input = sys.stdin.buffer.readline
n = int(input())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

parent = [0] * (n + 1)
depth = [0] * (n + 1)
order = [1]
for node in order:
    for neighbor in graph[node]:
        if neighbor != parent[node]:
            parent[neighbor] = node
            depth[neighbor] = depth[node] + 1
            order.append(neighbor)

subtree_size = [1] * (n + 1)
for node in reversed(order[1:]):
    subtree_size[parent[node]] += subtree_size[node]

distance_sum = [0] * (n + 1)
distance_sum[1] = sum(depth)
for node in order[1:]:
    distance_sum[node] = distance_sum[parent[node]] + n - 2 * subtree_size[node]
answer = min(range(1, n + 1), key=lambda node: (distance_sum[node], node))
print(answer, distance_sum[answer])
