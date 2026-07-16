import sys
from collections import deque


def main():
    read = sys.stdin.buffer.readline
    n, train_count = map(int, read().split())
    total_nodes = n + train_count
    graph = [[] for _ in range(total_nodes)]
    indegree = [0] * total_nodes

    for train in range(train_count):
        row = list(map(int, read().split()))
        stops = [station - 1 for station in row[1:]]
        stop_set = set(stops)
        virtual = n + train

        for station in range(stops[0], stops[-1] + 1):
            if station not in stop_set:
                graph[station].append(virtual << 1)
                indegree[virtual] += 1
        for station in stops:
            graph[virtual].append((station << 1) | 1)
            indegree[station] += 1

    level = [1] * n + [0] * train_count
    queue = deque(node for node in range(total_nodes) if indegree[node] == 0)
    while queue:
        node = queue.popleft()
        for edge in graph[node]:
            neighbor, weight = edge >> 1, edge & 1
            level[neighbor] = max(level[neighbor], level[node] + weight)
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    print(max(level[:n]))


if __name__ == "__main__":
    main()
