import sys
from collections import deque


MOD = 80112002


def main():
    read = sys.stdin.buffer.readline
    n, m = map(int, read().split())
    graph = [[] for _ in range(n + 1)]
    indegree = [0] * (n + 1)

    for _ in range(m):
        prey, predator = map(int, read().split())
        graph[prey].append(predator)
        indegree[predator] += 1

    queue = deque(node for node in range(1, n + 1) if indegree[node] == 0)
    ways = [0] * (n + 1)
    for source in queue:
        ways[source] = 1

    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            ways[neighbor] = (ways[neighbor] + ways[node]) % MOD
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    print(sum(ways[node] for node in range(1, n + 1) if not graph[node]) % MOD)


if __name__ == "__main__":
    main()
