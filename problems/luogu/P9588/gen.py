#!/usr/bin/env python3
import random


def main():
    random.seed()
    q = random.randint(1, 80)
    ops = []
    size = 0

    for _ in range(q):
        choices = [1]
        if size > 0:
            choices.extend([2, 3, 4])
        op = random.choice(choices)

        if op == 1:
            x = random.randint(1, 8)
            ops.append((1, x))
            size += x
        elif op == 2:
            y = random.randint(1, size)
            ops.append((2, y))
            size -= y
        elif op == 3:
            z = random.randint(1, size)
            ops.append((3, z))
        else:
            ops.append((4,))

    print(0, len(ops))
    for op in ops:
        print(*op)


if __name__ == "__main__":
    main()
