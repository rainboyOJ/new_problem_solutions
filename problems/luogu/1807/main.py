import sys


def main():
    read = sys.stdin.buffer.readline
    n, m = map(int, read().split())
    graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, weight = map(int, read().split())
        graph[u].append((v, weight))

    distance = [None] * (n + 1)
    distance[1] = 0
    for node in range(1, n + 1):
        if distance[node] is None:
            continue
        for neighbor, weight in graph[node]:
            candidate = distance[node] + weight
            if distance[neighbor] is None or candidate > distance[neighbor]:
                distance[neighbor] = candidate

    print(-1 if distance[n] is None else distance[n])


if __name__ == "__main__":
    main()
