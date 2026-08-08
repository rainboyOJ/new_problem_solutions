#!/usr/bin/env python3
import random

def main():
    n = random.randint(1, 100)
    L = random.randint(1, n)
    R = random.randint(L, n)

    # 统计合法超级和弦总数，确保 k 不超过
    total = 0
    for i in range(1, n + 1):
        left = i + L - 1
        right = min(i + R - 1, n)
        if left <= right:
            total += right - left + 1

    k = random.randint(1, max(1, total))
    a = [random.randint(-1000, 1000) for _ in range(n)]

    print(n, k, L, R)
    for x in a:
        print(x)

if __name__ == "__main__":
    main()
