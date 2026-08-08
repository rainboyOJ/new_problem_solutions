import sys


input = sys.stdin.buffer.readline
n, limit = map(int, input().split())
graph = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    u, v, weight = map(int, input().split())
    graph[u].append((v, weight))
    graph[v].append((u, weight))


def farthest(start):
    parent = [0] * (n + 1)
    distance = [0] * (n + 1)
    order = [start]
    for node in order:
        for neighbor, weight in graph[node]:
            if neighbor != parent[node]:
                parent[neighbor] = node
                distance[neighbor] = distance[node] + weight
                order.append(neighbor)
    end = max(order, key=distance.__getitem__)
    return end, parent, distance


diameter_start, _, _ = farthest(1)
diameter_end, parent, distance = farthest(diameter_start)
diameter = []
node = diameter_end
while node:
    diameter.append(node)
    if node == diameter_start:
        break
    node = parent[node]
diameter.reverse()
position = {node: index for index, node in enumerate(diameter)}
coordinate = [distance[node] for node in diameter]

branch_maximum = 0
for root in diameter:
    stack = [(root, 0, 0)]
    while stack:
        node, previous, branch_distance = stack.pop()
        branch_maximum = max(branch_maximum, branch_distance)
        for neighbor, weight in graph[node]:
            if neighbor != previous and neighbor not in position:
                stack.append((neighbor, node, branch_distance + weight))

diameter_length = coordinate[-1]
answer = diameter_length
right = 0
for left in range(len(diameter)):
    right = max(right, left)
    while right + 1 < len(diameter) and coordinate[right + 1] - coordinate[left] <= limit:
        right += 1
    answer = min(answer, max(coordinate[left], diameter_length - coordinate[right], branch_maximum))
print(answer)
