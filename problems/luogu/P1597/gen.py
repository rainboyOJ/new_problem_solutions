#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    vars_ = "abc"
    parts = []
    for _ in range(n):
        left = random.choice(vars_)
        if random.randint(0, 1) == 0:
            right = random.choice(vars_)
        else:
            right = str(random.randint(0, 9))
        parts.append(f"{left}:={right};")
    print("".join(parts))


if __name__ == "__main__":
    main()
