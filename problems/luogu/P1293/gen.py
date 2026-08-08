#!/usr/bin/env python3
import random


def main():
    random.seed()
    m = random.randint(1, 8)
    used = set()
    items = []
    for i in range(m):
        cnt = random.randint(1, 10)
        pos = random.randint(0, 30)
        while pos in used:
            pos = random.randint(0, 30)
        used.add(pos)
        items.append((cnt, pos, f"city{i}"))
    random.shuffle(items)
    for cnt, pos, name in items:
        print(cnt, pos, name)


if __name__ == "__main__":
    main()
