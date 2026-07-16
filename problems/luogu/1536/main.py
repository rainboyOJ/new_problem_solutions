import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0
    answer = []

    while pos < len(data):
        n = data[pos]
        pos += 1
        if n == 0:
            break
        m = data[pos]
        pos += 1

        parent = list(range(n + 1))
        size = [1] * (n + 1)
        blocks = n

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        for _ in range(m):
            a, b = find(data[pos]), find(data[pos + 1])
            pos += 2
            if a == b:
                continue
            if size[a] < size[b]:
                a, b = b, a
            parent[b] = a
            size[a] += size[b]
            blocks -= 1

        answer.append(str(blocks - 1))

    print("\n".join(answer))


if __name__ == "__main__":
    main()
