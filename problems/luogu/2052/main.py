import sys
from array import array


input = sys.stdin.buffer.readline
n = int(input())
head = array("i", [-1]) * (n + 1)
to = array("i", [0]) * (2 * n - 2)
next_edge = array("i", [0]) * (2 * n - 2)
weight = array("q", [0]) * (2 * n - 2)
edge_count = 0


def add_edge(u, v, length):
    global edge_count
    to[edge_count] = v
    weight[edge_count] = length
    next_edge[edge_count] = head[u]
    head[u] = edge_count
    edge_count += 1


for _ in range(n - 1):
    u, v, length = map(int, input().split())
    add_edge(u, v, length)
    add_edge(v, u, length)

parent = array("i", [0]) * (n + 1)
parent_weight = array("q", [0]) * (n + 1)
order = array("i", [1])
index = 0
while index < n:
    node = order[index]
    index += 1
    edge = head[node]
    while edge != -1:
        neighbor = to[edge]
        if neighbor != parent[node]:
            parent[neighbor] = node
            parent_weight[neighbor] = weight[edge]
            order.append(neighbor)
        edge = next_edge[edge]

subtree = array("q", [1]) * (n + 1)
answer = 0
for node in reversed(order[1:]):
    subtree[parent[node]] += subtree[node]
for node in range(2, n + 1):
    answer += parent_weight[node] * abs(n - 2 * subtree[node])
print(answer)
