import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[:2]
    edges = sorted(zip(data[2::3], data[3::3], data[4::3]), key=lambda edge: -edge[2])

    parent = list(range(2 * n + 1))
    size = [1] * (2 * n + 1)

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

    for u, v, weight in edges:
        if find(u) == find(v):
            print(weight)
            return
        union(u, v + n)
        union(u + n, v)

    print(0)


if __name__ == "__main__":
    main()
