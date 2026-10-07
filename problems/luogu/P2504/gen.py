#!/usr/bin/env python3
import random


def main():
    random.seed()

    monkey_cnt = random.randint(1, 8)
    print(monkey_cnt)
    jumps = [random.randint(0, 15) for _ in range(monkey_cnt)]
    print(*jumps)

    tree_cnt = random.randint(2, 8)
    print(tree_cnt)

    used = set()
    for _ in range(tree_cnt):
        while True:
            x = random.randint(-6, 6)
            y = random.randint(-6, 6)
            if (x, y) not in used:
                used.add((x, y))
                print(x, y)
                break


if __name__ == "__main__":
    main()
