import sys


def main():
    a, b, minimum_prime = map(int, sys.stdin.buffer.read().split())
    parent = list(range(b - a + 1))
    size = [1] * len(parent)
    groups = len(parent)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(x, y):
        nonlocal groups
        x, y = find(x), find(y)
        if x == y:
            return
        if size[x] < size[y]:
            x, y = y, x
        parent[y] = x
        size[x] += size[y]
        groups -= 1

    is_prime = bytearray(b + 1)
    is_prime[2:] = b"\x01" * (b - 1)
    for number in range(2, int(b ** 0.5) + 1):
        if is_prime[number]:
            start = number * number
            is_prime[start:b + 1:number] = b"\x00" * ((b - start) // number + 1)

    for prime in range(minimum_prime, b + 1):
        if not is_prime[prime]:
            continue
        first = (a + prime - 1) // prime * prime
        for multiple in range(first + prime, b + 1, prime):
            union(first - a, multiple - a)

    print(groups)


if __name__ == "__main__":
    main()
