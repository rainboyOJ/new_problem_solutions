#!/usr/bin/env python3
import random


def one_case_value():
    # 让暴力可承受，所以随机范围控制在 1e12 以内。
    typ = random.randint(1, 5)
    if typ == 1:
        a = random.randint(1, 10000)
        b = random.randint(1, 10000)
        return a * a * a * b
    if typ == 2:
        p = random.randint(2, 1000000)
        return p
    if typ == 3:
        p = random.randint(2, 1000000)
        return p * p
    if typ == 4:
        p = random.randint(2, 1000)
        q = random.randint(2, 1000)
        return p * p * q * q * q
    return random.randint(1, 10**12)


def main():
    random.seed()
    n = random.randint(1, 40)
    print(n)
    arr = [str(one_case_value()) for _ in range(n)]
    print(" ".join(arr))


if __name__ == "__main__":
    main()
