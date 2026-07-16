import sys
from collections import deque


def main():
    read = sys.stdin.buffer.readline
    n, m = map(int, read().split())
    graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = map(int, read().split())
        graph[u].append(v)
    for neighbors in graph:
        neighbors.sort()

    visited = bytearray(n + 1)
    dfs_order = []
    stack = [1]
    while stack:
        node = stack.pop()
        if visited[node]:
            continue
        visited[node] = 1
        dfs_order.append(node)
        stack.extend(reversed(graph[node]))

    visited = bytearray(n + 1)
    visited[1] = 1
    bfs_order = []
    queue = deque([1])
    while queue:
        node = queue.popleft()
        bfs_order.append(node)
        for neighbor in graph[node]:
            if not visited[neighbor]:
                visited[neighbor] = 1
                queue.append(neighbor)

    print(*dfs_order)
    print(*bfs_order)


if __name__ == "__main__":
    main()
