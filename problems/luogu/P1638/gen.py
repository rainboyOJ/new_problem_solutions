#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(1, 8)
    n = random.randint(m, 40)

    arr = [random.randint(1, m) for _ in range(n)]
    # 保证有解：把 1..m 至少放进去一次
    for i in range(m):
        arr[i] = i + 1
    random.shuffle(arr)

    print(n, m)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
