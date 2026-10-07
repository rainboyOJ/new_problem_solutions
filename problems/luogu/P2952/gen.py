#!/usr/bin/env python3
import random


def main():
    s = random.randint(1, 80)
    line_size = 0
    ops = []

    for _ in range(s):
        if line_size == 0:
            dir_ = random.choice(["L", "R"])
            ops.append(f"A {dir_}")
            line_size += 1
            continue

        if random.randint(0, 1) == 0:
            dir_ = random.choice(["L", "R"])
            ops.append(f"A {dir_}")
            line_size += 1
        else:
            dir_ = random.choice(["L", "R"])
            k = random.randint(1, line_size)
            ops.append(f"D {dir_} {k}")
            line_size -= k

    if line_size == 0:
        dir_ = random.choice(["L", "R"])
        ops.append(f"A {dir_}")

    print(len(ops))
    for op in ops:
        print(op)


if __name__ == "__main__":
    main()
