#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    size = 0
    ops = []
    for _ in range(n):
        if size == 0:
            op = random.choice([0, 2])
        else:
            op = random.randint(0, 2)
        if op == 0:
            x = random.randint(0, 100)
            ops.append(f"0 {x}")
            size += 1
        elif op == 1:
            ops.append("1")
            size -= 1
        else:
            ops.append("2")
    print(n)
    for line in ops:
        print(line)


if __name__ == "__main__":
    main()
