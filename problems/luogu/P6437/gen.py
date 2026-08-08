#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 12)
    arr = [random.randint(1, 50) for _ in range(n)]
    valid = []
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                valid.append(arr[i] + arr[j] + arr[k])
    m = random.randint(min(valid), max(valid) + 20)
    print(n, m)
    print(*arr)


if __name__ == "__main__":
    main()
