import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    cow_count, n, m = data[:3]
    starts = data[3:3 + cow_count]
    graph = [[] for _ in range(n + 1)]
    pos = 3 + cow_count
    for _ in range(m):
        u, v = data[pos], data[pos + 1]
        pos += 2
        graph[u].append(v)

    reachable_count = [0] * (n + 1)
    for start in starts:
        visited = bytearray(n + 1)
        visited[start] = 1
        stack = [start]
        while stack:
            node = stack.pop()
            reachable_count[node] += 1
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = 1
                    stack.append(neighbor)

    print(reachable_count.count(cow_count))

if __name__ == "__main__":
    main()
