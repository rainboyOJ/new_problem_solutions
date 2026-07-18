import sys

def main():
    read = sys.stdin.buffer.readline
    n, m = map(int, read().split())
    reverse_graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = map(int, read().split())
        reverse_graph[v].append(u)

    answer = [0] * (n + 1)
    for largest in range(n, 0, -1):
        if answer[largest]:
            continue
        answer[largest] = largest
        stack = [largest]
        while stack:
            node = stack.pop()
            for previous in reverse_graph[node]:
                if not answer[previous]:
                    answer[previous] = largest
                    stack.append(previous)

    print(*answer[1:])

if __name__ == "__main__":
    main()
