import sys
from collections import deque


input = sys.stdin.buffer.readline
n, constraints = map(int, input().split())
graph = [[] for _ in range(n + 1)]
reverse_graph = [[] for _ in range(n + 1)]
edges = []


def add_edge(u, v, weight):
    graph[u].append(v)
    reverse_graph[v].append(u)
    edges.append((u, v, weight))


possible = True
for _ in range(constraints):
    kind, a, b = map(int, input().split())
    if kind == 1:
        add_edge(a, b, 0)
        add_edge(b, a, 0)
    elif kind == 2:
        possible &= a != b
        add_edge(a, b, 1)
    elif kind == 3:
        add_edge(b, a, 0)
    elif kind == 4:
        possible &= a != b
        add_edge(b, a, 1)
    else:
        add_edge(a, b, 0)

if possible:
    visited = bytearray(n + 1)
    finish = []
    for start in range(1, n + 1):
        if visited[start]:
            continue
        visited[start] = 1
        stack = [(start, 0)]
        while stack:
            node, index = stack[-1]
            if index < len(graph[node]):
                neighbor = graph[node][index]
                stack[-1] = node, index + 1
                if not visited[neighbor]:
                    visited[neighbor] = 1
                    stack.append((neighbor, 0))
            else:
                finish.append(node)
                stack.pop()
    component = [0] * (n + 1)
    component_count = 0
    for start in reversed(finish):
        if component[start]:
            continue
        component_count += 1
        component[start] = component_count
        stack = [start]
        while stack:
            node = stack.pop()
            for neighbor in reverse_graph[node]:
                if component[neighbor] == 0:
                    component[neighbor] = component_count
                    stack.append(neighbor)
    size = [0] * (component_count + 1)
    dag = [[] for _ in range(component_count + 1)]
    indegree = [0] * (component_count + 1)
    for node in range(1, n + 1):
        size[component[node]] += 1
    for u, v, weight in edges:
        first, second = component[u], component[v]
        if first == second:
            if weight:
                possible = False
                break
        else:
            dag[first].append((second, weight))
            indegree[second] += 1

if not possible:
    print(-1)
else:
    value = [1] * (component_count + 1)
    queue = deque(node for node in range(1, component_count + 1) if indegree[node] == 0)
    while queue:
        node = queue.popleft()
        for neighbor, weight in dag[node]:
            value[neighbor] = max(value[neighbor], value[node] + weight)
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)
    print(sum(value[node] * size[node] for node in range(1, component_count + 1)))
