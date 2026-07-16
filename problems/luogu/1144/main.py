import sys
from array import array


input = sys.stdin.buffer.readline
n, edges = map(int, input().split())
head = array("i", [-1]) * (n + 1)
to = array("i", [0]) * (2 * edges)
next_edge = array("i", [0]) * (2 * edges)
edge_count = 0


def add_edge(u, v):
    global edge_count
    to[edge_count] = v
    next_edge[edge_count] = head[u]
    head[u] = edge_count
    edge_count += 1


for _ in range(edges):
    u, v = map(int, input().split())
    add_edge(u, v)
    add_edge(v, u)

distance = array("i", [-1]) * (n + 1)
ways = array("i", [0]) * (n + 1)
distance[1] = 0
ways[1] = 1
queue = array("i", [1])
index = 0
while index < len(queue):
    node = queue[index]
    index += 1
    edge = head[node]
    while edge != -1:
        neighbor = to[edge]
        if distance[neighbor] == -1:
            distance[neighbor] = distance[node] + 1
            queue.append(neighbor)
        if distance[neighbor] == distance[node] + 1:
            ways[neighbor] = (ways[neighbor] + ways[node]) % 100003
        edge = next_edge[edge]
output = sys.stdout.write
buffer = []
for node in range(1, n + 1):
    buffer.append(str(ways[node]))
    if len(buffer) == 8192:
        output("\n".join(buffer) + "\n")
        buffer.clear()
output("\n".join(buffer))
