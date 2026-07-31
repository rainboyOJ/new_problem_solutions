#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    q = random.randint(1, 60)
    print(n, q)
    for _ in range(n):
        print(f"{random.uniform(-20, 20):.6f} {random.uniform(-20, 20):.6f}")

    for _ in range(q):
        left = random.randint(1, n)
        right = random.randint(left, n)
        kind = random.randint(1, 7)
        if kind == 1:
            print(kind, left, right, f"{random.uniform(-10, 10):.6f}", f"{random.uniform(-10, 10):.6f}")
        elif kind == 2:
            print(kind, left, right, f"{random.uniform(-10, 10):.6f}", f"{random.uniform(-10, 10):.6f}", f"{random.uniform(-3.13, 3.13):.6f}")
        elif kind == 3:
            print(kind, left, right, f"{random.uniform(-10, 10):.6f}", f"{random.uniform(-10, 10):.6f}", f"{random.uniform(-1.5, 1.5):.6f}")
        elif kind == 4 or kind == 5:
            print(kind, left, right, f"{random.uniform(-1.56, 1.56):.6f}", f"{random.uniform(-10, 10):.6f}")
        elif kind == 6:
            print(kind, left, right)
        else:
            print(kind, left, right, f"{random.uniform(-20, 20):.6f}", f"{random.uniform(-20, 20):.6f}")


if __name__ == "__main__":
    main()
