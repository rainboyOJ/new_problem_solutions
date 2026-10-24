#!/usr/bin/env python3
import random
import sys

def main():
    # 随机生成适合对拍的数据：T 稍小（如 10 ~ 1000），便于 brute.cpp 快速跑完
    # n 在 2 ~ 6 之间，m 在 n ~ 15 之间，k 在 0 ~ 5 之间
    n = random.randint(2, 6)
    m = random.randint(n, 12)
    T = random.randint(5, 500)
    k = random.randint(0, min(5, T))

    c = [random.randint(1, 20) for _ in range(n)]

    # 保证每座城市至少有一条出边
    edges = []
    for u in range(1, n + 1):
        v = random.randint(1, n)
        while v == u:
            v = random.randint(1, n)
        w = random.randint(1, 5)
        edges.append((u, v, w))

    # 额外补充边
    for _ in range(m - n):
        u = random.randint(1, n)
        v = random.randint(1, n)
        while v == u:
            v = random.randint(1, n)
        w = random.randint(1, 5)
        edges.append((u, v, w))

    # 保证美食节时间互不相同且 1 <= t <= T
    times = sorted(random.sample(range(1, T + 1), k))
    festivals = []
    for t in times:
        x = random.randint(1, n)
        y = random.randint(1, 50)
        festivals.append((t, x, y))

    print(f"{n} {len(edges)} {T} {k}")
    print(" ".join(map(str, c)))
    for u, v, w in edges:
        print(f"{u} {v} {w}")
    for t, x, y in festivals:
        print(f"{t} {x} {y}")

if __name__ == "__main__":
    main()
