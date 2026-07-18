import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    n, m, q = data[:3]
    parent = list(range(n + 1))
    size = [1] * (n + 1)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a, b = find(a), find(b)
        if a == b:
            return
        if size[a] < size[b]:
            a, b = b, a
        parent[b] = a
        size[a] += size[b]

    pos = 3
    for _ in range(m):
        union(data[pos], data[pos + 1])
        pos += 2

    answer = []
    for _ in range(q):
        answer.append("Yes" if find(data[pos]) == find(data[pos + 1]) else "No")
        pos += 2
    print("\n".join(answer))

if __name__ == "__main__":
    main()
