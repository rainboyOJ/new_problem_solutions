import sys

def main():
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
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

    pos = 2
    for _ in range(m):
        relation = data[pos]
        a, b = int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        if relation == b"F":
            union(a, b)
            union(a + n, b + n)
        else:
            union(a, b + n)
            union(a + n, b)

    print(len({find(person) for person in range(1, n + 1)}))

if __name__ == "__main__":
    main()
